#pragma once
#include "DynamicVector.h"
#include <vector>
#include <algorithm>

class Repository
{
protected:
	std::vector<TrenchCoat>* repo;
public:
	/**
	 * Constructor for Repository.
	 *
	 */
	Repository(std::vector<TrenchCoat>* dv);
	/**
	 * Destructor for Repository.
	 *
	 */
	virtual ~Repository();
	/**
	 * Getter for Repository.
	 *
	 * \return: The repository
	 */
	std::vector<TrenchCoat>* get_repo() { return repo; }
	/**
	 * Repository section of 'add'.
	 * Checks for the existence of the element
	 * \param tc: Given trench coat
	 * \return: 1, if the trench coat was already in the repository, 0 otherwise
	 */
	int add_repo(TrenchCoat tc);
	/**
	 * Repository section of 'remove'.
	 * Checks for the existence of the element
	 * \param tc: Given trench coat
	 * \return: 1, if the trench coat doesn't exist, 0 otherwise
	 */
	int remove_repo(TrenchCoat tc);
	/**
	 * Repository section of 'update'.
	 * Checks for the existence of the element
	 * \param tc: Given trench coat
	 * \return: 1, if the trench coat doesn't exist, 0 otherwise
	 */
	int update_repo(TrenchCoat tc1, TrenchCoat tc2);
	/**
	 * Pure virtual methods for load and save
	 * 
	 */
	virtual void load() = 0;
	virtual void save() = 0;
};

