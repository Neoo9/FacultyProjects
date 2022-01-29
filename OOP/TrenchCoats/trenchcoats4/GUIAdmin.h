#pragma once
#include <qwidget.h>
#include "Controller.h"
#include <QMenu>
#include <QListWidget>
#include <qmainwindow.h>
#include <QPushButton>
#include <qmessagebox.h>
#include <qset.h>
#include <qevent.h>

class GUIAdmin : public QMainWindow{
	Q_OBJECT
private:
	Controller* cont;
	QPushButton* add;
	QPushButton* remove;
	QPushButton* update;
	QPushButton* undo;
	QPushButton* redo;
	QListWidget* list;
	void init();
	void populate();
	void connect();
	QSet<int> pressed_keys;
public:
	GUIAdmin(Controller* cont);
	~GUIAdmin() = default;
	friend class GUIAdminAddRemove;
	friend class GUIAdminUpdate;
	bool eventFilter(QObject* obj, QEvent* event);
};

