// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <vector>
#include "board.h"
#include<time.h>

vector<int> numMoves;
vector<float> times;

void printStats();

int main()
{
    ifstream fin;
    // Read the sample grid from the file.
    string fileName = "sudoku1-3.txt";

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

			//time objects to display runtime
			time_t t1, t2;
			int x = 0;

			//start the clock
			t1 = clock();

			b1.solve(x); //start count at 0, must be passed by reference

			//stop the clock
			t2 = clock();

			//calculate runtime from clock
			float diff((float)t2 - (float)t1);
			float seconds = diff / CLOCKS_PER_SEC;
			times.push_back(seconds);

			numMoves.push_back(x);
			cout << "Board " << numMoves.size() << " Solved in " <<
			   	x << " moves and "<<seconds<<" seconds"<<endl;
        }//end loop over file
	printStats();
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
	float totaltime = 0;
	for (int i = 0; i < size; i++) {
		totalMoves += numMoves[i];
		totaltime += times[i];
	}

	cout << "Average Solve Moves: " << (totalMoves / size) << endl;
	cout<<"Average Solve Time: "<<(totaltime / size)<<" seconds"<<endl;
}
