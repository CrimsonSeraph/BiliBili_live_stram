#include "MyWindow.h"
#include "./ui_MyWindow.h"

MyWindow::MyWindow(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MyWindow) {
	ui->setupUi(this);
    this->setStyleSheet(light_mode_bg_style);
    this->ui->change_mode->setStyleSheet(light_mode_button_style);
}

MyWindow::~MyWindow() {
	delete ui;
}

void MyWindow::changeMode() {
	w_mode = (w_mode == mode::dark_mode) ? mode::light_mode : mode::dark_mode;
    switch (w_mode) {
	case mode::dark_mode:
		this->setStyleSheet(dark_mode_bg_style);
        this->ui->change_mode->setStyleSheet(dark_mode_button_style);
		break;
	case mode::light_mode:
		this->setStyleSheet(light_mode_bg_style);
        this->ui->change_mode->setStyleSheet(light_mode_button_style);
		break;
	}
}

void MyWindow::on_change_mode_clicked() {
    changeMode();
}

