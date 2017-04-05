// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <vector>
#include "board.h"

vector<int> numMoves;

void printStats();

int main()
{
    ifstream fin;
    // Read the sample grid from the file.
    string fileName = "sudoku.txt";

    fin.open(fileName.c_str());

    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        while (fin && fin.peek() != 'Z')
        {
			cout << "Solving Board " << numMoves.size() + 1 << endl;
			board b1(9);
            b1.initialize(fin); //Initialize board
			int x = 0;
			b1.solve(x); //start count at 0, must be passed by reference
			numMoves.push_back(x);
			cout << "Board " << numMoves.size() << " Solved in " << x << " moves!\n";
			printStats();
        }//end loop over file
    }//end try statement
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }

    system("pause");
    return 0;
}//end main function

void printStats() {
	int size = numMoves.size();
	int totalMoves = 0;
	for (int i = 0; i < size; i++) {
		totalMoves += numMoves[i];
	}
	cout << "Average Solve Moves: " << (totalMoves / size) << endl;
}