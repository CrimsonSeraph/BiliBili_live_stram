#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <qrgb.h>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MyWindow;
}
QT_END_NAMESPACE

class MyWindow : public QWidget {
	Q_OBJECT

public:
	enum mode {
		dark_mode,
		light_mode
	};

	MyWindow(QWidget* parent = nullptr);
	~MyWindow();

	void changeMode();

private slots:

    void on_change_mode_clicked();

private:
	Ui::MyWindow* ui;
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
        "   background-color: rgba(80, 80, 80, 0.8);"
        "   color: rgba(255,255,255,1);"
        "   border-radius: 6px;"
        "   border: 1px solid rgba(255,255,255,0.1);"
        "   padding: 6px 12px;"
		"}"
		"QPushButton:hover {"
        "   background-color: rgba(110, 110, 110, 0.8);"
		"}"
		"QPushButton:pressed {"
        "   background-color: rgba(60, 60, 60, 0.8);"
		"}");
	QString dark_mode_button_style = QString("QPushButton {"
        "	background-color: rgba(50, 50, 50, 0.8);"
        "	color: rgba(255,255,255,1);"
		"	border-radius: 6px;"
        "	border: 1px solid rgba(255,255,255,0.05);"
		"	padding: 6px 12px;"
		"}"
		"QPushButton:hover {"
        "	background-color: rgba(70, 70, 70, 0.8);"
		"}"
		"QPushButton:pressed {"
        "	background-color: rgba(40, 40, 40, 0.8);"
		"}");
};
#endif // MYWINDOW_H
