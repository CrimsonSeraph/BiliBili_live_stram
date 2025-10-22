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
#include <qdir.h>
#include <QGraphicsDropShadowEffect>

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

	void closeEvent(QCloseEvent* event) override;//窗口关闭事件
	void changeEvent(QEvent* event) override;//窗口改变事件
	void changeMode();//切换模式
	void setButtonStyle(const QString style);//设置所有按键样式
    void setInfoStyle(const QString style);//设置内容区域样式
	void quit();//退出程序
    void resetLogin();//切换登录状态

private slots:

	void on_change_mode_clicked();

    void on_login_button_clicked();

    void on_setting_button_clicked();

    void on_quit_button_clicked();

private:
	Ui::MainWindow* ui;
	QSystemTrayIcon* tray;

    bool isLogin = false;

	QString menu_style = QString("QMenu {"
		"   background-color: rgba(30, 30, 30, 1);"
		"   color: rgba(255, 255, 255, 1);"
		"   border: 1px solid gray;"
		"}"
		"QMenu::item {"
		"   padding: 5px 30px;"
		"}"
		"QMenu::item:selected {"
		"   background-color: rgba(50, 50, 50, 1);"
		"}");

	QString info_light_style = QString("QWidget {"
		"   background-color: rgba(255, 255, 255, 1);"
		"   color: rgba(130, 130, 130, 1);"
		"   border: 1px solid rgba(124, 252, 0, 1);"
		"   border-radius: 10px;"
        "   qproperty-alignment: 'AlignCenter';"
		"}");

	QString info_dark_style = QString("QWidget {"
		"   background-color: rgba(232, 232, 232, 1);"
		"   color: rgba(0, 0, 0, 1);"
		"   border: 1px solid rgba(34, 139, 34, 1);"
		"   border-radius: 10px;"
        "   qproperty-alignment: 'AlignCenter';"
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
