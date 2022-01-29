#pragma once
#include <qwidget.h>
#include "GUIUser.h"
#include <qlabel.h>
#include "Subject.h"

class GUIUserSearchSize : public QWidget, public Subject{
	Q_OBJECT
private:
	GUIUser* parent;
	QPushButton* yes;
	QPushButton* no;
	QLabel* text;
	QLabel* curr;
	int curr_index;
	void init();
	void connect();
public:
	GUIUserSearchSize(GUIUser* us);
	~GUIUserSearchSize() = default;
};

