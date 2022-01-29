#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->capacity = 10;
	this->length = 0;
	this->elements = new TElem[this->capacity];
	this->frequency = new int[this->capacity];
	this->nrfreq = 0;
}


void Bag::add(TElem elem) {
	for(int i = 0; i < this->length; i++)
		if (this->elements[i] == elem) {
			this->frequency[i]++;
			this->nrfreq++;
			return;
		}
	if (this->length == this->capacity) {
		this->capacity = (int)(this->capacity * 1.5);
		TElem* new_elem = new TElem[capacity];
		int* new_freq = new int[capacity];
		for (int i = 0; i < this->length; i++) {
			new_elem[i] = this->elements[i];
			new_freq[i] = this->frequency[i];
		}
		delete[] this->elements;
		delete[] this->frequency;
		this->elements = new_elem;
		this->frequency = new_freq;
	}
	this->elements[this->length] = elem;
	this->frequency[this->length++] = 1;
	this->nrfreq++;
}//BC=Theta(1) - when elem is on the first position, WC=Theta(n) - when elem is not already in the bag, Total=O(n)


bool Bag::remove(TElem elem) {
	for (int i = 0; i < this->length; i++) {
		if (this->elements[i] == elem) {
			if (this->frequency[i] > 1) {
				this->frequency[i]--;
				this->nrfreq--;
				return true;
			}
			this->elements[i] = this->elements[this->length - 1];
			this->frequency[i] = this->frequency[this->length - 1];
			this->length--;
			this->nrfreq--;
			return true;
		}
	}
	return false; 
}//BC=Theta(1) - when elem is on the first position, WC=Theta(n) - when elem is not in the bag, Total=O(n)


bool Bag::search(TElem elem) const {
	for (int i = 0; i < this->length; i++) {
		if (this->elements[i] == elem)
			return true;
	}
	return false; 
}//BC=Theta(1) - when elem is on the first position, WC=Theta(n) - when elem is not in the bag, Total=O(n)

int Bag::nrOccurrences(TElem elem) const {
	for (int i = 0; i < this->length; i++) {
		if (this->elements[i] == elem)
			return this->frequency[i];
	}
	return 0;
}//BC = Theta(1) - when elem is on the first position, WC = Theta(n) - when elem is not in the bag, Total=O(n)


int Bag::size() const {
	return this->nrfreq;
}//BC=WC=Total=Theta(1)


bool Bag::isEmpty() const {
	if (!this->length)
		return true;
	return false;
}//BC=WC=Total=Theta(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	delete[] this->elements;
	delete[] this->frequency;
}//BC=WC=Total=Theta(1)

//adds nr occurrences of elem in the Bag (if elem was not in the bag, it will still be added). 
//throws an exception if nr is negative 
void Bag::addOccurrences(int nr, TElem elem) {
	if (nr < 0)
		throw exception();
	for (int i = 1; i <= nr; i++) {
		add(elem);
	}
}//BC=Theta(nr) - when we add nr occurences to the very first element, WC=Theta(nr*n) - when we add nr occurences to the last element, Total=O(nr*n)
