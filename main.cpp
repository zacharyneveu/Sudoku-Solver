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
			b1.initialize(fin);
			b1.print();
			b1.printConfs();

			//temp variables
			int r, c, value;
			char choice;
			while(1)
			{

				cout<<"Enter row of cell to edit (from 1-9)"<<endl;
				cin>>r;
				r--; 	//make indices match
				cout<<"Enter column of cell to edit (from 1-9)"<<endl;
				cin>>c;
				c--;	//make indices match

				cout<<"Press s to set a cell, c to clear one or q to quit"<<endl;
				cin>>choice;
				if(choice == 'q')
					break;
				else if(choice == 's')
				{
					cout<<"Enter the value to be inserted"<<endl;
					cin>>value;
					b1.setCell(r, c, value);
				}
				else if(choice =='c')
				{
					b1.clearCell(r, c);
				}
				else
				{
					cout<<"Sorry, invalid operation"<<endl;
					continue;
				}

				b1.print();
				b1.printConfs();
			}
		}
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
	system("pause");
	return 0;
}
