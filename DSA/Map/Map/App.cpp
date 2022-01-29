#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"


#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();
	cout << "Test new functionality\n";
	test_new();
	cout << "That's all!" << endl;
	return 0;
}


