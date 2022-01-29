#pragma once
#include <exception>
#include <string>

class ValidatorException : public std::exception{
private:
	std::string msg;
public:
	ValidatorException(std::string msg);
	//~ValidatorException();
	/**
	 * what() method overloading.
	 */
	virtual const char* what() const throw() { return msg.c_str(); }
};

class Validator {
public:
	/**
	* Function that validates given user input.
	*
	* \param name: Given name
	* \param size: Given size
	* \param colour: Given colour
	* \param price: Given price
	* \param quantity: Given quantity
	*/
	void validator(std::string name, std::string size, std::string colour, double price, int quantity);
};
