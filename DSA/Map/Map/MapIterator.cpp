#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->curr_poz = 0;
	while (this->curr_poz < this->map.m && this->map.T[this->curr_poz] == NULL) {
		this->curr_poz++;
	}
	if (this->curr_poz < this->map.m) {
		this->curr_list = this->map.T[this->curr_poz];
	}
	else {
		this->curr_list = NULL;
	}
}//BC=Theta(1), when there is an elem in T[0]; WC=Theta(m), when the only elem is found in the last list (T[m-1]) or the table is empty; Total=Theta(1), load factor


void MapIterator::first() {
	this->curr_poz = 0;
	while (this->curr_poz < this->map.m && this->map.T[this->curr_poz] == NULL) {
		this->curr_poz++;
	}
	if (this->curr_poz < this->map.m) {
		this->curr_list = this->map.T[this->curr_poz];
	}
	else {
		this->curr_list = NULL;
	}
}//BC=Theta(1), when there is an elem in T[0]; WC=Theta(m), when the only elem is found in the last list (T[m-1]) or the table is empty; Total=Theta(1), load factor


void MapIterator::next() {
	if (!valid()) {
		throw exception();
	}
	if (this->curr_list->next == NULL) {
		this->curr_poz++;
		while (this->curr_poz < this->map.m && this->map.T[this->curr_poz] == NULL) {
			this->curr_poz++;
		}
		if (this->curr_poz < this->map.m) {
			this->curr_list = this->map.T[this->curr_poz];
		}
	}
	else {
		this->curr_list = this->curr_list->next;
	}
}//BC=Theta(1), when there are remaining nodes in the current list; WC=Theta(m), when the current node is in T[0] and the next one is in T[m-1]; Total=Theta(1), load factor


TElem MapIterator::getCurrent(){
	if (!valid())
		throw exception();
	return this->curr_list->data;
}//BC=WC=Total=Theta(1)


bool MapIterator::valid() const {
	if(this->curr_list == NULL || this->curr_poz >= this->map.m)
		return false;
	return true;
}//BC=WC=Total=Theta(1)



