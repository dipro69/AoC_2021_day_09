#include <string>
#include <iostream>

using namespace std;

#pragma once

int getInputData(string* ptr_input_data, string file_name);
int charToInt(char c);
int decodeStr(string s, int** pArray, int row);