Basic Algorithm Notes:

	Board b1;
	B1.takeNotes();
	B1.fillGrid(int j)
		Int square = Find square(int j)
			If(square == -1)
				fillGrid(j++)
		Stack<int> squarestack.push(square)
		Bool worked = place(square, possibilities[])
			If(worked == 0)
				place(square, [-1])
				Squarestack.pop()
				Remove first item of squarestack.top() possibility list
				Fillsquare(fillsquare.top())
			Else
				Repeat at a


function purposes:

Int findSquare(int j)
//Returns index of first square with j items in possibility list
//returns -1 if no squares with this property found

Bool place(int index, int possibilities[])
//tries filling square at index with first possibility.   Update lists, if error, try next possibility.
//Return True on success, False on failure

Void clearsquare(int index)
//sets value of square to -1 and removes previous value from relevant lists

Bool fillGrid(int j)
//fills all squares of grid if passed 1 as j.  Recursively calls itself until grid is solved.

Void takeNotes()
//fills all possibility sets for the grid
