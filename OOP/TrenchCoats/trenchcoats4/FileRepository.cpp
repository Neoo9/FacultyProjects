#include "FileRepository.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

FileRepository::FileRepository(std::vector<TrenchCoat>* dv, std::string file_name) : Repository(dv), file_name(file_name) {}

FileRepository::~FileRepository() = default;

void FileRepository::load() {
	std::ifstream in(file_name);
	std::string line;
	while (getline(in, line)) {
		size_t pos = 0;
		std::string token, name = "", size = "", colour = "", price = "", quantity = "", photograph = "";
		while ((pos = line.find("|")) != std::string::npos) {
			token = line.substr(0, pos);
			if (!name.compare(""))
				name = token;
			else
				if (!size.compare(""))
					size = token;
				else
					if (!colour.compare(""))
						colour = token;
					else
						if (!price.compare(""))
							price = token;
						else
							if (!quantity.compare(""))
								quantity = token;
							else
								if (!photograph.compare(""))
									photograph = token;
			line.erase(0, pos + 1);
		}
		TrenchCoat tc(name, size, colour, std::stod(price), std::stoi(quantity), photograph);
		repo->push_back(tc);
	}
	in.close();
}

void FileRepository::save() {
	std::ofstream out(file_name);
	for (TrenchCoat tc : *repo) {
		std::ostringstream line;
		line << tc.get_name() << "|";
		line << tc.get_size() << "|";
		line << tc.get_colour() << "|";
		line << std::fixed << std::setprecision(2) << tc.get_price() << "|";
		line << tc.get_quantity() << "|";
		line << tc.get_photograph() << "|" << '\n';
		out << line.str();
	}
	out.close();
}

