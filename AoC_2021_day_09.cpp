// AoC_2021_day_09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include "CBasin.h"
#include "StackNode.cpp"

using namespace std;

enum class Edges{NO_EDGE_OR_CORNER, TOP_LEFT_CORNER, TOP_EDGE, TOP_RIGHT_CORNER, RIGHT_EDGE, BOTTOM_RIGHT_CORNER, BOTTOM_EDGE, BOTTOM_LEFT_CORNER, LEFT_EDGE};

const int NUM_LINES = 5; // constant for number of lines in file to read
const int LEN_LINE = 10; // constant for number of digits in an input line in file to read

// const int LOW_POINT_COUNT = 237; // constant for number of low points in the data
const int LOW_POINT_COUNT = 4; // constant for number of low points in the data

const string INPUT_FILE = "Data/heights_test.txt"; // filename with the input data
const int LARGE_DUMMY_VALUE = 999;

int getInputData(string* input_data, string file_name);
int charToInt(char c);
int decodeStr(string s, int** pArray, int row);
Edges getEdgeInfo(int row, int col);
int checkMinValue(int v, int first, int second, int third, int fourth);
int calcLowPoint(int** pArray, Edges input_edge_info, int row, int col);
int printBasinData(CBasin* pBasin);
int calculateBasinSize(CBasin* pBasin, int** pArray);
int algorithmDay9(int** pArray, CBasin* pArray_low_points);
int runDay9();
int testStackNode();

int main()
{
	// runDay9();

	testStackNode();

	cout << "\n";
	system("pause");
	return 0;
}

// this function opens a file and reads the lines into a string array
int getInputData(string* input_data, string file_name)
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
		*(input_data + i) = line;
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

// this function delivers the edge info according to our position in the multidimensional integer array
Edges getEdgeInfo(int row, int col)
{
	// input param: int row, col: the position in the input data array

	// if row = 0 or row = NUM_LINES-1 we are at a row_edge (top, bottom), 3 adjacent values to consider
	// if col = 0 or col = LEN_LINE-1 we are at a col_edge (left, right), 3 adjacent values to consider
	// if we are at a row_edge and a col_edge we are at a corner (top_left, top_right, bottom_left, bottom_right), 2 adjacent values to consider
	// everywhere else in the array, 4 adjacent values to consider

	// reset edge info
	Edges output_result = Edges::NO_EDGE_OR_CORNER;
		
	// get edge info
	if (row == 0) // at top
	{
		output_result = Edges::TOP_EDGE;
		
		if (col == 0) // at left
		{
			output_result = Edges::TOP_LEFT_CORNER;
		}
		else if (col == LEN_LINE - 1) // at right
		{
			output_result = Edges::TOP_RIGHT_CORNER;
		}
	}
	else if (row == NUM_LINES - 1) // at bottom
	{
		output_result = Edges::BOTTOM_EDGE;
		
		if (col == 0) // at left
		{
			output_result = Edges::BOTTOM_LEFT_CORNER;
		}
		else if (col == LEN_LINE - 1) // at right
		{
			output_result = Edges::BOTTOM_RIGHT_CORNER;
		}
	}
	else if (col == 0) // at left
	{
		output_result = Edges::LEFT_EDGE;
	}
	else if (col == LEN_LINE - 1) // at right
	{
		output_result = Edges::RIGHT_EDGE;
	}

	return output_result;
}

// this function checks if the value in the current position is the lowest value compared to it's neighbours (adjacent values)
int checkMinValue(int v, int first, int second, int third, int fourth)
{
	// input param: int v: the value that is checked
	// input param: int first to fourth: the neighbourvalues to check

	int output_result = -1;

	if (v < first && v < second && v < third && v < fourth)
	{
		output_result = v;
		// cout << "got low point";
	}

	return output_result;
}

// this functions checks if current value is a low point
int calcLowPoint(int** pArray, Edges input_edge_info, int row, int col)
{
	// input param: int** pArray: pointer to the multidimensional int array
	// input param: Edges input_edge_info: the edge info to check for each position
	// input param: int row, col: coordinates for our current position

	// if row = 0 or row = NUM_LINES-1 we are at a row_edge (top, bottom), 3 adjacent values to consider
	// if col = 0 or col = LEN_LINE-1 we are at a col_edge (left, right), 3 adjacent values to consider
	// if we are at a row_edge and a col_edge we are at a corner (top_left, top_right, bottom_left, bottom_right), 2 adjacent values to consider
	// everywhere else in the array, 4 adjacent values to consider

	// calculate if current array value is the minimum value compared to adjacent values, if true then it is a low_point
	int output_result = -1;
	int check_value = *(*(pArray + row) + col);

	switch(input_edge_info)
	{
	case(Edges::NO_EDGE_OR_CORNER):
		output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col));
		break;
	case(Edges::TOP_EDGE): // top edge
		output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row + 1) + col), LARGE_DUMMY_VALUE);
		break;
	case(Edges::BOTTOM_EDGE): // bottom edge
		output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), LARGE_DUMMY_VALUE);
		break;
	case(Edges::LEFT_EDGE): // left edge
		output_result = checkMinValue(check_value, *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col), *(*(pArray + row) + col + 1), LARGE_DUMMY_VALUE);
		break;
	case(Edges::RIGHT_EDGE): // right edge
		output_result = checkMinValue(check_value, *(*(pArray + row - 1) + col), *(*(pArray + row + 1) + col), *(*(pArray + row) + col - 1), LARGE_DUMMY_VALUE);
		break;
	case(Edges::TOP_LEFT_CORNER):
		output_result = checkMinValue(check_value, *(*(pArray + row) + col + 1), *(*(pArray + row + 1) + col), LARGE_DUMMY_VALUE, LARGE_DUMMY_VALUE);
		break;
	case(Edges::TOP_RIGHT_CORNER):
		output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row + 1) + col), LARGE_DUMMY_VALUE, LARGE_DUMMY_VALUE);
		break;
	case(Edges::BOTTOM_LEFT_CORNER):
		output_result = checkMinValue(check_value, *(*(pArray + row) + col + 1), *(*(pArray + row - 1) + col), LARGE_DUMMY_VALUE, LARGE_DUMMY_VALUE);
		break;
	case(Edges::BOTTOM_RIGHT_CORNER):
		output_result = checkMinValue(check_value, *(*(pArray + row) + col - 1), *(*(pArray + row - 1) + col), LARGE_DUMMY_VALUE, LARGE_DUMMY_VALUE);
		break;
	default:
		break;
	}

	return output_result; // if -1 than no low point else return low point value
}

int printBasinData(CBasin* pBasin)
{
	// temporary variables to store the data that we will show in cout
	int	ti = pBasin->getIndex();
	int	tr = pBasin->getRow();
	int	tc = pBasin->getCol();
	int	trl = pBasin->getRiskLevel();

	cout << "Low point info " << ti << " " << " " << tr << " " << tc << " " << trl << "\n";
	
	return 0;
}

int calculateBasinSize(CBasin* pBasin, int** pArray)
{
	// reset the integer array with input data, set all non 9 values to -1
	// we are going to fill each basin with the index integer from it's origin low point (stored in CBasin object)
	// 
	// start at row, col from low point stored in pBasin and put in on the investigation stack as starting point
	// start while (stack size not 0) do 
	//	   investigate the top, bottom, left and right neighbours from current point on the stack
	//	   if neighbour = 9, don't sample that point further
	//     if neighbour another integer value, don't sample that point further
	//     if neighbour is an edge point, don't sample that point further
	//	   if neighbour = -1, store it as a point on the stack for further investigation
	//     when all 4 neigbours are investigated, store the index value in the central point,
	//     increment the number of sampled points, this is the size of the basin
	//	   load next stack item for investigation

	// reset the integer array with input data, set all non 9 values to -1
	// loop through all the int values
	int int_empty = -1;
	int int_print = 0;
	for (int i = 0; i < NUM_LINES; i++)
	{
		for (int j = 0; j < LEN_LINE; j++)
		{
			if ( *(*(pArray + i) + j) != 9 )
			{
				*(*(pArray + i) + j) = int_empty;
			}
			// check this
			int_print = *(*(pArray + i) + j);
			cout << int_print;
		}
		// check this
		cout << "\n";
	}

	return 0;
}

// this function runs the puzzle algorithm for AoC day9 part 1
int algorithmDay9(int** pArray, CBasin* pArray_low_points)
{
	// input param: int** pArray: pointer to the multidimensional int array

	// puzzle day 9: part 1

	Edges edge_info = Edges::NO_EDGE_OR_CORNER;
	int sum_risk_level = 0;
	int height = 0;
	int risk_level = -1;
	int low_point_counter = 0;

	// loop through all the int values
	for (int i = 0; i < NUM_LINES; i++)
	{
		for (int j = 0; j < LEN_LINE; j++)
		{
			// if row = 0 or row = NUM_LINES-1 we are at a row_edge (top, bottom), 3 adjacent values to consider
			// if col = 0 or col = LEN_LINE-1 we are at a col_edge (left, right), 3 adjacent values to consider
			// if we are at a row_edge and a col_edge we are at a corner (top_left, top_right, bottom_left, bottom_right), 2 adjacent values to consider
			// everywhere else in the array, 4 adjacent values to consider

			// first get edge info for current position in the array
			edge_info = getEdgeInfo(i, j);
			// calculate if lowest point and if so get height, if not receive -1
			height = calcLowPoint(pArray, edge_info, i, j);
			// if indeed a lowest point then get risk level and total with output result in sum
			if (height != -1)
			{
				// calculate risk level
				// The risk level of a low point is 1 plus its height
				risk_level = 1 + height;
				sum_risk_level = sum_risk_level + risk_level;
				cout << "risk_level: " << risk_level << "\n";

				// here starts day 9 part 2
				// store the low point coordinates in a list
				// we need this list to identify basins
				// and calculate the size of the basins
				// final step is to calculate the addition of all the sizes
				CBasin basin;
				basin.setCoordinates(i, j);
				basin.setIndex(low_point_counter);
				basin.setRiskLevel(risk_level);
				basin.setNumElements(0);
				*(pArray_low_points + low_point_counter) = basin;
				low_point_counter++;
			}

		}
	}

	for (int i = 0; i < LOW_POINT_COUNT; i++)
	{
		printBasinData((pArray_low_points + i));
	}

	calculateBasinSize(pArray_low_points, pArray);

	// calculate sum of all found risk levels
	return sum_risk_level;
}

// this function retrieves the data and runs the central algorithm
int runDay9()
{
	string* input_data = new string[NUM_LINES]; // string array for retrieving input data

	// memory allocated for elements of rows
	int** pArray = new int* [NUM_LINES];
	// memory allocated for array with all the low points in the data
	CBasin* pArray_low_points = new CBasin[LOW_POINT_COUNT];

	// memory allocated for  elements of each column.  
	for (int i = 0; i < NUM_LINES; i++)
	{
		*(pArray + i) = new int[LEN_LINE];
	}

	getInputData(input_data, INPUT_FILE); // read the data from file

	// convert input data strings to integers
	for (int i = 0; i < NUM_LINES; i++)
	{
		decodeStr(input_data[i], pArray, i);
	}

	// perform the central algorithm to get puzzle answer
	int sum = algorithmDay9(pArray, pArray_low_points);
	cout << "Sum of puzzle day 9 part 1 = " << sum;

	// free the allocated memory 
	delete[] pArray_low_points;

	for (int i = 0; i < NUM_LINES; i++)
	{
		delete[] pArray[i];
	}

	delete[] pArray;
	delete[] input_data;

	// return function value
	return 0;
}

// Driver code
int testStackNode()
{
	// create a new StackNode pointer
	StackNode* ptr_root = NULL;

	// push integers on the stack
	// we pass the push function a reference to the root pointer so we can change it
	push(&ptr_root, 10);
	push(&ptr_root, 20);
	push(&ptr_root, 30);

	// now we pop an element from the stack
	cout << pop(&ptr_root) << " popped from stack\n";
	// we investigate the current top element
	cout << "Top element is " << peek(ptr_root) << endl;

	cout << "Elements present in stack : ";
	//print all elements in stack :
	while (!isEmpty(ptr_root))
	{
		// print top element in stack
		cout << peek(ptr_root) << " ";
		// remove top element in stack
		pop(&ptr_root);
	}

	printINT_MIN();

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
