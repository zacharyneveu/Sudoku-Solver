#pragma once

#include <set>
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

//Represents a cell in the soduku puzzle.
class Cell {
private:
	//Value of the cell -1 for not unknown.
	int value;
	//Possible Potential Values of the cell
	set<int> poss;

public:
	int getValue() { return value; }
	void setValue(int value) { this->value = value; }
	int getNumPossible() { return poss.size(); }
	int removePossibily(int value) { poss.erase(value); }
	int addPossibily(int value) { poss.insert(value); }
	Cell(int vaule) { this->value = value; }
	Cell() { this->value = -1; }
	void clear() {
		value = -1;
		poss.clear();
	}
};