#include "sudoku.h"

int*	copy_array(int* line)
{
	int*	copy;

	copy = malloc(size * sizeof(int));
	if (!copy)
		return (NULL);
	for (int i = 0; i < size; i++)
		copy[i] = line[i];
	return (copy);
}

bool	in_array(int x, int* line)
{
	for (int i = 0; i < size; i++)
	{
		if (line[i] == x)
			return (true);
	}
	return (false);
}

int	count_vision(int** line)
{
	int count = 0;
	int high = 0;
	for (int i = 0; i < size; i++)
	{
		if ((*line)[i] > high)
		{
			high = (*line)[i];
			count++;
		}
	}
	free(*line);
	return (count);
}

int	min_vision(int* line)
{
	int		i = 0;
	int		num = size;
	int*	copy;

	copy = copy_array(line);
	if (!copy)
		return (-1);
	while (i < size && copy[i] == 0)
	{
		if (in_array(num, copy) == false)
		{
			copy[i] = num;
			i++;
		}
		else if (num > 0)
			num--;
		else
			i++;
	}
	return (count_vision(&copy));
}

int	max_vision(int* line)
{
	int		i = 0;
	int		num;
	int*	copy;

	copy = copy_array(line);
	if (!copy)
		return (-1);
	if (line[0] == size)
		return (free(copy), 1);
	num = (line[0] + 1);
	while (i < size)
	{
		while (copy[i] == 0)
		{
			if (in_array(num, copy) == false)
				copy[i] = num;
			else if (num < size)
				num++;
			else
				break ;
		}
		i++;
	}
	return (count_vision(&copy));
}
