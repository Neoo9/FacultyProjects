#include "GUIUser.h"
#include <qgridlayout.h>
#include <qformlayout.h>
#include "GUIUserSearchSize.h"
#include <windows.h>
#include <qmessagebox.h>
#include "GUIChart.h"
#include <qevent.h>
#include <qheaderview.h>
#include "CustomDelegate.h"

GUIUser::GUIUser(Controller* cont, InMemoryRepository* temp, ModelViewTable* model) : cont{ cont }, temp{ temp }, model_view{ model } {
	this->cont->get_controller()->load();
	this->init();
	this->connect();
	this->total = 0;
}

void GUIUser::init(){
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->main = new QWidget();
	this->main->setMinimumSize(QSize(700, 400));
	this->main->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	this->main->installEventFilter(this);
	QGridLayout* grid = new QGridLayout();
	QFormLayout* form = new QFormLayout();
	this->table = new QTableView();
	this->table->setModel(this->model_view);
	this->table->resizeColumnsToContents();
	this->table->resizeRowsToContents();
	this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->table->setItemDelegate(new CustomDelegate{this->cont});
	this->table->horizontalHeader()->setDefaultSectionSize(100);
	this->table->verticalHeader()->setDefaultSectionSize(100);
	this->size = new QLineEdit();
	form->addRow("Size", this->size);
	this->search_size = new QPushButton("Search by size");
	this->see_basket = new QPushButton("See basket");
	this->buy_all = new QPushButton("Checkout");
	this->chart = new QPushButton("Chart");
	this->undo = new QPushButton("Undo");
	this->redo = new QPushButton("Redo");
	grid->addWidget(this->table, 0, 0, 1, 3);
	grid->addWidget(this->search_size, 1, 0);
	grid->addLayout(form, 1, 1, 1, 2);
	grid->addWidget(this->see_basket, 2, 1);
	grid->addWidget(this->buy_all, 2, 2);
	grid->addWidget(this->chart, 2, 0);
	grid->addWidget(this->undo, 3, 0);
	grid->addWidget(this->redo, 3, 2);
	this->main->setLayout(grid);
	this->main->show();
}

void GUIUser::connect(){
	QObject::connect(this->search_size, &QPushButton::clicked, [this]() {
		try {
			std::string size = this->size->text().toStdString();
			this->cont->user_search_coats_cont(size, this->temp);
			GUIUserSearchSize* search = new GUIUserSearchSize(this);
			search->add_observer(this->model_view);
		}
		catch (...) {
			QMessageBox::critical(this, "Error", "Couldn't get the trench coats");
		}
		});
	QObject::connect(this->see_basket, &QPushButton::clicked, [this]() {
		this->cont->get_basket()->save();
		CSVRepository& temp = static_cast<CSVRepository&>(*this->cont->get_basket());
		ShellExecuteA(NULL, "open", temp.get_file().c_str(), NULL, NULL, SW_SHOWNORMAL);
		});
	QObject::connect(this->buy_all, &QPushButton::clicked, [this]() {
		for (TrenchCoat tc : *this->cont->get_basket()->get_repo()) {
			this->cont->get_controller()->remove_repo(tc);
		}
		std::ostringstream str;
		str << "Your total was " << this->total << "\nThanks for your patronage!";
		QMessageBox::information(this, "Success", QString::fromStdString(str.str()));
		this->cont->get_controller()->save();
		this->main->close();
		});
	QObject::connect(this->chart, &QPushButton::clicked, [this]() {
		GUIChart* chart = new GUIChart(this);
		});
	QObject::connect(this->undo, &QPushButton::clicked, [this]() {
		try {
			this->cont->undo_op_user();
			this->notify_all();
		}
		catch (...) {
			QMessageBox::critical(this, "Error", "Couldn't perform the undo");
		}
		});
	QObject::connect(this->redo, &QPushButton::clicked, [this]() {
		try {
			this->cont->redo_op_user();
			this->notify_all();
		}
		catch (...) {
			QMessageBox::critical(this, "Error", "Couldn't perform the redo");
		}
		});
}

bool GUIUser::eventFilter(QObject* obj, QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		this->pressed_keys += ((QKeyEvent*)event)->key();
		if (pressed_keys.contains(Qt::Key_Control) && pressed_keys.contains(Qt::Key_Z)) {
			try {
				pressed_keys -= (Qt::Key_Control);
				pressed_keys -= (Qt::Key_Z);
				this->cont->undo_op_user();
				this->notify_all();
			}
			catch (...) {
				QMessageBox::critical(this, "Error", "Couldn't perform the undo");
			}
		}
		else if (pressed_keys.contains(Qt::Key_Control) && pressed_keys.contains(Qt::Key_Y)) {
			try {
				pressed_keys -= (Qt::Key_Control);
				pressed_keys -= (Qt::Key_Y);
				this->cont->redo_op_user();
				this->notify_all();
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


