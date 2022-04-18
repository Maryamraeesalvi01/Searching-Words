#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <conio.h>
#include <windows.h>
using namespace std;
void readeroffile(string B[]) { //file reader function(REadaing the file
	ifstream fin;
	fin.open("input.txt");
	string L;
	int i = 0;
	while (!fin.eof()) { //Working till eof
		getline(fin, L,'\n');
		B[i] = L;
		fin >> B[i];
		i++;
	}
	fin.close();
	cout<<"The following words are :"<<endl;
	for(int j=0; j<i; j++) {//Words are being displayed
		cout<<B[j]<<endl;
	}
}
int longstring(string array[]) { //function to find longest string
	int ocrnc, nwmx;
	for (int i = 0; i < 6; i++) {
		ocrnc = array[0].length();//loop working for occurence check
		if (array[i].length() < array[i + 1].length()) {
			nwmx = array[i + 1].length();
		}
		if (nwmx > ocrnc) {
			ocrnc = nwmx;
		}
	}
	return ocrnc;
}
void functionofgame(int len1, string array[]) {//Function for game
	char grid[len1][len1];
	int r;
	char c;
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len1; j++) {
			r = rand() % 26;//generates random number between 0 and 26
			c = 'B' + r;//adding  random number formed above 'r' into the ASCII value of 'B'
			grid[i][j] = c;//grid is initialized here
		}
	}
	int n=0;
	int m=0;
	for (int ind = 0; ind < 7; ind++) {//loop working for words placement

		if (array[ind].length() == len1||n==0) {
			// put words diagonally in the grid
			int rows = 0;
			int coloums = 0;
			for (int i = 0; array[ind][i] != '\0'; i++, rows++, coloums++) {
				grid[rows][coloums] = array[ind][i];
			}
			n++;
		} else if (array[ind].length() % 2 == 0) {
			// put word horizontally
			int rows = rand() % len1;
			int coloums = (rand() % 3)+4;
			if(n==1)
				rows--;
			else if(n==2)
				rows++;// increment in rows
			for (int i = 0; array[ind][i] != '\0'; i++, coloums++) {
				grid[rows][coloums] = array[ind][i];
			}
			n++;
		} else {
			int rows=(rand()%4)+1;
			int coloums=rand()%5;
			if(m==0)// when m is equal to zero 
				coloums++;
			for (int i = 0,j=ind; array[ind][i] != '\0'; i++, rows++) {
				grid[rows][coloums] = array[ind][i];//Grid check is performed
			}
			m++;
		}
	}
	ofstream fout("output.txt");//putting the grid in an output.txt file
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len1; j++) {
			fout << grid[i][j] << " ";
		}
		fout << endl;
	}
	fout.close();//file is closed
}
int main() {
	int len1 = 0;
	string array[7];
	readeroffile(array);//to read the input file 
	len1 = longstring(array);//checking the length of the word
	if (len1 < 10) {
		len1 = 10;
	}
	functionofgame(len1, array);//function  for initializing the word puzzle
	cout<<"The words canbe seen  in file output.txt"<<endl;
	system("pause");
	return 0;
}
