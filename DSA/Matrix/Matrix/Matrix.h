#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Sparse {
public:
	int line;
	int column;
	TElem value;
};

class BTNode {
public:
	Sparse elem;
	BTNode* left;
	BTNode* right;
	int nr_left;
};

class Matrix {

private:
	BTNode* root;
	int nrlines;
	int nrcols;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);
	BTNode* init_node(int i, int j, TElem e);
	void find_min(BTNode* node, BTNode* min);
	void setMainDiagonal(TElem elem);
};

