#include "sudoku.h"

t_grid* global_grid;

void	delete_rowcol_cell(int*** board, int x, int y, int num)
{
	for (int i = 0; i < size; i++)
		board[x][i][num] = 0;
	for (int i = 0; i < size; i++)
		board[i][y][num] = 0;
	for (int i = 1; i <= size; i++)
		board[x][y][i] = 0;
}

/*	Removes any digits that are too high for the skyscraper clue to remain valid	*/

void	remove_options(t_grid* grid, int*** board)
{
	for (int x = 0; x < size; x++)
	{
		if (grid->sky_left[x] <= 2 && grid->sky_right[x] <= 2)
			for (int z = 1; z < size - 1; z++)
				board[x][z][size - 1] = 0;
		for (int y = 0; y < size; y++)
		{
			if (board[x][y][0] == 0)
			{
				for (int z = size + 2 - grid->sky_left[x] + y; z <= size; z++)
					board[x][y][z] = 0;
				for (int z = size + 1 - grid->sky_right[x] + size - y; z <= size; z++)
					board[x][y][z] = 0;
				for (int z = size + 2 - grid->sky_up[y] + x; z <= size; z++)
					board[x][y][z] = 0;
				for (int z = size + 1 - grid->sky_down[y] + size - x; z <= size; z++)
					board[x][y][z] = 0;
			}
		}
	}
	for (int y = 0; y < size; y++)
		if (grid->sky_up[y] <= 2 && grid->sky_down[y] <= 2)
			for (int z = 1; z < size - 1; z++)
				board[z][y][size - 1] = 0;
}

/*	Find any digits that can only be placed in one place in a row	*/

int	place_single_row(int*** board)
{
	int num = 0;
	int changes = 0;

	for (int try = size; try > 0; try--)
	{
		for (int x = 0; x < size; x++)
		{
			if (in_row(board[x], try) == false)
			{
				num = alone_in_row(board[x], try);
				if (num != 0)
				{
					if (check_if_possible(global_grid, board, x, num, try) == false)
						return (DEAD_END);
					board[x][num][0] = try;
					delete_rowcol_cell(board, x, num, try);
					changes++;
				}
			}
		}
	}
	return (changes);
}

/*	Find any digits that can only be placed in one place in a column	*/

int	place_single_col(int*** board)
{
	int num = 0;
	int changes = 0;

	for (int try = size; try > 0; try--)
	{
		for (int y = 0; y < size; y++)
		{
			if (in_column(board, y, try) == false)
			{
				num = alone_in_column(board, y, try);
				if (num != 0)
				{
					if (check_if_possible(global_grid, board, num, y, try) == false)
						return (DEAD_END);
					board[num][y][0] = try;
					delete_rowcol_cell(board, num, y, try);
					changes++;
				}
			}
		}
	}
	return (changes);
}

/*	Find any cells that just have one option left	*/

int	place_single_cell(int*** board)
{
	int num = 0;
	int changes = 0;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (board[x][y][0] == 0)
			{
				num = alone_in_cell(board[x][y]);
				if (num != 0)
				{
					if (check_if_possible(global_grid, board, x, y, num) == true)
						return (DEAD_END);
					board[x][y][0] = num;
					delete_rowcol_cell(board, x, y, num);
					changes++;
				}
			}
		}
	}
	return (changes);
}

bool	logic_solve(t_grid* grid, int*** board)
{
	int changes = 1;
	int check;

	global_grid = grid;
	while (changes > 0)
	{
		changes = 0;
		check = place_single_cell(board);
		if (check == DEAD_END)
			return (false);
		changes += check;
		check = place_single_row(board);
		if (check == DEAD_END)
			return (false);
		changes += check;
		check = place_single_col(board);
		if (check == DEAD_END)
			return (false);
		changes += check;
	}
	return (true);
}
