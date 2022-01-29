#include "Subject.h"

void Subject::add_observer(Observer* obs){
	this->observers.push_back(obs);
}

void Subject::notify_all(){
	for (auto obs : this->observers) {
		obs->update();
	}
}
