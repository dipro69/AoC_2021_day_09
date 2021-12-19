#pragma once
class CBasin
{
public:
	int setCoordinates(int in_row, int in_col);
	int getRow();
	int getCol();
	int setIndex(int in_index);
	int getIndex();
	int setRiskLevel(int in_risk_level);
	int getRiskLevel();
	int setNumElements(int in_num_elements);
private:
	int row;
	int col;
	int index;
	int risk_level;
	int num_elements;
};

