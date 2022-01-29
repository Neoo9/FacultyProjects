#include "SetIterator.h"
#include "Set.h"
#include <exception>


SetIterator::SetIterator(const Set& m) : set(m)
{
	this->curr = m.head;
}//BC=WC=Total=Theta(1)


void SetIterator::first() {
	this->curr = this->set.head;
}//BC=WC=Total=Theta(1)


void SetIterator::next() {
	if (!valid()) {
		throw std::exception();
	}
	this->curr = this->set.next[this->curr];
}//BC=WC=Total=Theta(1)


TElem SetIterator::getCurrent(){
	if (!valid()) {
		throw std::exception();
	}
	return this->set.elems[this->curr];
}//BC=WC=Total=Theta(1)

bool SetIterator::valid() const {
	if (this->curr != -1) {
		return true;
	}
	return false;
}//BC=WC=Total=Theta(1)


//Change the iterator to be able to go k steps forward.
//Add the following operation in the SetIterator class :  
//moves the current element from the iterator k steps forward, or makes the iterator invalid if there are less than k elements left in the Set. 
//throws an exception if the iterator is invalid or if k is negative or zero void jumpForward(int k);
void SetIterator::jumpForward(int k) {
	if (k <= 0)
		throw std::exception();
	for (int i = 0; i < k; i++)
		this->next();
}//BC=Theta(1), when k is invalid or the iterator was already invalid; WC=Theta(k), when the iterator remains valid after k steps; Total=O(k)


