#include "sudoku.h"

int n;

static void	delete_rowcol(int*** board, int x, int y, int num)
{
	for (int i = 0; i < n; i++)
		board[x][i][num] = 0;
	for (int i = 0; i < n; i++)
		board[i][y][num] = 0;
}

/*	Remove all digits from the options that are already placed 
	somewhere in the row or column */

void	clean_up(int*** board)
{
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (board[x][y][0] != 0)
			{
				delete_rowcol(board, x, y, board[x][y][0]);
				for (int z = 1; z < n; z++)
					board[x][y][z] = 0;
			}
		}
	}
}

/*	Removes any digits that are too high for the skyscraper clue to remain valid	*/

void	remove_options(t_grid* grid, int*** board)
{
	int x = 0;
	int y = 0;

	while (x < n)
	{
		while (y < n)
		{
			if (board[x][y][0] == 0)
			{
				for (int z = n + 2 - grid->sky_left[x] + y; z <= n; z++)
					board[x][y][z] = 0;
				for (int z = n + 1 - grid->sky_right[x] + n - y; z <= n; z++)
					board[x][y][z] = 0;
				for (int z = n + 2 - grid->sky_up[y] + x; z <= n; z++)
					board[x][y][z] = 0;
				for (int z = n + 1 - grid->sky_down[y] + n - x; z <= n; z++)
					board[x][y][z] = 0;
			}
			y++;
		}
		y = 0;
		x++;
	}
}

/*	Find any digits that can only be placed in one place in a row	*/

void	place_single_row(int*** board)
{
	int try = 1;
	int x;
	int y;
	int check = -1;

	while (try <= n)
	{
		x = 0;
		while (x < n)
		{
			y = 0;
			while (y < n)
			{
				if (check == -1 && board[x][y][try] != 0)
					check = y;
				else if (board[x][y][try] != 0)
				{
					check = -1;
					break ;
				}
				y++;
			}
			if (check != -1)
			{
				board[x][check][0] = try;
				check = -1;
			}
			x++;
		}
		try++;
	}
}

/*	Find any digits that can only be placed in one place in a column	*/

void	place_single_col(int*** board)
{
	int try = 1;
	int x;
	int y;
	int check = 0;

	while (try <= n)
	{
		y = 0;
		while (y < n)
		{
			x = 0;
			while (x < n)
			{
				if (check == -1 && board[x][y][try] != 0)
					check = x;
				else if (board[x][y][try] != 0)
				{
					check = -1;
					break ;
				}
				x++;
			}
			if (check != -1)
			{
				board[check][y][0] = try;
				check = -1;
			}
			y++;
		}
		try++;
	}
}

/*	Find any cells that just have one option left	*/

void	place_single_cell(int*** board)
{
	int check = 0;

	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (board[x][y][0] == 0)
			{
				for (int z = 1; z <= n; z++)
				{
					if (check == 0 && board[x][y][z] != 0)
						check = z;
					else if (board[x][y][z] != 0)
					{
						check = 0;
						break ;
					}
				}
				if (check != 0)
				{
					board[x][y][0] = check;
					check = 0;
				}
			}
		}
	}
}

/* bool	check_if_solved(int*** board)
{

	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		if (check_if_possible(grid))
	}
} */

void	logic_solve(t_grid* grid, int*** board)
{
	n = grid->n;
	puts("Printing before logical stuff");
	print_everything(grid, board);
	print_board(grid, board);
	for (int i = 0; i < 10; i++)
	{
		clean_up(board);
		place_single_row(board);
		clean_up(board);
		place_single_col(board);
		clean_up(board);
		place_single_cell(board);
		clean_up(board);
	}
	puts("Printing after logical stuff");
	print_everything(grid, board);
	print_board(grid, board);
}
