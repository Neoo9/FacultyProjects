#pragma once
#include "Observer.h"
#include <vector>
using namespace std;

class Subject{
private:
	vector<Observer*> observers;
public:
	void add_observer(Observer* obs);
	void notify_all();
};

