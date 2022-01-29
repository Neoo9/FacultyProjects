#pragma once
#include "Repository.h"

class HTMLRepository : public Repository {
private:
	std::string file_name;
public:
	HTMLRepository(std::vector<TrenchCoat>* dv, std::string file_name);
	~HTMLRepository();
	std::string get_file() { return this->file_name; }
	void load();
	void save();
};