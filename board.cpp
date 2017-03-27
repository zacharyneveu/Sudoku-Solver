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

board::board(int sqSize)
// Board constructor
{
	b.resize(sqSize, sqSize);
	size = sqSize;
}

void board::clear()
// Mark all possible values as legal for each board entry
{
   for (int i = 0; i < size; i++)
	   for (int j = 0; j < size; j++)
      {
         b[i][j].clear();
      }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
	    {
	       fin >> ch;

          // If the read char is not Blank
		   if (ch != '.')
			   setCell(i, j, ch - '0');   // Convert char to int
		   else
			   setCell(i, j);
        }
}

ostream &operator<<(ostream &ostr, vector<Cell> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++) {
		ostr << (v[i].getValue() == -1 ? "." : to_string(v[i].getValue()));
		if (i % 3 == 2) {
			ostr << "  ";
		}
	}
   return ostr <<endl;
}

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
	b[r][c].setValue(-1);
	return;
}
void board::setCell(int r, int c, int value) {
	b[r][c].setValue(value);
	return;
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 0 || i >= size || j < 0 || j >= size)
      throw rangeError("bad value in setCell");

   return (getCell(i,j).getValue() - 1);
}

void board::print()
// Prints the current board.
{
	for (int i = 0; i < size; i++) {
		cout << b[i];
		if (i % 3 == 2) {
			cout << endl;
		}
   }
	cout << endl;
}
