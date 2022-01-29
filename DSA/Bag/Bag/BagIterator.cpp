#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = 0;
	this->currentfreq = 1;
}

void BagIterator::first() {
	this->current = 0;
	this->currentfreq = 1;
}//BC=WC=Total=Theta(1)


void BagIterator::next() {
	if (!valid()) {
		throw exception();
	}
	if (this->currentfreq == this->bag.frequency[this->current]) {
		this->current++;
		this->currentfreq = 1;
	}
	else {
		this->currentfreq++;
	}
}//BC=WC=Total=Theta(1)


bool BagIterator::valid() const {
	if (this->current < this->bag.length)
		return true;
	return false;
}//BC=WC=Total=Theta(1)


TElem BagIterator::getCurrent() const
{	
	if (!valid()) {
		throw exception();
	}
	return this->bag.elements[this->current];
}//BC=WC=Total=Theta(1)
