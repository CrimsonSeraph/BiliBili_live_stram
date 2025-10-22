#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QTimer>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>
#include <QImage>
#include <QPainter>
#include <QDebug>

class LoginManager : public QObject {
    Q_OBJECT
public:
    explicit LoginManager(QObject *parent = nullptr);

    void startLogin();//启动登录流程
    QPixmap getQRCode() const;//返回当前二维码图像

signals:
    void qrCodeUpdated(const QPixmap &pix);//当二维码生成后通知UI更新
    void loginStatusChanged(const QString &status);
    void loginSuccess();//登录成功信号

private slots:
    void onGenerateFinished();//获取二维码接口回调
    void onPollStatus();//轮询状态
    void onPollFinished();//轮询回调

private:
    void generateQRCodeImage(const QString &url);//生成二维码
    void saveCookiesFromReply(QNetworkReply *reply);

    QNetworkAccessManager *network;
    QTimer *pollTimer;
    QString qrcodeKey;
    QPixmap currentQR;
};

#endif // LOGINMANAGER_H
