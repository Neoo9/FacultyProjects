#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->m = 13;
	this->length = 0;
	this->T = new Node*[this->m];
	for (int i = 0; i < this->m; i++) {
		this->T[i] = NULL;
	}
}//BC=WC=Total=Theta(m)

Map::~Map() {
	for (int i = 0; i < this->m; i++) {
		Node* curr = this->T[i];
		Node* next = NULL;
		while (curr != NULL) {
			next = curr->next;
			delete curr;
			curr = next;
		}
	}
	delete[] this->T;
}//BC=WC=Total=Theta(m*L)

void Map::rehash() {
	int old_m = this->m;
	Node** old_T = this->T;
	this->m = this->m * 2 % 2 ? this->m * 2 : this->m * 2 + 1;
	this->length = 0;
	Node** new_T = new Node * [this->m];
	this->T = new_T;
	for (int i = 0; i < this->m; i++) {
		this->T[i] = NULL;
	}
	for (int i = 0; i < old_m; i++) {
		Node* curr = old_T[i];
		Node* next = NULL;
		while (curr != NULL) {
			next = curr->next;
			this->add(curr->data.first, curr->data.second);
			delete curr;
			curr = next;
		}
	}
	delete[] old_T;
}//BC=Theta(m), WC=Theta(m+L), Total=O(m+L)

TValue Map::add(TKey c, TValue v){
	int poz = this->h(c);
	Node* curr = this->T[poz];
	Node* prev = NULL;
	Node* new_node = new Node();
	new_node->data.first = c;
	new_node->data.second = v;
	if (curr == NULL) {
		new_node->next = NULL;
		this->T[poz] = new_node;
		this->length++;
		if ((float)this->length / this->m > 0.7)
			this->rehash();
		return NULL_TVALUE;
	}
	while (curr != NULL && curr->data.first != c) {
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL) {
		delete new_node;
		int old = curr->data.second;
		curr->data.second = v;
		return old;
	}
	prev->next = new_node;
	new_node->next = curr;
	this->length++;
	if ((float)this->length / this->m > 0.7)
		this->rehash();
	return NULL_TVALUE;
}//BC=Theta(1), when the list at T[poz] is empty; WC=Theta(L), when the elem is not in the list at T[poz] (no rehash); Total=Theta(1), load factor

TValue Map::search(TKey c) const{
	int poz = this->h(c);
	Node* curr = this->T[poz];
	while (curr != NULL && curr->data.first != c) {
		curr = curr->next;
	}
	if (curr != NULL) {
		return curr->data.second;
	}
	return NULL_TVALUE;
}//BC=Theta(1), when elem is at the beginning of the list; WC=Theta(L), when elem is not in the list; Total=Theta(1), load factor

TValue Map::remove(TKey c){
	int poz = this->h(c);
	Node* curr = this->T[poz];
	Node* prev = NULL;
	while (curr != NULL && curr->data.first != c) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) {
		return NULL_TVALUE;
	}
	int val = curr->data.second;
	if (prev != NULL) {
		prev->next = curr->next;
	}
	else {
		this->T[poz] = this->T[poz]->next;
	}
	delete curr;
	this->length--;
	return val;
}//BC=Theta(1), when elem is at the beginning of the list; WC=Theta(L), when elem is not in the list; Total=Theta(1), load factor


int Map::size() const {
	return this->length;
}//BC=WC=Total=Theta(1)

bool Map::isEmpty() const{
	if (!this->length)
		return true;
	return false;
}//BC=WC=Total=Theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}//BC=WC=Total=Theta(1)

//adds all pairs from m whose key is not in the Map already.  
//returns the number of added pairs 
int Map::addIfNotPresent(Map& m) {
	MapIterator it = m.iterator();
	int nr = 0;
	TElem elem;
	while (it.valid()) {
		elem = it.getCurrent();
		if (search(elem.first) == NULL_TVALUE) {
			nr++;
		}
		it.next();
	}
	return nr;
}//BC=Theta(n), each elem is found at the beginning of their list; WC=Theta(n*L), for each elem, which is found at the end, each list must be parsed completely; Total=Theta(1), load factor



