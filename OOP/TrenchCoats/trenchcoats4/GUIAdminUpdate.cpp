#include "GUIAdminUpdate.h"
#include "qformlayout.h"
#include "qlineedit.h"
#include "qmessagebox.h"

GUIAdminUpdate::GUIAdminUpdate(GUIAdmin* par) : parent{ par } {
	this->init();
	this->connect();
}

void GUIAdminUpdate::init(){
	this->setAttribute(Qt::WA_DeleteOnClose);
	QWidget* main = new QWidget();
	QFormLayout* form1 = new QFormLayout();
	this->name1 = new QLineEdit();
	this->size1 = new QLineEdit();
	this->colour1 = new QLineEdit();
	this->price1 = new QLineEdit();
	this->quantity1 = new QLineEdit();
	form1->addRow("Name", this->name1);
	form1->addRow("Size", this->size1);
	form1->addRow("Colour", this->colour1);
	form1->addRow("Price", this->price1);
	form1->addRow("Quantity", this->quantity1);
	QFormLayout* form2 = new QFormLayout();
	this->name2 = new QLineEdit();
	this->size2 = new QLineEdit();
	this->colour2 = new QLineEdit();
	this->price2 = new QLineEdit();
	this->quantity2 = new QLineEdit();
	this->photograph2 = new QLineEdit();
	form2->addRow("New name", this->name2);
	form2->addRow("New size", this->size2);
	form2->addRow("New colour", this->colour2);
	form2->addRow("New price", this->price2);
	form2->addRow("New quantity", this->quantity2);
	form2->addRow("New photograph", this->photograph2);
	this->button = new QPushButton("Update");
	form1->addRow(this->button);
	QGridLayout* grid = new QGridLayout();
	grid->addLayout(form1, 0, 0);
	grid->addLayout(form2, 0, 1);
	main->setLayout(grid);
	main->show();
}

void GUIAdminUpdate::connect(){
	QObject::connect(this->button, &QPushButton::clicked, this, &GUIAdminUpdate::update_gui);
}

void GUIAdminUpdate::update_gui(){
	try {
		using namespace std;
		string name1 = this->name1->text().toStdString();
		string size1 = this->size1->text().toStdString();
		string colour1 = this->colour1->text().toStdString();
		double price1 = stod(this->price1->text().toStdString());
		int quantity1 = stod(this->quantity1->text().toStdString());
		TrenchCoat tc1(name1, size1, colour1, price1, quantity1, "");
		string name2 = this->name2->text().toStdString();
		string size2 = this->size2->text().toStdString();
		string colour2 = this->colour2->text().toStdString();
		double price2 = stod(this->price2->text().toStdString());
		int quantity2 = stod(this->quantity2->text().toStdString());
		string photograph2 = this->photograph2->text().toStdString();
		TrenchCoat tc2(name2, size2, colour2, price2, quantity2, photograph2);
		int code = this->parent->cont->update_cont(tc1, tc2);
		if (!code) {
			QMessageBox::information(this, "Success", "Trench coat was updated");
		}
		this->parent->cont->get_controller()->save();
		this->parent->populate();
	}
	catch (...) {
		QMessageBox::critical(this, "Error", "Couldn't update the trench coat");
	}
}