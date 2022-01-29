#include "GUIAdminAddRemove.h"
#include <QFormLayout>
#include <qmessagebox.h>

GUIAdminAddRemove::GUIAdminAddRemove(GUIAdmin* c, int mode) : parent{c}, mode{mode}{
	this->init();
	this->connect();
}

void GUIAdminAddRemove::init(){
	this->setAttribute(Qt::WA_DeleteOnClose);
	QWidget* main = new QWidget();
	QFormLayout* form = new QFormLayout();
	this->name = new QLineEdit();
	this->size = new QLineEdit();
	this->colour = new QLineEdit();
	this->price = new QLineEdit();
	this->quantity = new QLineEdit();
	this->photograph = new QLineEdit();
	form->addRow("Name", this->name);
	form->addRow("Size", this->size);
	form->addRow("Colour", this->colour);
	form->addRow("Price", this->price);
	form->addRow("Quantity", this->quantity);
	if (!this->mode) {
		form->addRow("Photograph link", this->photograph);
		this->button = new QPushButton("Add");
	}
	else
		this->button = new QPushButton("Remove");
	QGridLayout* grid = new QGridLayout();
	grid->addLayout(form, 0, 0, 1, 2);
	grid->addWidget(this->button, 1, 0, 1, 2);
	main->setLayout(grid);
	main->show();
}

void GUIAdminAddRemove::connect(){
	if(!this->mode){
		QObject::connect(this->button, &QPushButton::clicked, this, &GUIAdminAddRemove::add_gui);
	}
	else {
		QObject::connect(this->button, &QPushButton::clicked, this, &GUIAdminAddRemove::remove_gui);
	}

}

void GUIAdminAddRemove::add_gui() {
	try {
		using namespace std;
		string name = this->name->text().toStdString();
		string size = this->size->text().toStdString();
		string colour = this->colour->text().toStdString();
		double price = stod(this->price->text().toStdString());
		int quantity = stod(this->quantity->text().toStdString());
		string photograph = this->photograph->text().toStdString();
		TrenchCoat tc(name, size, colour, price, quantity, photograph);
		int code = this->parent->cont->add_cont(tc);
		if (!code) {
			QMessageBox::information(this, "Success", "Trench coat was added");
		}
		else {
			QMessageBox::information(this, "Success", "Trench coat was already in the list\nQuantity was increased instead");
		}
		this->parent->cont->get_controller()->save();
		this->parent->populate();
	}
	catch (...) {
		QMessageBox::critical(this, "Error", "Couldn't add the trench coat");
	}
}

void GUIAdminAddRemove::remove_gui() {
	try {
		using namespace std;
		string name = this->name->text().toStdString();
		string size = this->size->text().toStdString();
		string colour = this->colour->text().toStdString();
		double price = stod(this->price->text().toStdString());
		int quantity = stod(this->quantity->text().toStdString());
		TrenchCoat tc(name, size, colour, price, quantity, "");
		int code = this->parent->cont->remove_cont(tc);
		if (!code) {
			QMessageBox::information(this, "Success", "Trench coat was removed");
		}
		this->parent->cont->get_controller()->save();
		this->parent->populate();
	}
	catch (...) {
		QMessageBox::critical(this, "Error", "Couldn't remove the trench coat");
	}
}

