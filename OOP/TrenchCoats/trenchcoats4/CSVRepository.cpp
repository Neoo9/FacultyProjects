#include "CSVRepository.h"
#include <fstream>
#include <iostream>
#include <iomanip>

CSVRepository::CSVRepository(std::vector<TrenchCoat>* dv, std::string file_name) :Repository(dv), file_name(file_name) {}

CSVRepository::~CSVRepository() = default;

void CSVRepository::load() {
	std::ofstream f(file_name);
	f << "";
	f.close();
}

void CSVRepository::save() {
	std::ofstream f(file_name);
	for (TrenchCoat tc : *repo) {
		f << tc.get_name() << ",";
		f << tc.get_size() << ",";
		f << tc.get_colour() << ",";
		f << std::fixed << std::setprecision(2) << tc.get_price() << ",";
		f << tc.get_photograph() << '\n';
	}
	f.close();
}
