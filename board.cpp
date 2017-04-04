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
        int value = getCell(r, c).getValue()-1;
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
			if(getCell(i,j).getValue() == -1)
				return false;
        }//end loop over columns
    }//end loop over rows
    //if all squares don't break, then puzzle is solved!
    return true;
}//end function


/*
 * ostream &operator<<(ostream &ostr, vector<Cell> &v)
 * // Overloaded output operator for vector class. Commented because not
 * currently being used for print out.
 * {
 *     for (int i = 0; i < v.size(); i++) {
 *         ostr << (v[i].getValue() == -1 ? "." : to_string(v[i].getValue()));
 *         if (i % 3 == 2) {
 *             ostr << "  ";
 *         }
 *     }
 *    return ostr <<endl;
 * }
 */

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

void board::setCell(int r, int c, int value)
//sets cell to value if passed a value
{
	b[r][c] = value;
	updateConfs(r, c);

	/*
     * else 	//if cell already filled
     * {
     *     cout << "That Cell is Already Filled" << endl;
     * }
	 */
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

/*
 *     //check to make sure moves are still available.  This runs in linear time,
 *     //but will run a max of 9 times, and will almost always run far less than
 *     //that.
 *     bool noMoves = true; //assume error at first
 *
 *     for (int i = 0; i < size; i++) //iterate over digits
 *     {
 *         if (confrows[row][i] || confcols[column][i] || confsqrs[square][i] == false)
 *         {
 *             noMoves = false; //no error if this is triggered
 *         }
 *     }
 *
 *     return ~noMoves;
 */
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

void board::findCell(int &row, int &col)
{
	row = -1;
	col = -1;
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			if(getCell(i,j).getValue() == -1)
			{
				row = i;
				col = j;
				return;
				//return 1;
			}
		}
	}
	//return 0;
}

bool board::isPossible(int row, int col, int dig)
{
	bool colbool = confcols[col][dig-1];
	bool rowbool = confrows[row][dig-1];
	bool sqrbool = confsqrs[getSquare(row, col)][dig-1];

	/*
	 * cout<<"Square: "<<getSquare(row, col)<<endl;
	 * cout<<"Square bool: "<<sqrbool<<endl;
	 */

	if(!(colbool || rowbool || sqrbool))
	{
		return true;
	}
	return false;
}


bool board::solve(int count)
{
	//cout<<"Count: "<<count<<endl;
	//printConfs();
	//int cont;
	//cin>>cont;
	bool solved = false;

	if(isSolved())
	{
		cout<<"Solved!"<<endl;
		print();
		return true;
	}
	else
	{
		int row = -1;
		int col = -1;
		findCell(row, col);
		for (int i=1; i<=size; i++)
		{
 			if (isPossible(row, col, i))
			{
			   	setCell(row, col, i);
				if(count>60)
				{
					print();
					cout<<"Count: "<<count<<endl;
				}
			   	solved = solve(++count);
				if(!solved)
				{
					clearCell(row, col);
				}
				else
				{
					return true;
				}
			}
		}
	return false;
	}
}
