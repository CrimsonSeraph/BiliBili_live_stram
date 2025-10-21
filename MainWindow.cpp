#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);
    this->setStyleSheet(light_mode_bg_style);
    setButtonMode(light_mode_button_style);

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
    tray->setToolTip("BiliBili推流码获取");
    tray->show();

    QMenu *menu = new QMenu(this);
    menu->setStyleSheet(menu_style);
    menu->addAction("退出", qApp, &QCoreApplication::quit);
    tray->setContextMenu(menu);

    connect(tray, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason){
        if(reason == QSystemTrayIcon::Trigger) {
            this->show();
            this->raise();
            this->setWindowState(Qt::WindowActive);
        }
    });
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(tray->isVisible()) {
        event->ignore();
        this->hide();
    } else {
        event->accept();
    }
}

void MainWindow::changeEvent(QEvent *event) {
    if(event->type() == QEvent::WindowStateChange) {
        if(this->isMinimized()) {
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
        setButtonMode(dark_mode_button_style);
		break;
	case mode::light_mode:
		this->setStyleSheet(light_mode_bg_style);
        setButtonMode(light_mode_button_style);
		break;
	}
}

void MainWindow::setButtonMode(QString style){
    this->ui->login->setStyleSheet(style);

    this->ui->change_mode->setStyleSheet(style);
    this->ui->live_start->setStyleSheet(style);
    this->ui->live_stop->setStyleSheet(style);
    this->ui->get_stram->setStyleSheet(style);
    this->ui->setting->setStyleSheet(style);
}

void MainWindow::on_change_mode_clicked() {
    changeMode();
}

