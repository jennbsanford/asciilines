/*
Programmer: Jen Sanford
Program: ASCII Lines (Assignment 1)
Date: 7/2/2019
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ASCII_OFFSET = 48;

struct container {

	char symbol;
	int rowCtr;
	int colCtr;
	char direction;
	int distance;

};

void writeLine(string command, char *** data, int rows, int cols);
void printData(char *** data, int rows, int cols);
void parseLine(string command, container * results);

int main(int argc, char * argv[]) {

	// enforces correct usage
	if (argc != 2)
	{
		cout << "\nPlease enter the input file name as the only parameter\n";
		return -1;
	}

	// grabs the filename
	string filename(argv[1]);
	ifstream inputFile(filename);

	// ensure file is opened
	if (!inputFile.is_open())
	{
		cout << "\nFile failed to open. Exiting program.\n";
		return -1;
	}

	string current;
	int rows;
	int cols;

	// parse the first line for array size
	getline(inputFile, current);
	rows = current[0] - ASCII_OFFSET;
	cols = current[2] - ASCII_OFFSET;

	// allocate the dynamic memory
	char ** data = new char *[rows];
	for (int i = 0; i < rows; i++)
		data[i] = new char[cols];

	// initialize the 2D array
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
			data[y][x] = '.';
	}

	// parse each line from the input file
	while (getline(inputFile, current))
	{
		writeLine(current, &data, rows, cols);
	}

	inputFile.close();

	// display the parsed data
	printData(&data, rows, cols);

	// deallocate the memory
	for (int i = 0; i < rows; i++)
		delete[] data[i];

	delete[] data;

	return 1;

}

// writes to the 2D array based on the parameters of the command
void writeLine(string command, char *** data, int rows, int cols)
{

	container toFill;

	parseLine(command, &toFill);

	while (toFill.colCtr < cols && toFill.rowCtr < rows && toFill.distance > 0)
	{
		(*data)[toFill.rowCtr][toFill.colCtr] = toFill.symbol;
		if (toFill.direction == 'h')
			toFill.colCtr++;
		else
			toFill.rowCtr++;
		toFill.distance--;
	}

}

// helps deal with those pesky '-' signs and fills the struct with parsed data
void parseLine(string command, container * results)
{
	results->symbol = command[0];
	int offset = 0;

	if (command[2] == '-')
	{
		offset++;
		results->rowCtr = 0;
	}
	else
		results->rowCtr = command[2] - ASCII_OFFSET;

	if (command[4 + offset] == '-')
	{
		offset++;
		results->colCtr = 0;
	}
	else
		results->colCtr = command[4 + offset] - ASCII_OFFSET;

	results->direction = command[6 + offset];
	results->distance = command[8 + offset] - ASCII_OFFSET;

	
}

// prints the data in formatted fashion
void printData(char *** data, int rows, int cols)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
			cout << (*data)[y][x];

		cout << "\n";
	}
}



