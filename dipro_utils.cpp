#include "dipro_utils.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// this function opens a file and reads the lines into a string array
int getInputData(string* ptr_input_data, string file_name)
{
	// input param: string* input_data: pointer to array that receives the input strings from file
	// input param: string file_name: the file to read from

	string line; // here we store a line of input data

	// define and open the filestream
	ifstream in;
	in.open(file_name);

	// loop through all the lines in the input file
	int i = 0;
	while (!in.eof())
	{
		// read the line from the current position in the file
		getline(in, line);
		// store the input data in a line
		*(ptr_input_data + i) = line;
		i++;
	}

	// close file and free resources
	in.close();

	// return function value
	return 0;
}

// this function is a util function that converts a char into an int digit
int charToInt(char c)
{
	// input param: char c: the char to convert to an int

	int output_int = 0;

	// check which char is the input and return the int representation
	switch (c)
	{
	case('0'):
		output_int = 0;
		break;
	case('1'):
		output_int = 1;
		break;
	case('2'):
		output_int = 2;
		break;
	case('3'):
		output_int = 3;
		break;
	case('4'):
		output_int = 4;
		break;
	case('5'):
		output_int = 5;
		break;
	case('6'):
		output_int = 6;
		break;
	case('7'):
		output_int = 7;
		break;
	case('8'):
		output_int = 8;
		break;
	case('9'):
		output_int = 9;
		break;

	default:
		bool bool_talktalk = true; // if true than we are debugging
		if (bool_talktalk)
		{
			cout << "Warning: input char is not an integer!";
		}
		break;
	}

	return output_int;
}

// this function has a string as input and decodes it into a multidimensional array of ints
int decodeStr(string s, int** pArray, int row)
{
	// input param: string s: this is the string to convert to an integer array
	// input param: int** pArray: this pointer to an int array receives the integer values from the string
	// input param: int row: this is the row index in the integer array

	int int_from_str = 0; // this variable  contains the int that is decoded from the substring
	char* charr_arr; //pointer to a char array
	charr_arr = &s[0]; // store the adress of string s

	// how many elements in this string?
	int string_length = s.length();
	// loop through all the elements in the string
	for (int i = 0; i < string_length; i++)
	{
		// decode the int value in the substring
		int_from_str = charToInt(*(charr_arr + i));
		// store the int value in the integer array in the proper row
		*(*(pArray + row) + i) = int_from_str;
	}

	return 0;
}

// A recursive function to replace 
// previous color 'currColor' at  '(x, y)'  
// and all surrounding pixels of (x, y) 
// with new color 'newColor'
int doFloodFill(int** p2DIntArr, int row, int col, int color, int num_rows, int num_cols)
{
	// Base cases
	if (row < 0 || row >= num_rows || col < 0 || col >= num_cols) // if point is outside array then do not continue
	{
		return 0;
	}
	else if (*(*(p2DIntArr + row) + col) != -1)
	{
		if (*(*(p2DIntArr + row) + col) == -2) // if point is a border than do not continue
		{
			return 0;
		}
		else if (*(*(p2DIntArr + row) + col) == color) // if point is already colored than do not continue
		{
			return 0;
		}
	}
	else if (*(*(p2DIntArr + row) + col) == -1)
	{
		// Replace the color at cell (x, y) 
		*(*(p2DIntArr + row) + col) = color;

		// Recursively call for north, east, south and west 
		doFloodFill(p2DIntArr, row + 1, col, color, num_rows, num_cols);
		doFloodFill(p2DIntArr, row - 1, col, color, num_rows, num_cols);
		doFloodFill(p2DIntArr, row, col + 1, color, num_rows, num_cols);
		doFloodFill(p2DIntArr, row, col - 1, color, num_rows, num_cols);
	}

	return 0;
}

int bubbleSort(int* pIntArray, int num_elements)
{
	int i, j, temp, pass = 0;
	
	for (i = 0; i < num_elements; i++)
	{
		for (j = i + 1; j < num_elements; j++)
		{
			if (*(pIntArray + j) < *(pIntArray + i) )
			{
				temp = *(pIntArray + i);
				*(pIntArray + i) = *(pIntArray + j);
				*(pIntArray + j) = temp;
			}
		}
		pass++;
	}

	return 0;
}