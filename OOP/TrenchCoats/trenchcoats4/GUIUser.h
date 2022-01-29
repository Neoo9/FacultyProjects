#pragma once
#include <qwidget.h>
#include <qmainwindow.h>
#include "Controller.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <vector>
#include <qset.h>
#include <qtableview.h>
#include "ModelViewTable.h"
#include "Subject.h"

class GUIUser : public QMainWindow, public Subject{
	Q_OBJECT
private:
	Controller* cont;
	ModelViewTable* model_view;
	QWidget* main;
	QPushButton* search_size;
	QPushButton* see_basket;
	QPushButton* buy_all;
	QPushButton* chart;
	QLineEdit* size;
	QTableView* table;
	void init();
	void connect();
	double total;
	InMemoryRepository* temp;
	QSet<int> pressed_keys;
	QPushButton* undo;
	QPushButton* redo;
public:
	GUIUser(Controller* cont, InMemoryRepository* temp, ModelViewTable* model);
	~GUIUser() = default;
	friend class GUIUserSearchSize;
	friend class GUIChart;
	bool eventFilter(QObject* obj, QEvent* event);
};

