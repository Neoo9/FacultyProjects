#pragma once
#include "Repository.h"

class CSVRepository : public Repository {
private:
	std::string file_name;
public:
	CSVRepository(std::vector<TrenchCoat>* dv, std::string file_name);
	~CSVRepository();
	std::string get_file() { return this->file_name; }
	void load();
	void save();
};
