
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
	sll.head = NULL;
	rel = r;
}//BC=WC=Total=Theta(1)


void PriorityQueue::push(TElem e, TPriority p) {
	SLLNode* new_node = new SLLNode();
	new_node->data.first = e;
	new_node->data.second = p;
	if (sll.head == NULL) { 
		sll.head = new_node;
		new_node->next = NULL;
		return;
	}
	SLLNode* curr = sll.head;
	SLLNode* prev = NULL;
	while (!rel(p, curr->data.second) && curr->next != NULL) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == sll.head && rel(p, curr->data.second)) {
		new_node->next = curr;
		sll.head = new_node;
		return;
	}
	if (curr != sll.head && rel(p, curr->data.second)) {
		prev->next = new_node;
		new_node->next = curr;
		return;
	}
	new_node->next = curr->next;
	curr->next = new_node;
}//BC=Theta(1), when modifying the head; WC=Theta(n), when adding at the end; Total=O(n)

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	if (sll.head == NULL)
		throw exception();
	return sll.head->data;
}//BC=WC=Total=Theta(1)

Element PriorityQueue::pop() {
	if (sll.head == NULL)
		throw exception();
	Element data = sll.head->data;
	SLLNode* next = sll.head->next;
	delete sll.head;
	sll.head = next;
	return data;
}//BC=WC=Total=Theta(1)

bool PriorityQueue::isEmpty() const {
	if (sll.head == NULL)
		return true;
	return false;
}//BC=WC=Total=Theta(1)


PriorityQueue::~PriorityQueue() {
	SLLNode* curr = sll.head;
	SLLNode* next = NULL;
	while (curr != NULL) {
		next = curr->next;
		delete curr;
		curr = next;
	}
	sll.head = NULL;
}//BC=WC=Total=Theta(n), since we're always parsing the entire list


//increases the priority of an element  
//returns the old priority of elem or if elem is not in the PriorityQueue, return -1
//if the new priority is “less than” (considering the relation) the old one, throw an exception

TPriority PriorityQueue::increasePriority(TElem elem, TPriority newPriority) {
	SLLNode* curr = sll.head;
	SLLNode* prev = NULL;
	while (curr != NULL && curr->data.first != elem) {
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL) {
		return -1;
	}
	if (!rel(newPriority, curr->data.second)) {
		throw exception();
	}
	if (curr != sll.head)
		prev->next = curr->next;
	else
		sll.head = curr->next;
	TPriority old = curr->data.second;
	delete curr;
	this->push(elem, newPriority);
	return old;
}//BC=Theta(1), when modifying the head; WC=Theta(n), when modifying the last element and its position in the queue doesn't change; Total=O(n)
