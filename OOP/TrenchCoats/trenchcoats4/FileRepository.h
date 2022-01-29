#pragma once
#include "Repository.h"

class FileRepository : public Repository {
private:
	std::string file_name;
public:
	FileRepository(std::vector<TrenchCoat>* dv, std::string file_name);
	~FileRepository();
	std::string get_file() { return this->file_name; }
	/**
	* Loads data from a file.
	*/
	void load();
	/**
	 * Saves data to a file.
	 */
	void save();
};
