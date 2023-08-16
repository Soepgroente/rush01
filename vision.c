#include "sudoku.h"

int n;

static int*	copy_array(int* line, int n)
{
	int*	copy;

	copy = malloc(n * sizeof(int));
	if (!copy)
		some_error();
	for (int i = 0; i < n; i++)
		copy[i] = line[i];
	return (copy);
}

static bool	in_array(int x, int n, int* line)
{
	for (int i = 0; i < n; i++)
	{
		if (line[i] == x)
			return (true);
	}
	return (false);
}

static int	min_vision(int* line)
{
	int		i = 0;
	int		num = n;
	int		high = 0;
	int		count = 0;
	int*	tmp;

	tmp = copy_array(line, n);
	while (i < n && tmp[i] == 0)
	{
		if (in_array(num, n, tmp) == false)
		{
			tmp[i] = num;
			i++;
		}
		else if (num > 0)
			num--;
		else
			i++;
	}
	for (int i = 0; i < n; i++)
	{
		if (tmp[i] > high)
		{
			high = tmp[i];
			count++;
		}
	}
	free(tmp);
	return (count);
}

static int	max_vision(t_grid* grid, int* line)
{
	int		i = 0;
	int		num;
	int		high = 0;
	int		count = 0;
	int*	tmp;

	tmp = copy_array(line, grid->n);
	if (line[0] == grid->n)
	{
		count = 1;
		free(tmp);
		return (count);
	}
	num = (line[0] + 1);
	while (i < grid->n)
	{
		while (tmp[i] == 0)
		{
			if (in_array(num, grid->n, tmp) == false)
				tmp[i] = num;
			else if (num < grid->n)
				num++;
			else
				break ;
		}
		i++;
	}
	for (int i = 0; i < grid->n; i++)
	{
		if (tmp[i] > high)
		{
			high = tmp[i];
			count++;
		}
	}
	// printf("Max: %d\n", count);
	// print_single_line(tmp, grid->n);
	free(tmp);
	return (count);
}

static bool	skyscrape_left(t_grid* grid, int x)
{
	int	min;
	int max;

	min = min_vision(grid, grid->row);
	max = max_vision(grid, grid->row);
	if (min > grid->sky_left[x] || max < grid->sky_left[x])
		return (false);
	return (true);
}

static bool	skyscrape_right(t_grid* grid, int x)
{
	int	min;
	int max;

	min = min_vision(grid, grid->rev_row);
	max = max_vision(grid, grid->rev_row);
	if (min > grid->sky_right[x] || max < grid->sky_right[x])
		return (false);
	return (true);
}

static bool	skyscrape_up(t_grid* grid, int y)
{
	int	min;
	int max;

	min = min_vision(grid, grid->col);
	max = max_vision(grid, grid->col);
	if (min > grid->sky_up[y] || max < grid->sky_up[y])
		return (false);
	return (true);
}

static bool	skyscrape_down(t_grid* grid, int y)
{
	int	min;
	int max;

	min = min_vision(grid, grid->rev_col);
	max = max_vision(grid, grid->rev_col);
	if (min > grid->sky_down[y] || max < grid->sky_down[y])
		return (false);
	return (true);
}

static bool	check_row(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < grid->n)
	{
		if (board[x][i][0] == try)
			return (false);
		grid->row[i] = board[x][i][0];
		grid->rev_row[i] = board[x][grid->n - 1 - i][0];
		i++;
	}
	grid->row[y] = try;
	grid->rev_row[grid->n - 1 - y] = try;
	return (true);
}

static bool	check_column(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < grid->n)
	{
		if (board[i][y][0] == try)
			return (false);
		grid->col[i] = board[i][y][0];
		grid->rev_col[i] = board[grid->n - 1 - i][y][0];
		i++;
	}
	grid->col[x] = try;
	grid->rev_col[grid->n - 1 - x] = try;
	return (true);
}

bool	check_if_possible(t_grid* grid, int*** board, int x, int y, int try)
{
	n = grid->n;
	if (check_row(grid, board, x, y, try) == true && \
		check_column(grid, board, x, y, try) == true && \
		skyscrape_left(grid, board, x) == true && \
		skyscrape_right(grid, board, x) == true && \
		skyscrape_up(grid, board, y) == true && \
		skyscrape_down(grid, board, y) == true)
		return (true);
	return (false);
}