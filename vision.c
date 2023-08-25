#include "sudoku.h"

static bool	skyscrape_left(t_grid* grid, int x)
{
	if (min_vision(grid->row) > grid->sky_left[x])
		return (false);
	if (max_vision(grid->row) < grid->sky_left[x])
		return (false);
	puts("Left true");
	return (true);
}

static bool	skyscrape_right(t_grid* grid, int x)
{
	if (min_vision(grid->rev_row) > grid->sky_right[x])
		return (false);
	if (max_vision(grid->rev_row) < grid->sky_right[x])
		return (false);
	puts("Right true");
	return (true);
}

static bool	skyscrape_up(t_grid* grid, int y)
{
	if (min_vision(grid->col) > grid->sky_up[y])
		return (false);
	if (max_vision(grid->col) < grid->sky_up[y])
		return (false);
	puts("Up true");
	return (true);
}

static bool	skyscrape_down(t_grid* grid, int y)
{
	if (min_vision(grid->rev_col) > grid->sky_down[y])
		return (false);
	if (max_vision(grid->rev_col) < grid->sky_down[y])
		return (false);
	puts("Down true");
	return (true);
}

static bool	check_row(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < size)
	{
		if (board[x][i][0] == try)
			return (false);
		for (int pos = 0; pos <= size; pos++)
		{
			grid->row[i][pos] = board[x][i][pos];
			grid->rev_row[i][pos] = board[x][size - 1 - i][pos];
		}
		i++;
	}
	grid->row[y][0] = try;
	grid->rev_row[size - 1 - y][0] = try;
	for (int i = 1; i <= size; i++)
	{
		grid->row[y][i] = 0;
		grid->rev_row[size - 1 - y][i] = 0;
	}
	puts("Row true");
	return (true);
}

static bool	check_column(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < size)
	{
		if (board[i][y][0] == try)
			return (false);
		for (int pos = 0; pos <= size; pos++)
		{
			grid->col[i][pos] = board[i][y][pos];
			grid->rev_col[i][pos] = board[size - 1 - i][y][pos];
		}
		i++;
	}
	grid->col[x][0] = try;
	grid->rev_col[size - 1 - x][0] = try;
	for (int i = 1; i <= size; i++)
	{
		grid->col[x][i] = 0;
		grid->rev_col[size - 1 - x][i] = 0;
	}
	puts("Col true");
	return (true);
}

bool	check_if_possible(t_grid* grid, int*** board, int x, int y, int try)
{
	if (check_row(grid, board, x, y, try) == true && \
		check_column(grid, board, x, y, try) == true && \
		skyscrape_left(grid, x) == true && \
		skyscrape_right(grid, x) == true && \
		skyscrape_up(grid, y) == true && \
		skyscrape_down(grid, y) == true)
		return (true);
	return (false);
}