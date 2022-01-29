#pragma once
#include <qwidget.h>
#include "Controller.h"
#include <QLineEdit>
#include <QPushButton>
#include "GUIAdmin.h"

class GUIAdminAddRemove : public QWidget{
	Q_OBJECT
private:
	GUIAdmin* parent;
	int mode;
	QLineEdit* name;
	QLineEdit* size;
	QLineEdit* colour;
	QLineEdit* quantity;
	QLineEdit* price;
	QLineEdit* photograph;
	QPushButton* button;
	void init();
	void connect();
	void add_gui();
	void remove_gui();
public:
	GUIAdminAddRemove(GUIAdmin* c, int mode);
	~GUIAdminAddRemove() = default;
};

