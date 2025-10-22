#include "LoginManager.h"
#include "qrcodegen.hpp"

using namespace qrcodegen;

LoginManager::LoginManager(QObject *parent)
    : QObject(parent),
    network(new QNetworkAccessManager(this)),
    pollTimer(new QTimer(this)) {

    pollTimer->setInterval(2000);
    connect(pollTimer, &QTimer::timeout, this, &LoginManager::onPollStatus);
}

void LoginManager::startLogin() {
    QNetworkRequest req(QUrl("https://passport.bilibili.com/x/passport-login/web/qrcode/generate"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; QtApp)");
    req.setRawHeader("Referer", "https://www.bilibili.com/");

    QNetworkReply *reply = network->get(req);
    connect(reply, &QNetworkReply::finished, this, &LoginManager::onGenerateFinished);
    emit loginStatusChanged("正在请求二维码...");
}


void LoginManager::onGenerateFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    QByteArray bytes = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    if (!doc.isObject()) {
        emit loginStatusChanged("二维码生成失败 (响应异常)");
        reply->deleteLater();
        return;
    }

    QJsonObject root = doc.object();
    QJsonObject obj = root["data"].toObject();

    qrcodeKey = obj["qrcode_key"].toString();

    if (qrcodeKey.isEmpty()) {
        emit loginStatusChanged("二维码生成失败 (无效数据)");
        reply->deleteLater();
        return;
    }

    QString url = QString("https://account.bilibili.com/h5/account-h5/auth/scan-web?qrcode_key=%1").arg(qrcodeKey);
    generateQRCodeImage(url);
    emit qrCodeUpdated(currentQR);
    emit loginStatusChanged("请使用B站客户端扫码登录");

    pollTimer->start();
    reply->deleteLater();
}


void LoginManager::generateQRCodeImage(const QString &url) {
    //生成二维码
    QrCode qr = QrCode::encodeText(url.toUtf8().constData(), QrCode::Ecc::LOW);
    int size = qr.getSize();
    if(size <= 0){
        qDebug() << "二维码生成失败，url:" << url;
        return;
    }

    int scale = 6;
    QImage img(size*scale, size*scale, QImage::Format_RGB32);
    img.fill(Qt::white);
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (qr.getModule(x,y)) {
                for(int dy=0; dy<scale; ++dy){
                    for(int dx=0; dx<scale; ++dx){
                        img.setPixel(x*scale+dx, y*scale+dy, qRgb(0,0,0));
                    }
                }
            }
        }
    }
    currentQR = QPixmap::fromImage(img);
    emit qrCodeUpdated(currentQR);

    currentQR = QPixmap::fromImage(img);
}

QPixmap LoginManager::getQRCode() const {
    return currentQR;
}

void LoginManager::onPollStatus() {
    if (qrcodeKey.isEmpty()) return;

    QUrl url(QString("https://passport.bilibili.com/x/passport-login/web/qrcode/poll?qrcode_key=%1").arg(qrcodeKey));
    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", "Mozilla/5.0");
    QNetworkReply *reply = network->get(req);
    connect(reply, &QNetworkReply::finished, this, &LoginManager::onPollFinished);
}

void LoginManager::onPollFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    QByteArray bytes = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    QJsonObject root = doc.object();
    QJsonObject data = root["data"].toObject();
    int status = data.value("code").toInt(-1);
    QString message = data.value("message").toString();

    switch (status) {
    case 0:
        emit loginStatusChanged("登录成功！");
        emit loginSuccess();
        pollTimer->stop();
        break;
    case 86038:
        emit loginStatusChanged("二维码已失效，请重新生成");
        pollTimer->stop();
        startLogin();
        break;
    case 86046:
        emit loginStatusChanged("等待扫码中...");
        break;
    case 86090:
        emit loginStatusChanged("已扫码，等待确认");
        break;
    case 86101:
        emit loginStatusChanged("未扫码");
        break;
    default:
        qDebug() << "未知状态:" << root;
        break;
    }

}

void LoginManager::saveCookiesFromReply(QNetworkReply *reply) {
    QList<QNetworkCookie> cookies = reply->manager()->cookieJar()->cookiesForUrl(reply->url());
    for (auto &cookie : cookies)
        qDebug() << "Cookie:" << cookie.name() << "=" << cookie.value();
}
