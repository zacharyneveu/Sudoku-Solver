#pragma once

// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "cell.h"

using namespace std;

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print();
	bool isBlank(int, int);
	Cell getCell(int, int);
	void setCell(int, int);
	void setCell(int, int, int);

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
	int size;
	matrix<Cell> b;
};
