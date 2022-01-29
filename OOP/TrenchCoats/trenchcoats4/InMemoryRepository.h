#pragma once
#include "Repository.h"

class InMemoryRepository : public Repository {
public:
	InMemoryRepository(std::vector<TrenchCoat>* dv);
	~InMemoryRepository();
	void load();
	void save();
};
