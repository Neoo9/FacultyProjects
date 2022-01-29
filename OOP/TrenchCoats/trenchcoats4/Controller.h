#pragma once
#include "Repository.h"
#include "FileRepository.h"
#include "InMemoryRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "Validator.h"
#include "Operations.h"
#include <vector>

class Controller
{
private:
	Repository* cont;
	Repository* basket;
	Validator* valid;
	std::vector<Operation*> undo_admin;
	std::vector<Operation*> redo_admin;
	std::vector<Operation*> undo_user;
	std::vector<Operation*> redo_user;

public:
	/**
	 * Constructor for Controller.
	 * 
	 */
	Controller(Repository* repo, Repository* bask, Validator* valid);
	/**
	 * Destructor for Controller.
	 * 
	 */
	~Controller() = default;
	/**
	 * Getter for Controller.
	 * 
	 * \return: The controller 
	 */
	Repository* get_controller() { return cont; }
	/**
	 * Getter for shopping basket repo.
	 * 
	 * \return: Basket repo
	 */
	Repository* get_basket() { return basket; }
	/**
	 * Controller section of 'add'.
	 * Validates user input.
	 * \param name: Given name
	 * \param size: Given size
	 * \param colour: Given colour
	 * \param price: Given price
	 * \param quantity: Given quantity
	 * \param photograph: Given url to image
	 * \return 
	 */
	int add_cont(TrenchCoat tc);
	/**
	 * Controller section of 'remove'.
	 * Validates user input.
	 * \param name: Given name
	 * \param size: Given size
	 * \param colour: Given colour
	 * \param price: Given price
	 * \param quantity: Given quantity
	 * \return 
	 */
	int remove_cont(TrenchCoat tc);
	/**
	 * Controller section of 'update'.
	 * Validates user input.
	 * \param name1: Given name for first element
	 * \param size1: Given size
	 * \param colour1: Given colour
	 * \param price1: Given price
	 * \param quantity1: Given quantity
	 * \param name2: Given name for second element
	 * \param size2: Given size
	 * \param colour2: Given colour
	 * \param price2: Given price
	 * \param quantity2: Given quantity
	 * \param photograph2: Given url to image
	 * \return 
	 */
	int update_cont(TrenchCoat tc1, TrenchCoat tc2);
	/**
	 * Function that searches for trench coats of a certain size.
	 * 
	 * \param size: Given size
	 * \param repo: Repository in which the trench coats matching the size will be stored
	 */
	int user_search_coats_cont(std::string size, Repository* repo);
	/**
	 * Function that adds a trench coat to the shopping basket.
	 * 
	 * \param tc: Given trench coat
	 * \param temp: Temporary repo keeping track of the changes of the database
	 * \param total: Total price of trench coats in the basket
	 * \return 
	 */
	int add_basket(TrenchCoat tc, Repository* temp, double& total);
	void undo_op_admin();
	void redo_op_admin();
	void undo_op_user();
	void redo_op_user();
};