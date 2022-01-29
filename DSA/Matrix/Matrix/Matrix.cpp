#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	this->root = NULL;
	this->nrlines = nrLines;
	this->nrcols = nrCols;
}//BC=WC=Total=Theta(1)


int Matrix::nrLines() const {
	return this->nrlines;
}//BC=WC=Total=Theta(1)


int Matrix::nrColumns() const {
	return this->nrcols;
}//BC=WC=Total=Theta(1)


TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->nrlines || j < 0 || j >= this->nrcols)
		throw exception();
	BTNode* curr = this->root;
	bool found = false;
	while (curr != NULL && !found) {
		if (curr->elem.line == i && curr->elem.column == j)
			found = true;
		else {
			if (curr->elem.line < i)
				curr = curr->right;
			else if (curr->elem.line > i)
				curr = curr->left;
			else {
				if (curr->elem.column < j)
					curr = curr->right;
				else
					curr = curr->left;
			}
		}
	}
	if (found)
		return curr->elem.value;
	return NULL_TELEM;
}//BC=Theta(1), elem is the root; WC=Theta(n), elem is the last node in a degenerated tree; Total=O(n)

TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->nrlines || j < 0 || j >= this->nrcols)
		throw exception();
	if (this->root == NULL) {
		this->root = init_node(i, j, e);
		return NULL_TELEM;
	}
	BTNode* prev = NULL;
	BTNode* curr = this->root;
	bool found = false;
	bool root = false;
	while (curr != NULL && !found) {
		if (curr->elem.line == i && curr->elem.column == j)
			found = true;
		else {
			prev = curr;
			if (curr->elem.line < i)
				curr = curr->right;
			else if (curr->elem.line > i)
				curr = curr->left;
			else {
				if (curr->elem.column < j)
					curr = curr->right;
				else
					curr = curr->left;
			}
		}
	}
	if (curr == this->root)
		root = true;
	if (found) {
		TElem old = curr->elem.value;
		if (e != NULL_TELEM) { // old != 0, new != 0
			curr->elem.value = e;
			return old;
		}
		else {  // old != 0, new == 0
			if (curr->left == NULL && curr->right == NULL) { // 0 descendants
				if (prev != NULL) {
					if (prev->left == curr)
						prev->left = NULL;
					else
						prev->right = NULL;
				}
				delete curr;
				if (root)
					this->root = NULL;
				return old;
			}
			if (curr->left != NULL && curr->right != NULL) {  // 2 descendants
				BTNode* min = curr->right;
				find_min(curr->right, min);
				if (root) {
					min->left = this->root->left;
					this->root = min;
				}
				else {
					if (prev != NULL) {
						if (prev->left == curr)
							prev->left = min;
						else
							prev->right = min;
						min->left = curr->left;
					}
				}
				delete curr;
				return old;
			}  
			if (root) {// 1 descendant
				this->root = curr->left != NULL ? curr->left : curr->right;
			}
			else {
				if (prev != NULL) {
					if (prev->left == curr)
						prev->left = curr->left != NULL ? curr->left : curr->right;
					else
						prev->right = curr->left != NULL ? curr->left : curr->right;
				}
			}
			delete curr;
			return old;
		}
	}
	else {
		if (e == NULL_TELEM)  // old == 0, new == 0
			return NULL_TELEM;
		BTNode* node = new BTNode(); // old == 0, new != 0
		node = init_node(i, j, e);
		if (prev->elem.line < i)
			prev->right = node;
		else if (prev->elem.line > i)
			prev->left = node;
		else {
			if (prev->elem.column < j)
				prev->right = node;
			else
				prev->left = node;
		}
		return NULL_TELEM;
	}
}//BC=Theta(1), when adding the root; WC=Theta(n), elem is the last node in a degenerated tree; Total=O(n)

BTNode* Matrix::init_node(int i, int j, TElem e){
	BTNode* node = new BTNode();
	node->elem.value = e;
	node->elem.line = i;
	node->elem.column = j;
	node->left = NULL;
	node->right = NULL;
	node->nr_left = 0;
	return node;
}//BC=WC=Total=Theta(1)

void Matrix::find_min(BTNode* node, BTNode* min){
	BTNode* curr = node;
	while (curr->left != NULL) {
		curr = curr->left;
	}
	min = curr;
}//BC=Theta(1), when node has no left subtree; WC=Theta(n), all nodes of the left subtree are parsed; Total=O(n) (here n=number of nodes in the left subtree)

//sets all the values from the main diagonal to the value elem.  
//throws an exception if it is not a square matrix. 
void Matrix::setMainDiagonal(TElem elem) {
	if (this->nrlines != this->nrcols)
		throw exception();
	for (int i = 0; i < this->nrlines; i++)
		modify(i, i, elem);
}//BC=Theta(l*logn), when the tree is balanced; WC=Theta(l*n), when the tree is degenerated; Total=O(l*n), l=nr. of lines

