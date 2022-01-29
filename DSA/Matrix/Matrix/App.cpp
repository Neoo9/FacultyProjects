
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {
	cout << "Test new functionality\n";
	test_new();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
}