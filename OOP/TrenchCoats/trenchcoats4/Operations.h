#pragma once
#include "Repository.h"

class Operation{
public:
	virtual void undo() = 0;
	virtual void redo() = 0;
};

class Add_Operation : public Operation {
private:
	Repository* repo;
	TrenchCoat tc;
public:
	Add_Operation(Repository* repo, TrenchCoat tc);
	void undo();
	void redo();
};

class Delete_Operation : public Operation {
private:
	Repository* repo;
	TrenchCoat tc;
public:
	Delete_Operation(Repository* repo, TrenchCoat tc);
	void undo();
	void redo();
};

class Update_Operation : public Operation {
private:
	Repository* repo;
	TrenchCoat tc1, tc2;
public:
	Update_Operation(Repository* repo, TrenchCoat tc1, TrenchCoat tc2);
	void undo();
	void redo();
};

