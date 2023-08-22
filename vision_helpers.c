#include "sudoku.h"

int*	copy_array(int* line)
{
	int*	copy;

	copy = malloc(size * sizeof(int));
	if (!copy)
		exit(EXIT_FAILURE);
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

int	count_vision(int* line)
{
	int count = 0;
	int high = 0;
	for (int i = 0; i < size; i++)
	{
		if (line[i] > high)
		{
			high = line[i];
			count++;
		}
	}
/* 	puts("\nLine / count:");
	for (int x = 0; x < size; x++)
		printf("%d", line[x]);
	printf("; %d\n", count); */
	free(line);
	return (count);
}

int	min_vision(int* line)
{
	int		i = 0;
	int		num = size;
	int*	copy;

	copy = copy_array(line);
	while (copy[i] != 0 && i < size)
		i++;
	while (in_array(num, copy) == true)
		num--;
	copy[i] = num;
	return (count_vision(copy));
}

int	max_vision(int* line)
{
	int		i = 0;
	int		num;
	int*	copy;
	// static int count = 0;

	copy = copy_array(line);
	num = copy[0] + 1;
	while (copy[i] != 0 && i < size)
		i++;
	while (i < size && num <= size)
	{
		if (copy[i] == 0)
		{
			if (in_array(num, copy) == false)
			{
				copy[i] = num;
				i++;
				num++;
			}
			else
				num++;
		}
		else
			i++;
	}
 	// puts("\nMax vision:");
	// for (int x = 0; x < size; x++)
	// 	printf("%d", copy[x]);
	// count++;
	// if (count == 10)
	// 	exit(0);
	return (count_vision(copy));
}
