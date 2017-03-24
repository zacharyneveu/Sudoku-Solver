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
	int value;
	set<int> poss;

public:
	int getValue() { return value; }
	int getNumPossible() { return poss.size(); }
	int removePossibily(int value) { poss.erase(value); }
	int addPossibily(int value) { poss.insert(value); }
	Cell(int vaule) { this->value = value; }
};

Cell::Cell(int value) {
	this->value = value;
}