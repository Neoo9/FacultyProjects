#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {
	testAll();
	cout << "Short tests over" << endl;
	testAddOccurences();
	cout << "Test add occurences over" << endl;
	testAllExtended();
	cout << "All test over" << endl;
}