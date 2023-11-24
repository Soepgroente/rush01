#include "sudoku.h"

/*	Copies a line	*/

void	copy_line(int** src_line, int** dest_line)
{
	for (int x = 0; x < size; x++)
		for (int y = 0; y <= size; y++)
			dest_line[x][y] = src_line[x][y];
}

/*	Counts amount of visible skyscrapers, returning -1 if it encounters 
	an unsolved number before encountering the tallest building	*/

int	count_vision(int** line, int clue)
{
	int count = 0;
	int high = 0;
	int i = 0;

	while (i < size && high < size)
	{
		if (line[i][0] == 0)
		{
			printf("high: %d, count: %d\n", high, 0);
			print_single_line(line);
			return (0);
		}
		if (line[i][0] > high)
		{
			high = line[i][0];
			count++;
		}
		i++;
	}
	printf("high: %d, count: %d, clue: %d\n", high, count, clue);
	print_single_line(line);
	if (count != clue)
		return (-1);
	return (count);
}

/*	Counts amount of visible skyscrapers from the opposite direction, returning -1 if it encounters 
	an unsolved number before encountering the tallest building	*/

int	count_rev_vision(int** line, int clue)
{
	int count = 0;
	int high = 0;
	int i = size - 1;

	while (i >= 0 && high < size)
	{
		if (line[i][0] == 0)
		{
			printf("(reverse) high: %d, count: %d\n", high, 0);
			print_single_line(line);
			return (0);
		}
		if (line[i][0] > high)
		{
			high = line[i][0];
			count++;
		}
		i--;
	}
	printf("(reverse) high: %d, count: %d, clue: %d\n", high, count, clue);
	print_single_line(line);
	if (count != clue)
		return (-1);
	return (count);
}

/*	Checks if a number is already filled in somewhere	*/

bool	in_array(int** line, int num)
{
	for (int i = 0; i < size; i++)
	{
		if (line[i][0] == num)
			return (true);
	}
	return (false);
}

/*	Tries to find a configuration for a row or column which obeys the skyscraper clues on both sides	*/

bool	skyscraper_vision(int*** line, int clue1, int clue2)
{
	int res1, res2;

	line++;
	copy_line((*(line - 1)), *line);
	for (int i = 0; i < size; i++)
	{
		if ((*line)[i][0] == 0)
		{
			for (int try = size; try > 0; try--)
			{
				if ((*line)[i][try] != 0 && in_array(*line, try) == false)
				{
					// print_single_line(*line);
					(*line)[i][0] = try;
					clear_row_cell(*line, try, i);
					if (solve_line(*line) == true)
					{
						puts("Before counting:");
						print_single_line(*line);
						res1 = count_vision(*line, clue1); res2 = count_rev_vision(*line, clue2);
						if (res1 == -1 || res2 == -1)
							break ;
						else if (res1 == clue1 && res2 == clue2)
							return (/*print_single_line(*line), */puts("true"), true);
						else if (skyscraper_vision(line, clue1, clue2) == true)
							return (/*print_single_line(*line), */puts("SUPERtrue"), true);
					}
					copy_line((*(line - 1)), *line);
				}
			}
			copy_line((*(line - 1)), *line);
			line--;
			return (puts("false"), false);
		}
	}
	if (count_vision(*line, clue1) != clue1 || count_rev_vision(*line, clue2) != clue2)
		return (puts("SUPERfalse"), false);
	return (true);
}