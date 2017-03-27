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

public:
	int getValue() { return value; }
	void setValue(int value) { this->value = value; }
	Cell(int value) { this->value = value; }
	Cell() { this->value = -1; }
	int getNumPossible();
};
