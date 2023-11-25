#include "sudoku.h"

/*	Checks if a number is already somewhere in the row (or line)	*/

bool	in_row(int** line, int num)
{
	for (int i = 0; i < size; i++)
	{
		if (line[i][0] == num)
			return (true);
	}
	return (false);
}

/*	Checks whether a number is already somewhere in the column	*/

bool	in_column(int*** board, int col, int num)
{
	for (int i = 0; i < size; i++)
	{
		if (board[i][col][0] == num)
			return (true);
	}
	return (false);
}

/*	Checks whether a cell only contains one option, returning 0 if it has multiple	*/

int	alone_in_cell(int* cell)
{
	int	num = 0;

	for (int i = 1; i <= size; i++)
	{
		if (cell[i] != 0)
		{
			if (num == 0)
				num = i;
			else
				return (0);
		}
	}
	return (num);
}

/*	Checks whether the supplied number can only be placed in 1 cell in a row,
	returning 0 if this is not the case	*/

int	alone_in_row(int** row, int num)
{
	int pos = 0;

	for (int i = 0; i < size; i++)
	{
		if (row[i][num] != 0)
		{
			if (pos == 0)
				pos = i;
			else
				return (0);
		}
	}
	return (pos);
}

/*	Checks whether the supplied number can only be placed in 1 cell in a column,
	returning 0 if this is not the case	*/

int	alone_in_column(int*** board, int col, int num)
{
	int pos = 0;

	for (int i = 0; i < size; i++)
	{
		if (board[i][col][num] != 0)
		{
			if (pos == 0)
				pos = i;
			else
				return (0);
		}
	}
	return (pos);
}

/*	Counts amount of visible skyscrapers, returning "DEAD_END" if it counts
	a different number than the clue specifies	*/

int	count_vision(int** line, int clue)
{
	int count = 0;
	int	maybe = 0;
	int high = 0;
	int i = 0;

	while (i < size && high < size)
	{
		if (line[i][0] == 0)
			maybe++;
		else if (line[i][0] > high)
		{
			high = line[i][0];
			count++;
		}
		i++;
	}
	if (maybe == 0 && count != clue)
		return (DEAD_END);
	else if (count + maybe < clue)
		return (DEAD_END);
	return (count);
}

/*	Count_vision modified to work in the opposite direction	*/

int	count_rev_vision(int** line, int clue)
{
	int count = 0;
	int	maybe = 0;
	int high = 0;
	int i = size - 1;

	while (i >= 0 && high < size)
	{
		if (line[i][0] == 0)
			maybe++;
		if (line[i][0] > high)
		{
			high = line[i][0];
			count++;
		}
		i--;
	}
	if (maybe == 0 && count != clue)
		return (DEAD_END);
	else if (count + maybe < clue)
		return (DEAD_END);
	return (count);
}

bool	double_vision(int** line, int clue1, int clue2)
{
	if (count_vision(line, clue1) != DEAD_END || \
		count_rev_vision(line, clue2) != DEAD_END)
	{
		return (false);
	}
	return (true);
}