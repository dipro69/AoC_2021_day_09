#include "CBasin.h"

int CBasin::setCoordinates(int in_row, int in_col)
{
	row = in_row;
	col = in_col;
	return 0;
}

int CBasin::getRow()
{
	return row;
}

int CBasin::getCol()
{
	return col;
}

int CBasin::setIndex(int in_index)
{
	index = in_index;
	return 0;
}

int CBasin::getIndex()
{
	return index;
}

int CBasin::setRiskLevel(int in_risk_level)
{
	risk_level = in_risk_level;
	return 0;
}

int CBasin::getRiskLevel()
{
	return risk_level;
}

int CBasin::setNumElements(int in_num_elements)
{
	num_elements = in_num_elements;
	return 0;
}
