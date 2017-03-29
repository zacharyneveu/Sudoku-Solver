#pragma once

// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "cell.h"
#include <stack>

using namespace std;

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clearBoard();
	void clearCell(int, int);
	void initialize(ifstream &fin);
	void print();
	void printConfs();
	bool isBlank(int, int);
	Cell getCell(int, int);
	void setCell(int, int);
	void setCell(int, int, int);
	bool updateConfs(int, int);
	int getSquare(int, int);
	bool isSolved();

	void buildNextList(int);

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
	int size;
	matrix<Cell> b;
	matrix<bool> confrows;
	matrix<bool> confcols;
	matrix<bool> confsqrs;
	stack<cell> filled;
	stack<cell> toFill;
};
