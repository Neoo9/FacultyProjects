#pragma once
#include <string>
#include <iostream>

class TrenchCoat
{
private:
	std::string name;
	std::string size;
	std::string colour;
	double price;
	int quantity;
	std::string photograph;
public:
	/**
	 * Default constructor for TrenchCoat.
	 * 
	 */
	TrenchCoat();
	/**
	 * Parametrized constructor for TrenchCoat.
	 * 
	 * \param name: Given name
	 * \param size: Given size
	 * \param colour: Given colour
	 * \param price: Given price
	 * \param quantity: Given quantity
	 * \param photograph: Given link to image
	 */
	TrenchCoat(std::string name, std::string size, std::string colour, double price, int quantity, std::string photograph);
	/**
	 * Copy constructor for TrenchCoat.
	 * 
	 * \param tc: Given trench coat
	 */
	TrenchCoat(const TrenchCoat* tc);
	/**
	 * Getters for TrenchCoat.
	 * 
	 * \return: Fields from TrenchCoat
	 */
	std::string get_name() { return this->name; }
	std::string get_size() { return this->size; }
	std::string get_colour() { return this->colour; }
	double get_price() { return this->price; }
	int get_quantity() { return this->quantity; }
	std::string get_photograph() { return this->photograph; }
	/**
	 * Operator overloading for TrenchCoat.
	 */
	bool operator==(TrenchCoat tc);
	TrenchCoat* operator=(const TrenchCoat* tc);
	friend std::ostream& operator<< (std::ostream& out, const TrenchCoat& tc);
	friend std::istream& operator>> (std::istream& in, TrenchCoat& tc);
	/**
	 * Setters for TrenchCoat.
	 */
	void set_name(std::string name) { this->name = name; }
	void set_size(std::string size) { this->size = size; }
	void set_colour(std::string colour) { this->colour = colour; }
	void set_price(double price) { this->price = price; }
	void set_quantity(int quantity) { this->quantity = quantity; }
	void set_photograph(std::string photograph) { this->photograph = photograph; }
	/**
	 * Converts the TrenchCoat obj to str, but without the quantity.
	 * 
	 * \return: String representation without quantity
	 */
	std::string to_string_noq();
	std::string to_string();
	~TrenchCoat() = default;
};

