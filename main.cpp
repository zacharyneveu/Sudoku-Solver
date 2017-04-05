// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "board.h"

int main()
{
    ifstream fin;
    // Read the sample grid from the file.
    string fileName = "sudoku1.txt";

    fin.open(fileName.c_str());

    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try
    {
        board b1(9);

        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin); //Initialize board
			int x = 0;
			b1.solve(x); //start count at 0, must be passed by reference
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
