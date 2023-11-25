#include "sudoku.h"

static bool	skyscrape_leftright(t_grid* grid, int x)
{
	if (double_vision(grid->row, grid->sky_left[x], grid->sky_right[x]) == true)
		return (true);
	return (false);
}

static bool	skyscrape_updown(t_grid* grid, int y)
{
	if (double_vision(grid->col, grid->sky_up[y], grid->sky_down[y]) == true)
		return (true);
	return (false);
}

static bool	check_row(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	if (in_row(board[x], try) == true)
		return (false);
	while (i < size)
	{
		for (int pos = 0; pos <= size; pos++)
			grid->row[i][pos] = board[x][i][pos];
		i++;
	}
	grid->row[y][0] = try;
	delete_rowcol_cell(board, x, y, try);
	return (true);
}

static bool	check_column(t_grid* grid, int*** board, int x, int y, int try)
{
	int i = 0;

	if (in_column(board, y, try) == true)
		return (false);
	while (i < size)
	{
		for (int pos = 0; pos <= size; pos++)
			grid->col[i][pos] = board[i][y][pos];
		i++;
	}
	grid->col[x][0] = try;
	delete_rowcol_cell(board, x, y, try);
	return (true);
}

bool	check_if_possible(t_grid* grid, int*** board, int x, int y, int try)
{
	if (check_row(grid, board, x, y, try) == true && \
		check_column(grid, board, x, y, try) == true && \
		skyscrape_leftright(grid, x) && \
		skyscrape_updown(grid, y) == true)
		return (true);
	return (false);
}