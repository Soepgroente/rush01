#include "sudoku.h"

int	count_vision(int** line)
{
	int count = 0;
	int high = 0;

	for (int i = 0; i < size; i++)
	{
		if (line[i][0] > high)
		{
			high = line[i][0];
			count++;
		}
	}
	return (count);
}

int	count_rev_vision(int** line)
{
	int count = 0;
	int high = 0;

	for (int i = size - 1; i >= 0; i--)
	{
		if (line[i][0] > high)
		{
			high = line[i][0];
			count++;
		}
	}
	return (count);
}

bool	in_array(int** line, int num)
{
	for (int i = 0; i < size; i++)
	{
		if (line[i][0] == num)
			return (true);
	}
	return (false);
}

bool	skyscraper_vision(int** line, int clue1, int clue2)
{
	for (int i = 0; i < size; i++)
	{
		if (line[i][0] == 0)
		{
			for (int try = size; try > 0; try--)
			{
				if (line[i][try] != 0 && in_array(line, try) == false)
				{
					line[i][0] = try;
					if (skyscraper_vision(line, clue1, clue2) == true)
						return (true);
					line[i][0] = 0;
				}
			}
			return (false);
		}
		// if (in_array(line, try) == false)
	}
	if (count_vision(line) != clue1 || count_rev_vision(line) != clue2)
		return (false);
	return (true);
}