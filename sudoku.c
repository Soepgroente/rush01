#include "sudoku.h"

int size;

void	copy_board(int*** src_board, int*** dest_board)
{
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			for (int z = 0; z <= size; z++)
				dest_board[x][y][z] = src_board[x][y][z];
}

static bool	solve_puzzle(t_grid* grid)
{
	static int b = 0;

	grid->iter++;
	copy_board(grid->board[b], grid->board[b + 1]);
	b++;
	if (grid->iter == ITER_COUNT)
		update_progress(grid, grid->board[b]);
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (grid->board[b][x][y][0] == 0)
			{
				for (int try = size; try > 0; try--)
				{
					if (grid->board[b][x][y][try] != 0 && check_if_possible(grid, grid->board[b], x, y, try) == true)
					{
						grid->board[b][x][y][0] = try;
						if (logic_solve(grid->board[b]) == false)
							copy_board(grid->board[b - 1], grid->board[b]);
						else if (solve_puzzle(grid) == true)
							return (true);
						copy_board(grid->board[b - 1], grid->board[b]);
					}
				}
				b--;
				return (false);
			}
		}
	}
	grid->main_board = grid->board[b];
	return (true);
}

int	main(int argc, char **argv)
{
	t_grid	grid;
	clock_t start_time; clock_t end_time;

	printf("Argc: %d\n", argc);
	if (argc > 37)
		return (puts("The universe implodes if I try to calculate bigger than 9x9"), 1);
	if ((argc - 1) % 4 != 0)
		return (puts("Amount of clues indivisible by 4"), 1);
	size = ((argc - 1) / 4);
	start_time = clock();
	parse_input(&grid, argv);
	printf("Initial board:");
	print_board(&grid, grid.board[0]);
	if (solve_puzzle(&grid) == true)
	{
		printf("\nSolved!\nFinal board:\n\n");
		print_board(&grid, grid.main_board);
	}
	else
		printf("Couldn't solve :-(\n");
	end_time = clock();
	// free_everything(&grid);
	printf("Running time (seconds): %.2f\n", (float)(end_time - start_time) / CLOCKS_PER_SEC);
	printf("Iterations: %lu\n", (size_t) grid.iter_count * ITER_COUNT + grid.iter);
	// system("leaks -q sudoku_solver");
	return (0);
}