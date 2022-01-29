#include <assert.h>
#include <exception>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
	return;
}

void test_new(){
	Matrix m(10, 11);
	try {
		m.setMainDiagonal(2);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	Matrix mat(10, 10);
	mat.modify(0, 1, 7);
	mat.modify(2, 3, 8);
	mat.modify(9, 1, 11);
	mat.modify(5, 0, 3);
	mat.modify(2, 2, 1);
	mat.setMainDiagonal(1);
	assert(mat.element(0, 0) == 1);
	assert(mat.element(9, 9) == 1);
}
