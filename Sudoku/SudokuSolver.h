#pragma once

#include "Main.h"
#include <utility>
#include <cmath>

#define STRUCTURE 9
#define SPACE " "
#define HORIZONATALINE "------------------------------------"
#define VERTICALINE "|"

class SudokuSolver
{
public:
	void init();
	void printGrid();
	bool rules(int Check, int Flag, int numCheck);
	bool checkCube(int startCol, int startRow, int numCheck);
	std::pair <int, int> getUnsignedValue();
	bool legal(std::pair <int, int> locCheck, int numCheck);
	bool algorthim();
	int** getGrid();
	void setMap(int g[9][9]);
	~SudokuSolver();
private:
	int sMap[STRUCTURE][STRUCTURE];
	int** tempArr;
	std::pair <int, int> full;
};

