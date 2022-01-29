#include "TrenchCoat.h"
#include <sstream>
#include <iomanip>

TrenchCoat::TrenchCoat() {
	this->name = "";
	this->size = "";
	this->colour = "";
	this->price = 0;
	this->quantity = 0;
	this->photograph = "";
}

TrenchCoat::TrenchCoat(std::string name, std::string size, std::string colour, double price, int quantity, std::string photograph){
	this->name = name;
	this->size = size;
	this->colour = colour;
	this->price = price;
	this->quantity = quantity;
	this->photograph = photograph;
}

TrenchCoat::TrenchCoat(const TrenchCoat* tc) {
	this->name = tc->name;
	this->size = tc->size;
	this->colour = tc->colour;
	this->price = tc->price;
	this->quantity = tc->quantity;
	this->photograph = tc->photograph;
}

bool TrenchCoat::operator==(TrenchCoat tc) {
	if (this->name.compare(tc.name))
		return false;
	if (this->size.compare(tc.size))
		return false;
	if (this->colour.compare(tc.colour))
		return false;
	if (this->price != tc.price)
		return false;
	/*if (this->quantity != tc.quantity)
		return false;*/
	return true;
}

TrenchCoat* TrenchCoat::operator=(const TrenchCoat* tc) {
	this->name = tc->name;
	this->size = tc->size;
	this->colour = tc->colour;
	this->price = tc->price;
	this->quantity = tc->quantity;
	this->photograph = tc->photograph;
	return this;
}

std::string TrenchCoat::to_string_noq() {
	std::ostringstream str;
	str << "Name: " << this->name;
	str << " | Size: " << this->size;
	str << " | Colour: " << this->colour;
	str << " | Price: " << std::fixed << std::setprecision(2) << this->price;
	return str.str();
}

std::string TrenchCoat::to_string() {
	std::ostringstream str;
	str << "Name: " << this->name;
	str << " | Size: " << this->size;
	str << " | Colour: " << this->colour;
	str << " | Price: " << std::fixed << std::setprecision(2) << this->price;
	str << " | Quantity: " << this->quantity;
	return str.str();
}

std::ostream& operator<<(std::ostream& out, const TrenchCoat& tc){
	out << "Name: " << tc.name;
	out << " | Size: " << tc.size;
	out << " | Colour: " << tc.colour;
	out << " | Price: " << std::fixed << std::setprecision(2) << tc.price;
	out << " | Quantity: " << tc.quantity;
	return out;
}

std::istream& operator>> (std::istream& in, TrenchCoat& tc) {
	using namespace std;
	string price_str, quantity_str;
	try {
		cout << "\nGive name: ";
		getline(in, tc.name);
		cout << "\nGive size: ";
		getline(in, tc.size);
		cout << "\nGive colour: ";
		getline(in, tc.colour);
		cout << "\nGive price: ";
		getline(in, price_str);
		cout << "\nGive quantity: ";
		getline(in, quantity_str);
		cout << "\nGive link to the photograph: ";
		getline(in, tc.photograph);
		tc.price = stod(price_str);
		tc.quantity = stoi(quantity_str);
	}
	catch (const invalid_argument& err){
		throw invalid_argument("Invalid input");
	}
	return in;
}
