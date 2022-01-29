#pragma once
#include "TrenchCoat.h"

template<typename T>
class DynamicVector
{
private:
	T* elements;
	int length;
	int capacity;
	void resize();
public:
	/**
	 * Constructor for DynamicVector.
	 * 
	 */
	DynamicVector();
	/**
	 * Destructor for DynamicVector.
	 * 
	 */
	~DynamicVector();
	/**
	 * Getter for the elements of DynamicVector.
	 * 
	 * \return: Pointer to the elements 
	 */
	T* get_elements() { return this->elements; }
	/**
	 * Getter for the length of DynamicVector.
	 * 
	 * \return: The length
	 */
	int get_length() { return this->length; }
	/**
	 * Getter for the capacity of DynamicVector.
	 * 
	 * \return: The capacity
	 */
	int get_capacity() { return this->capacity; }
	/**
	 * Setter for the length.
	 * 
	 * \param val: New value
	 */
	void set_length(int val) { this->length = val; }
	/**
	 * Function that adds a new element to the array.
	 * 
	 * \param tc: Given trench coat
	 */
	void add(T tc);
	/**
	 * Function that removes an element from the array.
	 * 
	 * \param tc: Given trench coat
	 * \return: true, if the remove was successful , false otherwise (i.e. the element doesn't exist)
	 */
	bool remove(T tc);
	/**
	 * Function that updates an element from the array.
	 * 
	 * \param tc1: Trench coat to be updated
	 * \param tc2: New trench coat
	 * \return: true, if the update was successful, false otherwise (i.e. the element doesn't exist)
	 */
	bool update(T tc1, T tc2);
	/**
	 * Searches for an element in the array.
	 * 
	 * \param tc: Given trench coat
	 * \return: true, if the element exists, false otherwise
	 */
	bool search(T tc);
};

template<typename T>
DynamicVector<T>::DynamicVector() {
	this->capacity = 10;
	this->length = 0;
	this->elements = new T[this->capacity];
}

template<typename T>
DynamicVector<T>::~DynamicVector() {
	delete[] this->elements;
}

template<typename T>
void DynamicVector<T>::resize() {
	this->capacity = (int)(this->capacity * 1.5);
	T* new_elem = new T[this->capacity];
	for (int i = 0; i < this->length; i++) {
		new_elem[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = new_elem;
}

template<typename T>
void DynamicVector<T>::add(T tc) {
	if (this->length == this->capacity) // if the array is full, we resize
		resize();
	this->elements[this->length] = tc;
	this->length++;
}

template<typename T>
bool DynamicVector<T>::remove(T tc) {
	for (int i = 0; i < this->length; i++) {
		if (this->elements[i] == tc) {
			if (this->elements[i].get_quantity() > 1) { // if we have duplicates, we decrement the quantity
				this->elements[i].set_quantity(this->elements[i].get_quantity() - 1);
				return true;
			} // otherwise, we remove the entry entirely
			this->elements[i] = this->elements[this->length - 1];
			this->length--;
			return true;
		}
	}
	return false;
}

template<typename T>
bool DynamicVector<T>::update(T tc1, T tc2) {
	for (int i = 0; i < this->length; i++) {
		if (this->elements[i] == tc1) {
			this->elements[i].set_photograph(tc2.get_photograph());
			this->elements[i].set_name(tc2.get_name());
			this->elements[i].set_colour(tc2.get_colour());
			this->elements[i].set_price(tc2.get_price());
			this->elements[i].set_quantity(tc2.get_quantity());
			this->elements[i].set_size(tc2.get_size());
			return true;
		}
	}
	return false;
}

template<typename T>
bool DynamicVector<T>::search(T tc) {
	for (int i = 0; i < this->length; i++) {
		if (this->elements[i] == tc) {
			return true;
		}
	}
	return false;
}
