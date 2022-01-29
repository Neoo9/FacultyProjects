#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"


void testAll() { //call each function to see if it is implemented
	Map m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
	assert(m.size() == 5);
	assert(m.search(10) == 10);
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);


	TElem e;
	MapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
	assert(s1 == 19);
	assert(s2 == 19);

}

void test_new() {
	Map m1, m2;
	m1.add(5, 5);
	m1.add(7, 7);
	m1.add(9, 9);
	m1.add(11, 11); // 5 7 9 11
	m2.add(2, 2);
	m2.add(5, 2);
	m2.add(7, 2);
	m2.add(10, 2); // 2 5 7 10
	assert(m1.addIfNotPresent(m2) == 2);
	m2.remove(7);
	m2.remove(2); // 5 10
	assert(m1.addIfNotPresent(m2) == 1);
	assert(m2.addIfNotPresent(m1) == 3);
	m1.add(10, 10); // 5 7 9 10 11
	assert(m2.addIfNotPresent(m1) == 3);
}


