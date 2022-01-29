#include "Validator.h"
#include <stdexcept>

ValidatorException::ValidatorException(std::string msg) : msg(msg) {}
//ValidatorException::~ValidatorException() = default;

void Validator::validator(std::string name, std::string size, std::string colour, double price, int quantity){
	if (price <= 0) {
		throw ValidatorException("Invalid price value");
	}
	if (quantity <= 0) {
		throw ValidatorException("Invalid quantity value");
	}
	if (std::string::npos != size.find_first_of("0123456789") || std::string::npos == size.find_first_of("XSLM")) {
		throw ValidatorException("Invalid size value");
	}
	if (std::string::npos != colour.find_first_of("0123456789")) {
		throw ValidatorException("Invalid colour value");
	}
}
