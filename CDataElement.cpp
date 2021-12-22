# include "CDataElement.h"

int CDataElement::setCoordinates(int in_row, int in_col)
{
	row = in_row;
	col = in_col;
	return 0;
}

int CDataElement::getRow()
{
	return row;
}

int CDataElement::getCol()
{
	return col;
}

int CDataElement::setIndex(int in_index)
{
	index = in_index;
	return 0;
}

int CDataElement::getIndex()
{
	return index;
}

int CDataElement::setRiskLevel(int in_risk_level)
{
	risk_level = in_risk_level;
	return 0;
}

int CDataElement::getRiskLevel()
{
	return risk_level;
}

int CDataElement::setNumElements(int in_num_elements)
{
	num_elements = in_num_elements;
	return 0;
}
