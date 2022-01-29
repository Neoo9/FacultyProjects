#include "HTMLRepository.h"
#include <fstream>
#include <iostream>
#include <iomanip>

HTMLRepository::HTMLRepository(std::vector<TrenchCoat>* dv, std::string file_name) :Repository(dv), file_name(file_name) {}

HTMLRepository::~HTMLRepository() = default;

void HTMLRepository::load() {
	std::ofstream f(file_name);
	f << "";
	f.close();
}

void HTMLRepository::save() {
	std::ofstream f(file_name);
	f << "<!DOCTYPE html>\n<html>\n<head>\n\t<title>Basket</title>\n</head>\n<body>\n<table border=\"1\">\n";
	f << "\t<tr>\n\t\t<td>Name</td>\n\t\t<td>Size</td>\n\t\t<td>Colour</td>\n\t\t<td>Price</td>\n\t\t<td>Photograph link</td>\n\t</tr>\n";
	for (TrenchCoat tc : *repo) {
		f << "\t<tr>\n";
		f << "\t\t<td>"<<tc.get_name() << "</td>\n";
		f << "\t\t<td>" << tc.get_size() << "</td>\n";
		f << "\t\t<td>" << tc.get_colour() << "</td>\n";
		f << "\t\t<td>" << std::fixed << std::setprecision(2) << tc.get_price() << "</td>\n";
		f << "\t\t<td><a href=\"" << tc.get_photograph() << "\">Link</a></td>\n\t</tr>\n";
	}
	f << "</table>\n</body>\n</html>";
	f.close();
}
