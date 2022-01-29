#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	this->cap = 10;
	this->length = 0;
	this->elems = new TElem[this->cap];
	this->next = new int[this->cap];
	this->head = -1;
	for (int i = 0; i < this->cap - 1; i++) {
		this->elems[i] = NULL_TELEM;
		this->next[i] = i + 1;
	}
	this->elems[this->cap - 1] = NULL_TELEM;
	this->next[this->cap - 1] = -1;
	this->first_empty = 0;
}//BC=WC=Total=Theta(n), always parsing the entire array


bool Set::add(TElem elem) {
	if (search(elem)) {
		return false;
	}
	if (this->first_empty == -1) {
		TElem* new_elems = new TElem[(int)(this->cap * 2)];
		int* new_next = new int[(int)(this->cap * 2)];
		for (int i = 0; i < this->cap; i++) {
			new_elems[i] = this->elems[i];
			new_next[i] = this->next[i];
		}
		for (int i = this->cap; i < (int)(this->cap * 2) - 1; i++) {
			new_next[i] = i + 1;
		}
		new_next[(int)(this->cap * 2) - 1] = -1;
		delete[] this->elems;
		delete[] this->next;
		this->elems = new_elems;
		this->next = new_next;
		this->first_empty = this->cap;
		this->cap = (int)(this->cap * 2);
	}
	if (this->head == -1) {
		this->elems[this->first_empty] = elem;
		this->head = this->first_empty;
		this->next[this->head] = -1;
		this->first_empty = this->next[this->first_empty];
		this->length++;
		return true;
	}
	this->elems[this->first_empty] = elem;
	int aux = this->first_empty;
	this->first_empty = this->next[this->first_empty];
	this->next[aux] = this->head;
	this->head = aux;
	this->length++;
	return true;
}//BC=Theta(1), when elem is already in the list (and is the head); WC=Theta(n), when elem is not in the list; Total=O(n)


bool Set::remove(TElem elem) {
	int curr = this->head;
	int prev = -1;
	while (curr != -1 && this->elems[curr] != elem) {
		prev = curr;
		curr = this->next[curr];
	}
	if (curr != -1) {
		if (curr == this->head) {
			this->head = this->next[this->head];
		}
		else {
			this->next[prev] = this->next[curr];
		}
		this->next[curr] = this->first_empty;
		this->first_empty = curr;
		this->length--;
		return true;
	}
	return false;
}//BC=Theta(1), when removing the head; WC=Theta(n), when elem is not in the list; Total=O(n)

bool Set::search(TElem elem) const {
	int curr = this->head;
	while (curr != -1 && this->elems[curr] != elem) {
		curr = this->next[curr];
	}
	if (curr != -1) {
		return true;
	}
	return false;
}//BC=Theta(1), when elem is the head; WC=Theta(n), when elem is not in the list; Total=O(n)


int Set::size() const {
	return this->length;
}//BC=WC=Total=Theta(1)


bool Set::isEmpty() const {
	if (this->length == 0) {
		return true;
	}
	return false;
}//BC=WC=Total=Theta(1)


Set::~Set() {
	delete[] this->elems;
	delete[] this->next;
}//BC=WC=Total=Theta(1)


SetIterator Set::iterator() const {
	return SetIterator(*this);
}//BC=WC=Total=Theta(1)


