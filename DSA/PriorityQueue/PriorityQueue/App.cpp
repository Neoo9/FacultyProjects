#include <iostream>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;

int main() {
	testAll();
	testAllExtended();
	cout << "Test increase priority\n";
	testIncreasePriority();
	cout << "End" << endl;
}
