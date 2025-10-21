#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qrgb.h>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QApplication>
#include <QStyle>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	enum mode {
		dark_mode,
		light_mode
	};

	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void closeEvent(QCloseEvent* event) override;
	void changeEvent(QEvent* event) override;
	void changeMode();
	void setButtonMode(QString style);

private slots:

	void on_change_mode_clicked();

private:
	Ui::MainWindow* ui;
	QSystemTrayIcon* tray;

    QString menu_style = QString("QMenu {"
		"  background-color: rgba(30,30,30,230);"
		"  color: white;"
		"  border: 1px solid gray;"
		"}"
		"QMenu::item {"
		"  padding: 5px 30px;"
		"}"
		"QMenu::item:selected {"
		"  background-color: rgba(50,50,50,255);"
		"}");

	mode w_mode = mode::light_mode;
	QString light_mode_bg_style = QString("background:qlineargradient("
		"x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
		"stop : 0 rgba(255, 192, 203, 1),"
		"stop : 0.5 rgba(250, 250, 250, 1),"
		"stop : 1 rgba(135, 206, 235, 1))");
	QString dark_mode_bg_style = QString("background:qlineargradient("
		"x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
		"stop : 0 rgba(205, 140, 149, 1),"
		"stop : 0.5 rgba(207, 207, 207, 1),"
		"stop : 1 rgba(0, 104, 139, 1))");

	QString light_mode_button_style = QString("QPushButton {"
		"   background-color: rgba(238, 169, 184,0.6);"
		"   color: rgba(255,255,255,1);"
		"   border-radius: 3px;"
		"   border: 3px solid rgba(255,255,255,0.1);"
		"   padding: 3px 6px;"
		"}"
		"QPushButton:hover {"
		"   background-color: rgba(255, 181, 197,0.6);"
		"}"
		"QPushButton:pressed {"
		"   background-color: rgba(205, 145, 158,0.6);"
		"}");
	QString dark_mode_button_style = QString("QPushButton {"
		"	background-color: rgba(100, 149, 237,0.6);"
		"	color: rgba(255,255,255,1);"
		"	border-radius: 3px;"
		"	border: 3px solid rgba(255,255,255,0.05);"
		"	padding: 3px 6px;"
		"}"
		"QPushButton:hover {"
		"	background-color: rgba(70, 130, 180,0.6);"
		"}"
		"QPushButton:pressed {"
		"	background-color: rgba(25, 25, 112,0.6);"
		"}");
};
#endif // MAINWINDOW_H
