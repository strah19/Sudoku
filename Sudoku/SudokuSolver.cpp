#include "SudokuSolver.h"

void SudokuSolver::init()
{
	srand(time(NULL));
	full.first = 9;
	full.second = 9;

	std::pair <int, int> leg;
	int l = 0;
	int r;
	while (l < 1)
	{
		leg = getUnsignedValue();
		r = rand() % 9 + 1;
		sMap[leg.first][leg.second] = r;
		if (algorthim()) {
			l = 1;
		}
	}
	l = 0;
	int randI, randJ;
	int c = 0;

	while (l < 1)
	{
		c++;
		randI = rand() % 9;
		randJ = rand() % 9;

		sMap[randI][randJ] = 0;

		if (c == 80)
			l = 1;
	}
}

SudokuSolver::~SudokuSolver()
{
	delete tempArr;
}

void SudokuSolver::printGrid()
{
	for (int i = 0; i < STRUCTURE; i++) {

		std::cout << SPACE << std::endl;
		std::cout << HORIZONATALINE << std::endl;

		for (int j = 0; j < STRUCTURE; j++) {
			std::cout << SPACE;
			std::cout << sMap[i][j];
			std::cout << SPACE;
			std::cout << VERTICALINE;
		}
	}
	std::cout << std::endl << HORIZONATALINE << std::endl;
}

bool SudokuSolver::rules(int Check, int Flag, int numCheck)
{
	if (!Flag) {
		for (int i = 0; i < STRUCTURE; i++) {
			if (sMap[Check][i] == numCheck) {
				return true;
			}
		}
	}
	if (Flag) {
		for (int i = 0; i < STRUCTURE; i++) {
			if (sMap[i][Check] == numCheck) {
				return true;
			}
		}
	}
	return false;
}

bool SudokuSolver::checkCube(int startCol, int startRow, int numCheck)
{
	for (int i = 0; i < STRUCTURE / 3; i++) {
		for (int j = 0; j < STRUCTURE / 3; j++) {
			if (sMap[i + startCol][j + startRow] == numCheck) {
				return true;
			}
		}
	}
	return false;
}

std::pair<int, int> SudokuSolver::getUnsignedValue()
{
	for (int i = 0; i < STRUCTURE; i++) {
		for (int j = 0; j < STRUCTURE; j++) {
			if (sMap[i][j] == 0) {
				return std::make_pair(i, j);
			}
		}
	}
	return std::make_pair(9, 9);
}

bool SudokuSolver::legal(std::pair <int, int> locCheck, int numCheck)
{
	return !rules(locCheck.first, 0, numCheck) && !rules(locCheck.second, 1, numCheck) && !checkCube(locCheck.first - locCheck.first % 3, locCheck.second - locCheck.second % 3, numCheck);
}

bool SudokuSolver::algorthim()
{
	if (full == getUnsignedValue())
	{
		return true;
	}

	std::pair <int, int> unSignedPos = getUnsignedValue();

	for (int value = 1; value <= 9; value++) {
		if (legal(unSignedPos, value))
		{
			sMap[unSignedPos.first][unSignedPos.second] = value;
			if (algorthim())
			{
				return true;
			}
			sMap[unSignedPos.first][unSignedPos.second] = 0;
		}
	}

	return false;
}

int** SudokuSolver::getGrid()
{
	tempArr = new int* [STRUCTURE];
	for (int i = 0; i < STRUCTURE; i++) {
		tempArr[i] = new int[STRUCTURE];
		for (int j = 0; j < STRUCTURE; j++) {
			tempArr[i][j] = sMap[i][j];
		}
	}
	return tempArr;
}

void SudokuSolver::setMap(int g[9][9])
{
	for (int i = 0; i < STRUCTURE; i++) {
		for (int j = 0; j < STRUCTURE; j++) {
			sMap[i][j] = g[i][j];
		}
	}
}