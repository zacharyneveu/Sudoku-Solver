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
	this->size = size;
}

void board::clearBoard()
// Mark all possible values as legal for each board entry
{
   for (int i = 0; i < size; i++)
	   for (int j = 0; j < size; j++)
      {
         b[i][j].setValue(-1);
      }
}

void board::clearCell(int r, int c)
//This function clears the value in a given cell and updates the relevant
//conflict lists
{
	//temp variables
	int value = getCell(r,c).getValue();
	int square = getSquare(r,c);

	//update conflict lists manually
	confrows[r][value] = false;
	confcols[c][value] = false;
	confsqrs[square][value] = false;

	//clear value of square
	b[r][c].setValue(-1);
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clearBoard();

   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
	    {
	       fin >> ch;

          // If the read char is not Blank
		   if (ch != '.')
			   setCell(i, j, ch - '0');   // Convert char to int
		   else
			   setCell(i, j);

		   bool worked = updateConfs(i, j); //update conflicts for each cell
		   if (worked == false)
		   {
		       cout<<"Impossible Puzzle to Solve"<<endl;
		   }
        }
}

bool board::isSolved()
//This function checks each row, colummn and square to make sure the properties
//for a solved board are met for each square.
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			//update conflicts for each square
			updateConfs(i,j);
			for (int k=0; k<9; k++)
			{
				//if any conflict is set to true, puzzle is not solved
				if (confrows[i][k] == true
						|| confcols [j][k] == true
						|| confsqrs[i][k]==true)
				{
					return false;
				}
			}//end loop over digits
		}//end loop over columns
	}//end loop over rows
	//if all squares don't break, then puzzle is solved!
	return true;
}//end function


/*
 * ostream &operator<<(ostream &ostr, vector<Cell> &v)
 * // Overloaded output operator for vector class.
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
      return b[i][j];
   else
      throw rangeError("bad value in getCell");
}

void board::setCell(int r, int c) {
	b[r][c]=-1;
	updateConfs(r,c);
	return;
}

void board::setCell(int r, int c, int value) {
	b[r][c]=value;
	updateConfs(r,c);
	return;
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 0 || i >= size || j < 0 || j >= size)
      throw rangeError("bad value in setCell");

   //TODO: Why -1 at the end of this??
   return (getCell(i,j).getValue() - 1);
}

void board::print()
// Prints the current board.
{
	for (int i = 0; i < size; i++) {
		cout<<"---------------------------"<<endl;
		for (int j=0; j<size; j++)
		{
			int value = b[i][j].getValue();
			if (value < 0)
			{
				cout<<"  |";
			}
			else cout<<value<<" |";
		}
		cout<<endl;
   }
	cout << "---------------------------"<<endl;
}

void board::printConfs()
//Prints conflict lists for each row, column, and square.
{
	cout<<"             Digit: 1 2 3 4 5 6 7 8 9"<<endl;
	cout<<"-------------------------------------"<<endl;
	for (int i=1; i<=size; i++)
	{
		cout<<"   Row "<<i<<" Conflicts: ";
		for (int j=0; j<size; j++)
		{
			cout<<confrows[i-1][j]<<" ";
		}
		cout<<endl;

		cout<<"Column "<<i<<" Conflicts: ";
		for (int j=0; j<size; j++)
		{
			cout<<confcols[i-1][j]<<" ";
		}
		cout<<endl;

		cout<<"Square "<<i<<" Conflicts: ";
		for (int j=0; j<size; j++)
		{
			cout<<confsqrs[i-1][j]<<" ";
		}
		cout<<endl<<endl;
	}
}

bool board::updateConfs(int row, int column)
//This function updates the conflict lists for the row, column, and square of a
//given square.  Returns false if a conflict list is all true
{
	int value = b[row][column].getValue();
	int square = getSquare(row, column);
	if (value > 0 && value < 10)
	{
		confrows[row][value-1] = true;
		confcols[column][value-1] = true;
		confsqrs[square][value-1] = true;
	}

	//check to make sure moves are still available.  This runs in linear time,
	//but will run a max of 9 times, and will almost always run far less than
	//that.
	bool noMoves = true;
	for (int i=0; i<size; i++)
	{
		if (confrows[row][i] || confcols[column][i] || confsqrs[square][i] == false)
		{
			noMoves = false;
		}
	}
	return ~noMoves;
}

int board::getSquare(int row, int column)
//returns square number for cell at given indices.
//Cells are index from 0-8
{
	int rowoffset = 0;
	rowoffset = row > 2 ? 1: rowoffset;
	rowoffset = row > 5 ? 2: rowoffset;
	return 3*rowoffset + (column/3);
}

/*
 * void board::findCell(int j, int k)
 * //Returns the index of a square with j items in its possibility list.
 * //Returns -1 if no squares are available
 * {
 *     for (int i=0; i<size; i++)
 *     {
 *         for (int g=0; g<size; g++)
 *         {
 *             Cell thiscell = getCell(i,g);
 *
 *             if (thiscell.getNumPossible() == j)
 *             {
 *                 j = i;
 *                 k = g;
 *                 return;
 *             }
 *         }
 *
 *     }
 * }
 *
 */
