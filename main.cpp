// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "board.h"

int squareNumber(int i, int j);

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

            //temp variables used in while loop
            int r, c, value;
            char choice;

            while (!b1.isSolved()) //loop while puzzle not solved
            {
                b1.print(); 		//print board
                b1.printConfs(); 	//print conflicts on board


                //get user input for what to do
                cout << "Press s to set a cell, c to clear one or q to quit" << endl;
                cin >> choice;

                if (choice == 'q') //quit option
                {
                    break;
                }

                //These inputs trigger for all cases except quit
                cout << "Enter row of cell to edit (from 1-9)" << endl;
                cin >> r;
                r--; 	//make indices match
                cout << "Enter column of cell to edit (from 1-9)" << endl;
                cin >> c;
                c--;	//make indices match

                if (c < 0 || c > 9 || r < 0 || r > 9) //range check
                {
                    cout << "Not a valid row or column" << endl;
                    break; //exit program
                }

                if (choice == 's') //set a cell
                {
                    //get value to be set from user
                    cout << "Enter the value to be inserted" << endl;
                    cin >> value;
                    b1.setCell(r, c, value);
                }
                else if (choice == 'c') //clear a square
                {
                    b1.clearCell(r, c);
                }
                else 	//cover default case
                {
                    cout << "Sorry, invalid operation" << endl;
                    continue;
                }

                //Print whether board is solved or not
                if (b1.isSolved())
                {
                    cout << "Puzzle is Solved!" << endl;
                }
                else
                {
                    cout << "Puzzle is Unsolved" << endl;
                }

            }//end loop until solved
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
