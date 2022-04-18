#include <iostream>
#include <fstream>
#include<string>
using namespace std;
int Strlength(char* str)   //Calculating string length
{
	int stringLen = 0;
	int i = 0;

	while (str[i] != '\0')//not equal to null
	{
		stringLen++;
		i++;
	}

	return stringLen;
}
char** wordslist(int tstcase, int readingfrmline)
{
	ifstream file("Input.txt");
	if (file)
	{

		string Linedmy;
		for (int i = 0; i < readingfrmline; i++)      //this skips all the data before words 
		{
			getline(file, Linedmy);
		}

		char** wordList = new char* [tstcase];

		int i = 0;

		while (i < tstcase)
		{
			char xyz[80];

			file.getline(xyz, 80);

			int colomns = 0;
			colomns = Strlength(xyz);

			wordList[i] = new char[colomns + 1];

			int j = 0;
			for (j = 0; j < colomns; j++) //deep copying
			{
				wordList[i][j] = xyz[j];
			}
			wordList[i][j] = '\0';
			i++;
		}

		return wordList;
	}

}
char** ReadWordSearchGrid(int rows, int colomns, int readingfrmline)
{
	ifstream file("Input.txt");
	if (file)
	{

		string Linedmy;
		for (int i = 0; i < readingfrmline; i++) //this skips all the data before grid
		{
			getline(file, Linedmy);
		}

		int i = 0;
		char** grid = new char* [rows];
		while (i < rows)
		{
			char xyz[80];

			file.getline(xyz, 80);



			grid[i] = new char[colomns + 1];

			int j = 0;
			int k = 0;
			for (j = 0; j < colomns && k < (colomns + colomns - 1); j++) 
			{

				grid[i][j] = xyz[k];
				k += 2;

			}
			grid[i][j] = '\0';
			i++;
		}

		return grid;
	}

}

int* checkingdirections(char** grid, int inrows, int incolomns, int row, int colomns, char* wrd)
{
	int directionofrows[] = { 0, 0, 1,-1, 1, 1, -1, -1 };     // All the 8 Directions
	int directionofcolomns[] = { -1, 1, 0, 0, 1, -1, 1, -1 };

	int* array = new int[3];    //If word is founf record will be saved and show 1
							 //if word is not found show -1

	if (grid[row][colomns] != wrd[0])   //checks of coordinate first letters
	{
		array[0] = -1;
		array[1] = 0;
		array[2] = 0;
		return  array;
	}


	int length = Strlength(wrd);


	for (int i = 0; i < 8; i++)  //for All 8 directions
	{
		int j;
		int mvrows = row + directionofrows[i];
		int mvcolomns = colomns + directionofcolomns[i];

		// First character is checked
		// cheking remaining
		for (j = 1; j < length; j++)  //starting from from 1 after first is found
		{
			// if conditions as :
			if (mvrows >= inrows || mvrows < 0 || mvcolomns >= incolomns || mvcolomns < 0)
			{
				break;
			}


			// If not matched
			if (grid[mvrows][mvcolomns] != wrd[j])
			{
				break;
			}



			mvrows = mvrows + directionofrows[i];   //moves in particular direction
			mvcolomns = mvcolomns + directionofcolomns[i];
		}


		if (j == length) //if the wrd is found then j will be equal to length
		{
			mvrows = mvrows - directionofrows[i];
			mvcolomns = mvcolomns - directionofcolomns[i];

			array[0] = 1;
			array[1] = mvrows;   //end cordinates of the wrd
			array[2] = mvcolomns;

			return array;
		}

	}
	array[0] = -1;
	array[1] = 0;
	array[2] = 0;
	return  array;
}


int* searchingofgrid(char** grid, int inrows, int incolomns, char* wrd)  //Searching all the words
{
	int* returnArray = new int[4];
	int* array = new int[3];

	for (int row = 0; row < inrows; row++)
	{
		for (int colomns = 0; colomns < incolomns; colomns++)
		{
			array = checkingdirections(grid, inrows, incolomns, row, colomns, wrd);
			if (array[0] == 1)
			{
				returnArray[0] = row;  //starting cordinates
				returnArray[1] = colomns;

				returnArray[2] = array[1];  //ending coordinates
				returnArray[3] = array[2];
				return returnArray;
			}

		}

	}
	delete[]array;
	returnArray[0] = -1;
	returnArray[1] = 0;
	returnArray[2] = 0;
	returnArray[3] = 0;
	return returnArray;

}


void showingthecoordinatenumbers(char** list, int totalnumofwords, char** grid, int rows, int colomns)  //showing start and coordinates of th words
{
	ofstream file("Output.txt");
	if (file)
	{
		for (int i = 0; i < totalnumofwords; i++)
		{

			int* rsltarray = new int[4];

			rsltarray = searchingofgrid(grid, rows, colomns, list[i]);  //returning the coordinates

			if (rsltarray[0] == -1)
			{
				file << "Cnnot be found !!";
			}
			else
			{
				file << "{" << rsltarray[0] << "," << rsltarray[1] << "}" << "{" << rsltarray[2] << "," << rsltarray[3] << "}";
			}
			file << endl;
			delete[]rsltarray;


		}
	}
	file.close();


}
int main()
{
	ifstream fin("Input.txt");
	if (fin)
	{
		int rows, colomns, tstcase;

		fin >> rows >> colomns >> tstcase;//taking the rows , coloumns , and tstcase.
		

		cout <<"***word Searching****";

		int readLine; 

		char** grid = 0;
		readLine = 2;  //first line has rows and coloumns //second lines has testcase
		grid = ReadWordSearchGrid(rows, colomns, readLine);     //This is reading the grid
		

		char** list = 0;//list of the words starting after grid
		readLine = 2 + rows;  
		list = wordslist(tstcase, readLine);  //Is reading the list

		showingthecoordinatenumbers(list, tstcase, grid, rows, colomns);   
		cout << endl << "Words are searched check the file "<<endl;
		return 0;
	}
} 
	
