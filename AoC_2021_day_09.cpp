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

const int TOP_LEFT = 1;
const int TOP_RIGHT = 1;
const int BOTTOM_LEFT = 1;
const int BOTTOM_RIGHT = 1;

const int TOP_LEFT_CORNER = 1;
const int TOP_RIGHT_CORNER = 1;
const int BOTTOM_LEFT_CORNER = 1;
const int BOTTOM_RIGHT_CORNER = 1;

const string INPUT_FILE = "heights_test.txt"; // filename with the input data

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
int singleStrToInt(string s)
{
	// input param: string s: the string that has 1 element to convert to an int

	int output_int = 0;

	// check if input has length 1
	if (s.length() == 1)
	{
		// check which string is the input and return the int representation
		if (s == "0")
			output_int = 0;
		else if (s == "1")
			output_int = 1;
		else if (s == "2")
			output_int = 2;
		else if (s == "3")
			output_int = 3;
		else if (s == "4")
			output_int = 4;
		else if (s == "5")
			output_int = 5;
		else if (s == "6")
			output_int = 6;
		else if (s == "7")
			output_int = 7;
		else if (s == "8")
			output_int = 8;
		else if (s == "9")
			output_int = 9;
	}
	else
	{
		bool bool_talktalk = true; // if true than we are debugging
		if (bool_talktalk)
		{
			cout << "Warning: input string doesn't have required length 1!";
		}
	}

	return output_int;
}

// this function has a string as input and decodes it into a multidimensional array of ints
int decodeStr(string s, int** pArray, int row)
{
	// input param: string s: this is the string to convert to an integer array
	// input param: int int_array[][LEN_LINES]: this array receives the integer values from the string (by reference)
	// input param: int row: this is the row index in the integer array

	string sub_string = ""; // this variable will receive the substring
	int int_from_str = 0; // this variable  contains the int that is decoded from the substring

	// how many elements in this string?
	int string_length = s.length();
	// loop through all the elements in the string
	for (int i = 0; i < string_length; i++)
	{
		// get the element via substring routine
		sub_string = s.substr(i, 1);
		// decode the int value in teh substring
		int_from_str = singleStrToInt(sub_string);
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
	edge_info_array[0] = 0; // TOP_LEFT
	edge_info_array[1] = 0; // TOP_RIGHT
	edge_info_array[2] = 0; // BOTTOM_LEFT
	edge_info_array[3] = 0; // BOTTOM_RIGHT
	edge_info_array[4] = 0; // TOP_LEFT_CORNER
	edge_info_array[5] = 0; // TOP_RIGHT_CORNER
	edge_info_array[6] = 0; // BOTTOM_LEFT_CORNER
	edge_info_array[7] = 0; // BOTTOM_RIGHT_CORNER

	// get edge info
	if (row == 0) // at top
	{
		edge_info_array[0] = TOP_LEFT;
		edge_info_array[1] = TOP_RIGHT;

		if (col == 0) // at left
		{
			edge_info_array[4] = TOP_LEFT_CORNER;
		}
		else if (col == LEN_LINE - 1) // at right
		{
			edge_info_array[5] = TOP_RIGHT_CORNER;
		}
	}
	else if (row == NUM_LINES - 1) // at bottom
	{
		edge_info_array[2] = BOTTOM_LEFT;
		edge_info_array[3] = BOTTOM_RIGHT;

		if (col == 0) // at left
		{
			edge_info_array[6] = BOTTOM_LEFT_CORNER;
		}
		else if (col == LEN_LINE - 1) // at right
		{
			edge_info_array[7] = BOTTOM_RIGHT_CORNER;
		}
	}

	if (col == 0) // at left
	{
		edge_info_array[0] = TOP_LEFT;
		edge_info_array[2] = BOTTOM_LEFT;
	}
	else if (col == LEN_LINE - 1) // at right
	{
		edge_info_array[1] = TOP_RIGHT;
		edge_info_array[3] = BOTTOM_RIGHT;
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

	int edge_check = edge_info_array[0] + edge_info_array[1] + edge_info_array[2] + edge_info_array[3];
	int corner_check = edge_info_array[4] + edge_info_array[5] + edge_info_array[6] + edge_info_array[7];

	if (edge_check > 0)
	{
		if (corner_check == 0)
		{
			if (edge_info_array[0] == TOP_LEFT && edge_info_array[1] == TOP_RIGHT) // top edge
			{
				output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row + 1) + col), 999);
			}
			else if (edge_info_array[2] == BOTTOM_LEFT && edge_info_array[3] == BOTTOM_RIGHT) // bottom edge
			{
				output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), 999);
			}
			else if (edge_info_array[0] == TOP_LEFT && edge_info_array[2] == BOTTOM_LEFT) // left edge
			{
				output_result = checkMinValue(check_value, *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col), *(*(pArray + row) + col + 1), 999);
			}
			else if (edge_info_array[1] == TOP_RIGHT && edge_info_array[3] == BOTTOM_RIGHT) // right edge
			{
				output_result = checkMinValue(check_value, *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col), *(*(pArray + row) + col - 1), 999);
			}
		}
		else if (corner_check == 1)
		{
			if (edge_info_array[4] == TOP_LEFT_CORNER)
			{
				output_result = checkMinValue(check_value, *(*(pArray + row) + col + 1), *(*(pArray + row + 1) + col), 999, 999);
			}
			else if (edge_info_array[5] == TOP_RIGHT_CORNER)
			{
				output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row + 1) + col), 999, 999);
			}
			else if (edge_info_array[6] == BOTTOM_LEFT_CORNER)
			{
				output_result = checkMinValue(check_value, *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), 999, 999);
			}
			else if (edge_info_array[7] == BOTTOM_RIGHT_CORNER)
			{
				output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row - 1) + col), 999, 999);
			}
		}
	}
	else
	{
		output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col));
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
			// cout << "edge_info_array   " << i << " " << j << " ";
			// cout << edge_info_array[0] << edge_info_array[1] << edge_info_array[2] << edge_info_array[3];
			// cout << edge_info_array[4] << edge_info_array[5] << edge_info_array[6] << edge_info_array[7] << "\n";
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

	int stop_val;
	for (;;)
	{
		cout << "\nPress 0 to stop\n";
		cin >> stop_val;
		if (!stop_val)
		{
			break;
		}
	}
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
