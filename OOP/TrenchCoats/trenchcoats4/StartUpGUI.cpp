#include "StartUpGUI.h"
#include <QGridLayout>
#include <QGroupBox>
#include "GUIAdmin.h"
#include "GUIUser.h"

StartUpGUI::StartUpGUI(int* option_1, int* option_2) : option_1{ option_1 }, option_2{ option_2 } {
	this->init();
	this->connect();
}

void StartUpGUI::init(){
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->main = new QWidget();
	QGridLayout* grid = new QGridLayout();
	QGroupBox* mode = new QGroupBox("Login mode");
	QHBoxLayout* hboxmode = new QHBoxLayout;
	this->admin_button = new QRadioButton("Admin");
	this->user_button = new QRadioButton("User");
	this->admin_button->setChecked(true);
	hboxmode->addWidget(this->admin_button);
	hboxmode->addWidget(this->user_button);
	mode->setLayout(hboxmode);
	QGroupBox* repo = new QGroupBox("Repository type");
	QHBoxLayout* hboxrepo = new QHBoxLayout;
	this->csv_button = new QRadioButton("CSV");
	this->html_button = new QRadioButton("HTML");
	this->csv_button->setChecked(true);
	hboxrepo->addWidget(this->csv_button);
	hboxrepo->addWidget(this->html_button);
	repo->setLayout(hboxrepo);
	this->start = new QPushButton("Start application");
	QWidget* mode_selection = new QWidget();
	mode_selection->setLayout(hboxmode);
	grid->addWidget(mode_selection, 0, 0, 1, 2);
	QWidget* repo_selection = new QWidget();
	repo_selection->setLayout(hboxrepo);
	grid->addWidget(repo_selection, 1, 0, 1, 2);
	grid->addWidget(this->start, 2, 0, 1, 2);
	this->main->setLayout(grid);
	this->main->show();
}

void StartUpGUI::connect() {
	QObject::connect(this->start, &QPushButton::clicked, [this]() {
		*option_1 = this->csv_button->isChecked() ? 0 : 1;
		*option_2 = this->admin_button->isChecked() ? 0 : 1;
		this->main->close();
		});
}
