#include "sudoku.h"


static bool	skyscrape_left(t_grid* grid, int x)
{
	if (min_vision(grid->row) > grid->sky_left[x])
		return (false);
	if (max_vision(grid->row) < grid->sky_left[x])
		return (false);
	return (true);
}

static bool	skyscrape_right(t_grid* grid, int x)
{
	if (min_vision(grid->rev_row) > grid->sky_right[x])
		return (false);
	if (max_vision(grid->rev_row) < grid->sky_right[x])
		return (false);
	return (true);
}

static bool	skyscrape_up(t_grid* grid, int y)
{
	if (min_vision(grid->col) > grid->sky_up[y])
		return (false);
	if (max_vision(grid->col) < grid->sky_up[y])
		return (false);
	return (true);
}

static bool	skyscrape_down(t_grid* grid, int y)
{
	if (min_vision(grid->rev_col) > grid->sky_down[y])
		return (false);
	if (max_vision(grid->rev_col) < grid->sky_down[y])
		return (false);
	return (true);
}

static bool	check_row(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < size)
	{
		if (board[x][i][0] == try)
			return (false);
		grid->row[i] = board[x][i][0];
		grid->rev_row[i] = board[x][size - 1 - i][0];
		i++;
	}
	grid->row[y] = try;
	grid->rev_row[size - 1 - y] = try;
	// puts("\nRow");
	// for (int i = 0; i < size; i++)
	// 	printf("%d", grid->row[i]);
	// puts("\nRev_row");
	// for (int i = 0; i < size; i++)
	// 	printf("%d", grid->rev_row[i]);
	return (true);
}

static bool	check_column(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	while (i < size)
	{
		if (board[i][y][0] == try)
			return (false);
		grid->col[i] = board[i][y][0];
		grid->rev_col[i] = board[size - 1 - i][y][0];
		i++;
	}
	grid->col[x] = try;
	grid->rev_col[size - 1 - x] = try;
	// puts("\nCol");
	// for (int i = 0; i < size; i++)
	// 	printf("%d", grid->col[i]);
	// puts("\nRev_col");
	// for (int i = 0; i < size; i++)
	// 	printf("%d", grid->rev_col[i]);
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