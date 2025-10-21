#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);
    resetLoginButtonText();
	this->setStyleSheet(light_mode_bg_style);
	setButtonStyle(light_mode_button_style);
	setInfoStyle(info_light_style);

	tray = new QSystemTrayIcon(this);
	tray->setIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
	tray->setToolTip("BiliBili推流码获取");
	tray->show();

	QMenu* menu = new QMenu(this);
	menu->setStyleSheet(menu_style);
	menu->addAction("退出", qApp, &QCoreApplication::quit);
	tray->setContextMenu(menu);

	connect(tray, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) {
		if (reason == QSystemTrayIcon::Trigger) {
			this->show();
			this->raise();
			this->setWindowState(Qt::WindowActive);
		}
		});
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
	if (tray->isVisible()) {
		event->ignore();
		this->hide();
	}
	else {
		event->accept();
	}
}

void MainWindow::changeEvent(QEvent* event) {
	if (event->type() == QEvent::WindowStateChange) {
		if (this->isMinimized()) {
			this->hide();
			tray->showMessage("提示", "程序已最小化到托盘");
		}
	}
	QMainWindow::changeEvent(event);
}


void MainWindow::changeMode() {
	w_mode = (w_mode == mode::dark_mode) ? mode::light_mode : mode::dark_mode;
	switch (w_mode) {
	case mode::dark_mode:
		this->setStyleSheet(dark_mode_bg_style);
		setButtonStyle(dark_mode_button_style);
		setInfoStyle(info_dark_style);
		break;
	case mode::light_mode:
		this->setStyleSheet(light_mode_bg_style);
		setButtonStyle(light_mode_button_style);
		setInfoStyle(info_light_style);
		break;
	}
}

void MainWindow::setButtonStyle(const QString style) {
	auto buttons = this->findChildren<QPushButton*>();
	for (auto& btn : buttons)
		btn->setStyleSheet(style);
}

void MainWindow::setInfoStyle(const QString style) {
	QPixmap pix(":/AllAssets/assets/default_avatar.png");
	ui->avatar->setPixmap(pix);
	ui->avatar->setScaledContents(true);
	ui->avatar->setAlignment(Qt::AlignCenter);

	ui->name->setStyleSheet(style);
	ui->avatar->setStyleSheet(style);
	ui->fans->setStyleSheet(style);
	ui->like->setStyleSheet(style);

	ui->name->setText("账号名称(等待登录)");
	ui->fans->setText("粉丝");
	ui->like->setText("获赞");
}

void MainWindow::quit() {
	qApp->quit();
}

void MainWindow::resetLoginButtonText() {
	ui->login->setText(isLogin ? "信息" : "登录");
};

void MainWindow::on_change_mode_clicked() {
	changeMode();
}


void MainWindow::on_quit_clicked() {
	quit();
}
