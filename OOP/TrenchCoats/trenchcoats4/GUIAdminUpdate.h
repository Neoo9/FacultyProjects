#pragma once
#include <qwidget.h>
#include "GUIAdmin.h"

class GUIAdminUpdate : public QWidget{
	Q_OBJECT
private:
	GUIAdmin* parent;
	QLineEdit* name1;
	QLineEdit* size1;
	QLineEdit* colour1;
	QLineEdit* quantity1;
	QLineEdit* price1;
	QLineEdit* name2;
	QLineEdit* size2;
	QLineEdit* colour2;
	QLineEdit* quantity2;
	QLineEdit* price2;
	QLineEdit* photograph2;
	QPushButton* button;
	void init();
	void connect();
	void update_gui();
public:
	GUIAdminUpdate(GUIAdmin* par);
	~GUIAdminUpdate() = default;
};

