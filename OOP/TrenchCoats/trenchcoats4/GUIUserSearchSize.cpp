#include "GUIUserSearchSize.h"
#include <qgridlayout.h>
#include <windows.h>
#include <qmessagebox.h>

GUIUserSearchSize::GUIUserSearchSize(GUIUser* us) : parent{ us } {
	this->init();
	this->connect();
}


void GUIUserSearchSize::init(){
	this->setAttribute(Qt::WA_DeleteOnClose);
	QWidget* main = new QWidget();
	QGridLayout* grid = new QGridLayout();
	this->yes = new QPushButton("Yes");
	this->no = new QPushButton("No");
	this->text = new QLabel("Do you want to add this trench coat to the basket?");
	this->curr = new QLabel();
	grid->addWidget(this->curr, 0, 0, 1, 2);
	grid->addWidget(this->text, 1, 0, 1, 2);
	grid->addWidget(this->yes, 2, 0);
	grid->addWidget(this->no, 2, 1);
	main->setLayout(grid);
	main->show();
	this->curr_index = 0;
	this->curr->setText(QString::fromStdString(this->parent->temp->get_repo()->at(this->curr_index).to_string()));
	ShellExecuteA(NULL, "open", this->parent->temp->get_repo()->at(this->curr_index).get_photograph().c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void GUIUserSearchSize::connect(){
	QObject::connect(this->yes, &QPushButton::clicked, [this]() {
		this->parent->cont->add_basket(this->parent->temp->get_repo()->at(this->curr_index), this->parent->temp, this->parent->total);
		this->notify_all();
		QMessageBox::information(this, "Success", "Trench coat was added to the basket");
		if (this->curr_index == this->parent->temp->get_repo()->size() - 1)
			this->curr_index = 0;
		else
			this->curr_index++;
		this->curr->setText(QString::fromStdString(this->parent->temp->get_repo()->at(this->curr_index).to_string()));
		ShellExecuteA(NULL, "open", this->parent->temp->get_repo()->at(this->curr_index).get_photograph().c_str(), NULL, NULL, SW_SHOWNORMAL);
		});
	QObject::connect(this->no, &QPushButton::clicked, [this]() {
		if (this->curr_index == this->parent->temp->get_repo()->size() - 1)
			this->curr_index = 0;
		else
			this->curr_index++;
		this->curr->setText(QString::fromStdString(this->parent->temp->get_repo()->at(this->curr_index).to_string()));
		ShellExecuteA(NULL, "open", this->parent->temp->get_repo()->at(this->curr_index).get_photograph().c_str(), NULL, NULL, SW_SHOWNORMAL);
		});
}

