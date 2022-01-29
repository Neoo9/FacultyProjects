#include "Controller.h"
#include <stdexcept>

Controller::Controller(Repository* repo, Repository* bask, Validator* valid):cont(repo), basket(bask), valid(valid){}

int Controller::add_cont(TrenchCoat tc){
	valid->validator(tc.get_name(), tc.get_size(), tc.get_colour(), tc.get_price(), tc.get_quantity());
	int ret = cont->add_repo(tc);
	Operation* op = new Add_Operation(this->cont, tc);
	this->undo_admin.push_back(op);
	this->redo_admin.clear();
	return ret;
}

int Controller::remove_cont(TrenchCoat tc) {
	valid->validator(tc.get_name(), tc.get_size(), tc.get_colour(), tc.get_price(), tc.get_quantity());
	int ret = cont->remove_repo(tc);
	Operation* op = new Delete_Operation(this->cont, tc);
	this->undo_admin.push_back(op);
	this->redo_admin.clear();
	return ret;
}

int Controller::update_cont(TrenchCoat tc1, TrenchCoat tc2){
	valid->validator(tc1.get_name(), tc1.get_size(), tc1.get_colour(), tc1.get_price(), tc1.get_quantity());
	valid->validator(tc2.get_name(), tc2.get_size(), tc2.get_colour(), tc2.get_price(), tc2.get_quantity());
	int ret = cont->update_repo(tc1, tc2);
	Operation* op = new Update_Operation(this->cont, tc1, tc2);
	this->undo_admin.push_back(op);
	this->redo_admin.clear();
	return ret;
}

int Controller::user_search_coats_cont(std::string size, Repository* repo) {
	int quantity = 0;
	repo->get_repo()->clear();
	for (TrenchCoat tc : *cont->get_repo()) {
		if (!tc.get_size().compare(size) || !size.compare("")) {
			repo->add_repo(tc);
			quantity += tc.get_quantity();
		}
	}
	if (!repo->get_repo()->size())
		throw std::invalid_argument("We don't have trench coats in our stock with the given size");
	return quantity;
}

int Controller::add_basket(TrenchCoat tc, Repository* temp, double& total) {
	if (tc.get_quantity() == 0)
		return 2;	
	TrenchCoat tc2;
	tc2 = tc;
	tc2.set_quantity(tc2.get_quantity() - 1);
	temp->update_repo(tc, tc2);
	int old_quantity = tc.get_quantity();
	tc.set_quantity(1);
	total += tc.get_price();
	int ret = basket->add_repo(tc);
	Operation* op = new Add_Operation(this->basket, tc);
	this->undo_user.push_back(op);
	this->redo_user.clear();
	return ret;
}

void Controller::undo_op_admin(){
	if (this->undo_admin.size() == 0) {
		throw std::exception("No more undos");
	}
	Operation* op = this->undo_admin.back();
	op->undo();
	this->undo_admin.pop_back();
	this->redo_admin.push_back(op);
}

void Controller::redo_op_admin(){
	if (this->redo_admin.size() == 0) {
		throw std::exception("No more redos");
	}
	Operation* op = this->redo_admin.back();
	op->redo();
	this->redo_admin.pop_back();
	this->undo_admin.push_back(op);
}

void Controller::undo_op_user(){
	if (this->undo_user.size() == 0) {
		throw std::exception("No more undos");
	}
	Operation* op = this->undo_user.back();
	op->undo();
	this->undo_user.pop_back();
	this->redo_user.push_back(op);
}

void Controller::redo_op_user(){
	if (this->redo_user.size() == 0) {
		throw std::exception("No more redos");
	}
	Operation* op = this->redo_user.back();
	op->redo();
	this->redo_user.pop_back();
	this->undo_user.push_back(op);
}
