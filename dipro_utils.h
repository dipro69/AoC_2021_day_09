#include <string>
#include <iostream>

using namespace std;

#pragma once

int getInputData(string* ptr_input_data, string file_name);
int charToInt(char c);
int decodeStr(string s, int** pArray, int row);
int doFloodFill(int** p2DIntArr, int row, int col, int color, int num_rows, int num_cols);
int bubbleSort(int* pIntArray, int num_elements);