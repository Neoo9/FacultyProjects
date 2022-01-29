#include "GUIAdmin.h"
#include <QGridLayout>
#include "GUIAdminAddRemove.h"
#include "GUIAdminUpdate.h"

GUIAdmin::GUIAdmin(Controller* cont) : cont{cont}{
	this->init();
	this->connect();
	this->cont->get_controller()->load();
	this->populate();
}

void GUIAdmin::init()
{
	this->setAttribute(Qt::WA_DeleteOnClose);
	QWidget* main = new QWidget();
	main->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	main->installEventFilter(this);
	QGridLayout* grid = new QGridLayout();
	this->list = new QListWidget();
	this->add = new QPushButton("Add");
	this->remove = new QPushButton("Remove");
	this->update = new QPushButton("Update");
	this->undo = new QPushButton("Undo");
	this->redo = new QPushButton("Redo");
	grid->addWidget(list, 0, 0, 1, 3);
	grid->addWidget(this->add, 1, 0);
	grid->addWidget(this->remove, 1, 1);
	grid->addWidget(this->update, 1, 2);
	grid->addWidget(this->undo, 2, 0);
	grid->addWidget(this->redo, 2, 2);
	main->setLayout(grid);
	main->setMinimumSize(QSize(700, 400));
	main->show();
}

void GUIAdmin::populate() {
	if (this->list->count() > 0) {
		this->list->clear();
	}
	for (auto& tc : *this->cont->get_controller()->get_repo()) {
		QString str = QString::fromStdString(tc.to_string());
		QListWidgetItem* item = new QListWidgetItem(str);
		this->list->addItem(item);
	}
}

void GUIAdmin::connect()
{
	QObject::connect(this->add, &QPushButton::clicked, [this]() {
		GUIAdminAddRemove* addrem = new GUIAdminAddRemove(this, 0);
		});
	QObject::connect(this->remove, &QPushButton::clicked, [this]() {
		GUIAdminAddRemove* addrem = new GUIAdminAddRemove(this, 1);
		});
	QObject::connect(this->update, &QPushButton::clicked, [this]() {
		GUIAdminUpdate* upt = new GUIAdminUpdate(this);
		});
	QObject::connect(this->undo, &QPushButton::clicked, [this]() {
		try {
			this->cont->undo_op_admin();
			this->populate();
		}
		catch (...) {
			QMessageBox::critical(this, "Error", "Couldn't perform the undo");
		}
		});
	QObject::connect(this->redo, &QPushButton::clicked, [this]() {
		try {
			this->cont->redo_op_admin();
			this->populate();
		}
		catch (...) {
			QMessageBox::critical(this, "Error", "Couldn't perform the redo");
		}
		});
}

bool GUIAdmin::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		this->pressed_keys += ((QKeyEvent*)event)->key();
		if (pressed_keys.contains(Qt::Key_Control) && pressed_keys.contains(Qt::Key_Z)) {
			try {
				pressed_keys -= (Qt::Key_Control);
				pressed_keys -= (Qt::Key_Z);
				this->cont->undo_op_admin();
				this->populate();
			}
			catch (...) {
				QMessageBox::critical(this, "Error", "Couldn't perform the undo");
			}
		}
		else if (pressed_keys.contains(Qt::Key_Control) && pressed_keys.contains(Qt::Key_Y)) {
			try {
				pressed_keys -= (Qt::Key_Control);
				pressed_keys -= (Qt::Key_Y);
				this->cont->redo_op_admin();
				this->populate();
			}
			catch (...) {
				QMessageBox::critical(this, "Error", "Couldn't perform the redo");
			}
		}
	}
	else if (event->type() == QEvent::KeyRelease) {
		pressed_keys -= ((QKeyEvent*)event)->key();
	}
	return false;
}


