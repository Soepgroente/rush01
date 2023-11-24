#include "sudoku.h"

static bool	check_row_presence(int** line, int try)
{
	for (int i = 0; i < size; i++)
		if (line[i][0] == try)
			return (true);
	return (false);
}

/*	Removes try from the rest of the row and sets the other options in the cell to 0	*/

void	clear_row_cell(int** line, int try, int cell)
{
	for (int pos = 1; pos <= size; pos++)
		line[cell][pos] = 0;
	for (int pos = 0; pos < size; pos++)
		line[pos][try] = 0;
}

static int	alone_in_row(int** line)
{
	int	check = -1;
	int changes = 0;

	for (int try = 1; try <= size; try++)
	{
		if (check_row_presence(line, try) == false)
		{
			for (int y = 0; y < size; y++)
			{
				if (check == -1 && line[y][try] != 0)
					check = y;
				else if (line[y][try] != 0)
				{
					check = -2;
					break ;
				}
			}
			if (check == -1)
				return (-1);
			if (check >= 0)
			{
				line[check][0] = try;
				clear_row_cell(line, try, check);
				changes++;
			}
		}
		check = -1;
	}
	return (changes);
}

static int	alone_in_cell(int** line)
{
	int	check = -1;
	int changes = 0;

	for (int y = 0; y < size; y++)
	{
		if (line[y][0] == 0)
		{
			for (int try = 1; try <= size; try++)
			{
				if (check == -1 && line[y][try] != 0)
					check = y;
				else if (line[y][try] != 0)
				{
					check = -2;
					break ;
				}
			}
			if (check == -1)
				return (-1);
			if (check > 0)
			{
				line[y][0] = check;
				clear_row_cell(line, check, y);
				changes++;
			}
		}
		check = -1;
	}
	return (changes);
}

bool	solve_line(int** line)
{
	int changes = 1;
	int check;

	while (changes > 0)
	{
		changes = 0;
		check = alone_in_row(line);
		if (check == -1)
			return (false);
		changes += check;
		check = alone_in_cell(line);
		if (check == -1)
			return (false);
		changes += check;
	}
	return (true);
}
