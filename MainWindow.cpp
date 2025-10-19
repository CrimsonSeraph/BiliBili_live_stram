#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MainWindow) {
	ui->setupUi(this);
    this->setStyleSheet(light_mode_bg_style);
    setButtonMode(light_mode_button_style);
}

MainWindow::~MainWindow() {
	delete ui;
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

