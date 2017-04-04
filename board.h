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
    board(int); //constructor with size
    void clearBoard(); //clears whole board except pre filled cells
    void clearCell(int, int); //clears given cell
    void initialize(ifstream &fin); //initializes conflicts
    void print(); //prints the puzzle
    void printConfs(); //prints the conflict lists
    bool isBlank(int, int); //checks if cell is blank
    Cell getCell(int, int); //gets the value of a cell
    void setCell(int, int, int); //sets a cell to given value
    bool updateConfs(int, int); //updates conflicts and checks for errors
    int getSquare(int, int); //returns the square number from cell index
    bool isSolved(); 	//checks if the puzzle is solved
    bool isPreFilled(int, int); //checks if cell came pre-filled from file

	bool isPossible(int, int, int);
	void findCell(int &row, int &col);
	bool solve(int count);

private:

    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
    int size;
    matrix<Cell> b; //stores the board
    vector<vector<int>> preFilled; //keep track of pre-filled cells
    matrix<bool> confrows; //stores row conflicts
    matrix<bool> confcols; //stores column conflicts
    matrix<bool> confsqrs; //stores square conflicts
};
