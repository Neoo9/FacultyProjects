#pragma once
#include <qwidget.h>
#include <QPushButton>
#include <QRadioButton>

class StartUpGUI : public QWidget{
	Q_OBJECT
private:
	QPushButton* start;
	QRadioButton* admin_button;
	QRadioButton* user_button;
	QRadioButton* csv_button;
	QRadioButton* html_button;
	QWidget* main;
	int* option_1;
	int* option_2;
	void init();
	void connect();
public:
	StartUpGUI(int* option_1, int* option_2);
	~StartUpGUI() = default;
};

