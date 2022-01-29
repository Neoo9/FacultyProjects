#include "Operations.h"

Add_Operation::Add_Operation(Repository* repo, TrenchCoat tc) : repo{ repo }, tc{ tc } {}

void Add_Operation::undo(){
	this->repo->remove_repo(tc);
}

void Add_Operation::redo(){
	this->repo->add_repo(tc);
}

Delete_Operation::Delete_Operation(Repository* repo, TrenchCoat tc) :repo{ repo }, tc{ tc } {}

void Delete_Operation::undo(){
	this->repo->add_repo(tc);
}

void Delete_Operation::redo(){
	this->repo->remove_repo(tc);
}

Update_Operation::Update_Operation(Repository* repo, TrenchCoat tc1, TrenchCoat tc2) :repo{ repo }, tc1{ tc1 }, tc2{ tc2 } {}

void Update_Operation::undo(){
	this->repo->update_repo(tc2, tc1);
}

void Update_Operation::redo(){
	this->repo->update_repo(tc1, tc2);
}
