// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "cell.h"
#include "board.h"
#include <string>
#include<cassert>

using namespace std;

board::board(int size)
// Board constructor
{
    //resize all matrices to match square size
    b.resize(size, size);
    confrows.resize(size, size);
    confcols.resize(size, size);
    confsqrs.resize(size, size);
    //set size member
    this->size = size;
}//end function

void board::clearBoard()
// Mark all possible values as legal for each board entry
{
    for (int i = 0; i < size; i++) 		//iterate over all rows
        for (int j = 0; j < size; j++) 	//iter over cols
        {
            if (!isPreFilled(i, j))		//make sure not pre filled
            {
                b[i][j].setValue(-1);    //-1 is clear value
            }
        }
}//end function

void board::clearCell(int r, int c)
//This function clears the value in a given cell and updates the relevant
//conflict lists
{
    if (!isPreFilled(r, c)) //make sure square not pre-filled
    {
        //temp variables
        int value = getCell(r, c).getValue() - 1;
        int square = getSquare(r, c);

        if (value >= 0 && value < size)
        {
            //update conflict lists manually because updateConfs() would not know
            //what value to set to false
            confrows[r][value] = false;
            confcols[c][value] = false;
            confsqrs[square][value] = false;
        }

        //clear value of square
        b[r][c].setValue(-1);
    }
    else
    {
        cout << "Square Was Pre-Filled, cannot be cleared" << endl;
    }
}//end function

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
    char ch;

    clearBoard();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fin >> ch;

            // If the read char is not Blank
            if (ch != '.')
            {
                setCell(i, j, ch - '0');    // Convert char to int

                //mark squares as pre filled
                vector<int> toAdd;
                toAdd.push_back(i);
                toAdd.push_back(j);
                preFilled.push_back(toAdd);
            }
            else //The char is blank
            {
                //clear cell (i, j)
                clearCell(i, j);
            }

            bool worked = updateConfs(i, j); //update conflicts for each cell

            if (worked == false) //a square had all conflicts
            {
                cout << "Impossible Puzzle to Solve" << endl;
            }
        }//end loop over cols
    }//end loop over rows
}//end function

bool board::isSolved()
//This function checks each row, colummn and square to make sure the properties
//for a solved board are met for each square.  Runs in n^3 times, but is called
//infrequently, and only needs to perform three comparisons each loop.
{
    for (int i = 0; i < size; i++) //iterate over rows
    {
        for (int j = 0; j < size; j++) //iterate over cols
        {
            if (getCell(i, j).getValue() == -1)
            {
                return false;
            }
        }//end loop over columns
    }//end loop over rows

    //if all squares don't break, then puzzle is solved!
    return true;
}//end function


Cell board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 0 && i <= size && j >= 0 && j <= size)
    {
        return b[i][j];
    }
    else
    {
        throw rangeError("bad value in getCell");
    }
}//end function

bool board::setCell(int r, int c, int value)
//sets cell to value if passed a value
//returns false if conflict update fails (causes impossible square)
{
    b[r][c] = value;
    bool worked = updateConfs(r, c);

    if (worked)
    {
        return true;
    }
    else
    {
        return false;
    }
}//end function

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 0 || i >= size || j < 0 || j >= size)
    {
        throw rangeError("bad value in setCell");
    }

    return (getCell(i, j).getValue() - 1);
}//end function

void board::print()
// Prints the current board.
{
    for (int i = 0; i < size; i++)
    {
        cout << "---------------------------" << endl;

        for (int j = 0; j < size; j++)
        {
            int value = b[i][j].getValue();

            if (value < 0) //if cleared square
            {
                cout << "  |";
            }
            else	//if not empty square
            {
                cout << value << " |";
            }
        }//end loop over cols

        cout << endl;
    }//end for loop over rows

    //line divider
    cout << "---------------------------" << endl;
}//end function

void board::printConfs()
//Prints conflict lists for each row, column, and square.
{
    cout << "             Digit: 1 2 3 4 5 6 7 8 9" << endl;
    cout << "-------------------------------------" << endl;

    for (int i = 1; i <= size; i++)
    {
        cout << "   Row " << i << " Conflicts: ";

        for (int j = 0; j < size; j++)
        {
            cout << confrows[i - 1][j] << " ";
        }

        cout << endl;

        cout << "Column " << i << " Conflicts: ";

        for (int j = 0; j < size; j++)
        {
            cout << confcols[i - 1][j] << " ";
        }

        cout << endl;

        cout << "Square " << i << " Conflicts: ";

        for (int j = 0; j < size; j++)
        {
            cout << confsqrs[i - 1][j] << " ";
        }

        cout << endl << endl;
    }//end for loop over digits
}//end function

bool board::updateConfs(int row, int column)
//This function updates the conflict lists for the row, column, and square of a
//given square.  Returns false if a conflict list is all true, meaning there is
//an error on the board.
{
    int value = b[row][column].getValue();
    int square = getSquare(row, column);

    if (value > 0 && value < 10)
    {
        confrows[row][value - 1] = true;
        confcols[column][value - 1] = true;
        confsqrs[square][value - 1] = true;
    }

    //check to make sure moves are still available.  This runs in linear time,
    //but will run a max of 9 times, and will almost always run far less than
    //that.
    bool noMoves = true; //assume error at first

    for (int i = 0; i < size; i++) //iterate over digits
    {
        if (confrows[row][i] || confcols[column][i] || confsqrs[square][i] == false)
        {
            noMoves = false; //no error if this is triggered
        }
    }

    return ~noMoves;
    return true;
}//end function


int board::getSquare(int row, int column)
//returns square number for cell at given indices.
// squares are indexed from 0-8.  Square numbers are ordered from left to right,
// then top to bottom
{
    //Row offset is the vertical component of the square number (range 0-2)
    int rowoffset = 0;
    rowoffset = row > 2 ? 1 : rowoffset;
    rowoffset = row > 5 ? 2 : rowoffset;
    //column/3 returns a value from 0-2 determining whether cell is in left,
    //middle, or right square
    return 3 * rowoffset + (column / 3);
}//end function


//For part a only. Returns if the selected cell was read in from file, or entered by user.
bool board::isPreFilled(int row, int col)
{
    if (!preFilled.empty())
    {
        for (int i = 0; i < preFilled.size(); i++)
        {
            if (preFilled[i][0] == row && preFilled[i][1] == col)
            {
                return true;
            }
        }
    }

    return false;
}

bool board::findCell(int &row, int &col)
//this function finds a cell that is blank, and has a minimum
//number of available possible values it can take, the function is passed
//the row and column by reference, and updat
{
    int numPoss = 9; //keep track of cheapest cell to solve

    for (int r = 0; r < size; r++) //iterate over rows
    {
        for (int c = 0; c < size; c++) //iterate over cols
        {
            int count = 0; //stores number of possibilities

            if (getCell(r, c).getValue() != -1) //skip filled cells
            {
                continue;
            }

            for (int dig = 1; dig <= size; dig++) //iterates over digits
            {
                //if a digit is possible
                if (isPossible(r, c, dig))
                {
                    count++;
                }
            }

            if (count < numPoss) //e.g. if cell has 1 poss
            {
                //assign values
                numPoss = count;
                row = r;
                col = c;
            }
        }//end loop over cols
    } //end loop over rows

    //return true on a successful solve, false if a conflict exists
    return (numPoss > 0);
} //end function

bool board::isPossible(int row, int col, int dig)
//checks if dig is a possibility for the cell at (row, col)
//cells indexed from dig has range 1-9
{
    //-1 because passed dig has range 1-9
    bool colbool = confcols[col][dig - 1];
    bool rowbool = confrows[row][dig - 1];
    bool sqrbool = confsqrs[getSquare(row, col)][dig - 1];

    //if no conflicts
    if (!(colbool || rowbool || sqrbool))
    {
        return true;
    }

    //if there are conflicts
    return false;
}//end function


bool board::solve(int &count)
//recursively solves the board, placing numbers in open cells and backtracking
//when no viable cells are found
{
    bool solved = false;

    if (isSolved())
    {
        cout << "Solved!" << endl;
        //cout << "Count: " << count << endl;
        print();
        return true;
    }
    else
    {
        //row and col are passed by reference to findCell to be set
        int row = -1;
        int col = -1;

        //If find cell finds any cell with 0 possibilities, backtrace
        if (!findCell(row, col))
        {
            return false;
        }

        if (row == -1 || col == -1) //if findCell doesn't find anything
        {
            return false;
        }

        for (int i = 1; i <= size; i++)
        {
            if (isPossible(row, col, i))
            {
                bool setworked = setCell(row, col, i);

                if (!setworked) //if set caused errors, backtrack
                {
                    return false;
                    cout << "Caused Conflicts" << endl;
                }

				/*
                 * if (count % 100 == 0)
                 * {
                 *     cout << "Count: " << count << endl;
                 *     print();
                 * }
				 */

                solved = solve(++count);

                if (!solved)
                {
                    clearCell(row, col);
                    //cout<<"Backtracking"<<endl;
                }
                else
                {
                    return true;
                }
            }//end if ispossible
        }//end loop over digits

        return false;
    }//end if not solved
}//end solved function
