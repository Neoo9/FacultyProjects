#include "Repository.h"
#include <fstream>
#include <sstream>
#include <iomanip>

Repository::Repository(std::vector<TrenchCoat>* dv):repo(dv){}

Repository::~Repository() = default;

int Repository::add_repo(TrenchCoat tc) {
	std::vector<TrenchCoat>::iterator it11 = repo->begin();
	std::vector<TrenchCoat>::iterator it = std::find_if(repo->begin(), repo->end(), [&](TrenchCoat tc2) {return tc == tc2; });
	if (it != repo->end()) { // if it exists, then we increment the already existing quantity, while keeping the other data intact
		TrenchCoat* tcc = new TrenchCoat(tc.get_name(), tc.get_size(), tc.get_colour(), tc.get_price(), tc.get_quantity() + it->get_quantity(), tc.get_photograph());
		*it = tcc;
		return 1;
	}
	repo->push_back(tc);  // if not, we simply add it
	return 0;
}

int Repository::remove_repo(TrenchCoat tc) {
	std::vector<TrenchCoat>::iterator it = std::find_if(repo->begin(), repo->end(), [&](TrenchCoat tc2) {return tc == tc2; });
	if (it == repo->end()) {
		throw std::invalid_argument("Trench coat doesn't exist");
	}
	if(it->get_quantity() - tc.get_quantity() <= 0)
		repo->erase(it);
	else
	{
		repo->at(std::distance(repo->begin(), it)).set_quantity(it->get_quantity() - tc.get_quantity());
	}
	return 0;
}

int Repository::update_repo(TrenchCoat tc1, TrenchCoat tc2) {
	std::vector<TrenchCoat>::iterator it = std::find_if(repo->begin(), repo->end(), [&](TrenchCoat tc2) {return tc1 == tc2; });
	if (it == repo->end()) {
		throw std::invalid_argument("Trench coat doesn't exist");
	}
	*it = tc2;
	return 0;
}



