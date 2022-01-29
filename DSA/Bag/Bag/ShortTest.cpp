#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}
}

void testAddOccurences() {
	Bag b;
	b.addOccurrences(1000, 9);
	assert(b.size() == 1000);
	b.addOccurrences(1500, 10);
	assert(b.size() == 2500);
	assert(b.nrOccurrences(9) == 1000);
	assert(b.nrOccurrences(10) == 1500);
	b.addOccurrences(2000, 9);
	assert(b.nrOccurrences(9) == 3000);
}
