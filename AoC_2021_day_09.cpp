// AoC_2021_day_09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int NUM_LINES = 5; // constant for number of lines in file to read
const int LEN_LINE = 10; // constant for number of digits in an input line in file to read

const int NUM_EDGES = 4;
const int NUM_CORNERS = 4;

const int TOP_EDGE = 1;
const int LEFT_EDGE = 2;
const int RIGHT_EDGE = 4;
const int BOTTOM_EDGE = 8;

const int TOP_LEFT_CORNER = 1;
const int TOP_RIGHT_CORNER = 2;
const int BOTTOM_LEFT_CORNER = 4;
const int BOTTOM_RIGHT_CORNER = 8;

const string INPUT_FILE = "Data/heights_test.txt"; // filename with the input data

// this function opens a file and reads the lines into a string array
int getInputData(string* input_data, string file_name)
{
	// input param: string input_data[]: array that receives the input strings from file (by reference)
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
		*(input_data + i) = line;
		i++;
	}

	// close file and free resources
	in.close();

	// return function value
	return 0;
}

// this function converts a string (length has to be 1) into an int digit
int charToInt(char c)
{
	// input param: string s: the string that has 1 element to convert to an int

	int output_int = 0;

	switch (c)
	{
		// check which string is the input and return the int representation
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
	// input param: int** pArray: this array receives the integer values from the string (by reference)
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

int getEdgeInfo(int edge_info_array[], int row, int col)
{
	// input param: int edge_info_array[]: contains information about the array edges so we can check where we are in the array

	// if row = 0 or row = NUM_LINES-1 we are at a row_edge (top, bottom), 3 adjacent values to consider
	// if col = 0 or col = LEN_LINE-1 we are at a col_edge (left, right), 3 adjacent values to consider
	// if we are at a row_edge and a col_edge we are at a corner (top_left, top_right, bottom_left, bottom_right), 2 adjacent values to consider
	// everywhere else in the array, 4 adjacent values to consider

	// reset edge_info_array
	edge_info_array[0] = 0; // no edges yet
	edge_info_array[1] = 0; // no corners yet
	
	// get edge info
	if (row == 0) // at top
	{
		edge_info_array[0] = TOP_EDGE; // 1
		
		if (col == 0) // at left
		{
			edge_info_array[0] = TOP_EDGE + LEFT_EDGE; // 3
			edge_info_array[1] = TOP_LEFT_CORNER; // 1
		}
		else if (col == LEN_LINE - 1) // at right
		{
			edge_info_array[0] = TOP_EDGE + RIGHT_EDGE; // 5
			edge_info_array[1] = TOP_RIGHT_CORNER; // 2
		}
	}
	else if (row == NUM_LINES - 1) // at bottom
	{
		edge_info_array[0] = BOTTOM_EDGE; // 8
		
		if (col == 0) // at left
		{
			edge_info_array[0] = BOTTOM_EDGE + LEFT_EDGE; // 10
			edge_info_array[1] = BOTTOM_LEFT_CORNER; // 4
		}
		else if (col == LEN_LINE - 1) // at right
		{
			edge_info_array[0] = BOTTOM_EDGE + RIGHT_EDGE; // 12
			edge_info_array[1] = BOTTOM_RIGHT_CORNER; // 8
		}
	}
	else if (col == 0) // at left
	{
		edge_info_array[0] = LEFT_EDGE; // 2
	}
	else if (col == LEN_LINE - 1) // at right
	{
		edge_info_array[0] = RIGHT_EDGE; // 4
	}

	return 0;
}

int checkMinValue(int v, int first, int second, int third, int fourth)
{
	int output_result = -1;

	if (v < first && v < second && v < third && v < fourth)
	{
		output_result = v;
		// cout << "got low point";
	}

	return output_result;
}

// this functions checks if current value is a low point
int calcLowPoint(int** pArray, int edge_info_array[], int row, int col)
{
	// calculate if current array value is the minimum value compared to adjacent values, if true then it is a low_point
	int output_result = -1;
	int check_value = *(*(pArray + row) + col);

	int edge_check = edge_info_array[0];
	int corner_check = edge_info_array[1];

	if (edge_check == 0 && corner_check == 0)
	{
		output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col));
	}
	else if (edge_check > 0 && corner_check == 0)
	{
		switch (edge_check)
		{
		case(TOP_EDGE): // top edge
			output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row + 1) + col), 999);
			break;
		case(BOTTOM_EDGE): // bottom edge
			output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), 999);
			break;
		case(LEFT_EDGE): // left edge
			output_result = checkMinValue(check_value, *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col), *(*(pArray + row) + col + 1), 999);
			break;
		case(RIGHT_EDGE): // right edge
			output_result = checkMinValue(check_value, *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col), *(*(pArray + row) + col - 1), 999);
			break;
		default:
			break;
		}
	}
	else if (corner_check > 0)
	{
		switch (corner_check)
		{
		case(TOP_LEFT_CORNER):
			output_result = checkMinValue(check_value, *(*(pArray + row) + col + 1), *(*(pArray + row + 1) + col), 999, 999);
			break;
		case(TOP_RIGHT_CORNER):
			output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row + 1) + col), 999, 999);
			break;
		case(BOTTOM_LEFT_CORNER):
			output_result = checkMinValue(check_value, *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), 999, 999);
			break;
		case(BOTTOM_RIGHT_CORNER):
			output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row - 1) + col), 999, 999);
			break;
		default:
			break;
		}
	}

	return output_result; // if -1 than no low point else return low point value
}

int puzzleDay9Part1(int** pArray)
{
	// puzzle day 9: part 1

	int edge_info_array[NUM_EDGES + NUM_CORNERS] = { 0,0,0,0,0,0,0,0 };
	int sum_risk_level = 0;
	int height = 0;
	int risk_level = -1;

	// loop through all the int values
	for (int i = 0; i < NUM_LINES; i++)
	{
		for (int j = 0; j < LEN_LINE; j++)
		{
			// if row = 0 or row = NUM_LINES-1 we are at a row_edge (top, bottom), 3 adjacent values to consider
			// if col = 0 or col = LEN_LINE-1 we are at a col_edge (left, right), 3 adjacent values to consider
			// if we are at a row_edge and a col_edge we are at a corner (top_left, top_right, bottom_left, bottom_right), 2 adjacent values to consider
			// everywhere else in the array, 4 adjacent values to consider

			getEdgeInfo(edge_info_array, i, j);
			height = calcLowPoint(pArray, edge_info_array, i, j);
			if (height != -1)
			{
				// calculate risk level
				// The risk level of a low point is 1 plus its height
				risk_level = 1 + height;
				sum_risk_level = sum_risk_level + risk_level;
				cout << "risk_level: " << risk_level << "\n";
			}

		}
	}

	// calculate sum of all found risk levels

	return sum_risk_level;
}

int runDay9Part1()
{
	string* input_data = new string[NUM_LINES]; // string array for retrieving input data

	// memory allocated for elements of rows
	int** pArray = new int* [NUM_LINES];
	// memory allocated for  elements of each column.  
	for (int i = 0; i < NUM_LINES; i++)
	{
		*(pArray + i) = new int[LEN_LINE];
	}

	string file_name = INPUT_FILE; // define our input file

	getInputData(input_data, file_name); // read the data from file

	for (int i = 0; i < NUM_LINES; i++)
	{
		decodeStr(input_data[i], pArray, i);
	}

	int sum = puzzleDay9Part1(pArray);
	cout << "Sum of puzzle day 9 part 1 = " << sum;

	// free the allocated memory 
	for (int i = 0; i < NUM_LINES; i++)
	{
		delete[] pArray[i];
	}
	delete[] pArray;
	delete[] input_data;

	// return function value
	return 0;
}

int main()
{
	runDay9Part1();
	cout << "\n";
	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
