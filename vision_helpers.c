#include "sudoku.h"

static void	free_line(int** line)
{
	for (int i = 0; i < size; i++)
		free(line[i]);
	free(line);
	line = NULL;
}

int**	copy_array(int** line)
{
	int**	copy;

	copy = malloc(size * sizeof(int*));
	if (!copy)
		some_error("Malloc fail");
	for (int i = 0; i < size; i++)
	{
		copy[i] = malloc((size + 1) * sizeof(int));
		if (!copy[i])
			some_error("Malloc fail");
	}
	for (int y = 0; y < size; y++)
		for (int z = 0; z <= size; z++)
			copy[y][z] = line[y][z];
	return (copy);
}

bool	in_array(int num, int** line)
{
	for (int i = 0; i < size; i++)
	{
		if (line[i][0] == num)
			return (true);
	}
	return (false);
}

int	count_vision(int** line)
{
	int count = 0;
	int high = 0;
	static int hi = 0;

	for (int i = 0; i < size; i++)
	{
		if (line[i][0] > high)
		{
			high = line[i][0];
			count++;
		}
	}
	print_single_line(line);
	free_line(line);
	hi++;
	if (hi == 10)
		exit(0);
	// printf("Count: %d\n\n", count);
	return (count);
}

int	min_vision(int** line)
{
	int		i = 0;
	int		high = 0;
	int		num = size;
	int**	copy;

	copy = copy_array(line);
	while (i < size && copy[i][0] != 0)
	{
		if (copy[i][0] > high)
			high = copy[i][0];
		i++;
	}
	
	while (in_array(num, copy) == true)
		num--;
	if (i < size && copy[i][0] == 0)
		copy[i][0] = num;
	// puts("Min");
	print_single_line(line);
	return (count_vision(copy));
}

int	max_vision(int** line)
{
	int**	copy;
	int i = 0;
	int num = size;
	int found = 0;

	copy = copy_array(line);
	if (in_array(num, copy) == false)
	{
		for (int x = num - 1; x >= 0; x--)
		{
			if (copy[x][num] != 0)
			{
				copy[x][0] = num;
				num--;
				break ;
			}
		}
	}
	while (in_array(num, copy) == false)
	{
		for (int x = size - 1; x >= 0; x--)
		{
			if (copy[x][num] != 0)
			{
				if (found == 0)
					found = x;
				else
				{
					found = 0;
					break ;
				}
			}
		}
		if (found != 0)
			copy[found][0] = num;
		num--;
		found = 0;
	}
	num = copy[0][0] + 1;
	while (i < size && num < size)
	{
		while (num < size && in_array(num, copy) == true)
			num++;
		while (i < size && copy[i][0] != 0)
			i++;
		if (i < size && copy[i][num] != 0)
			copy[i][0] = num;
		i++;
	}
	print_single_line(line);
	return (count_vision(copy));
}
