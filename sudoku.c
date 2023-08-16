#include "sudoku.h"

static int***	copy_board(t_grid* grid, int*** board)
{
	int***	new_board;

	new_board = malloc_board(SIZE);
	for (int x = 0; x < SIZE; x++)
		for (int y = 0; y < SIZE; y++)
			for (int z = 0; z <= SIZE; z++)
				new_board[x][y][z] = board[x][y][z];
	return (new_board);
}

static bool	solve_puzzle(t_grid* grid, int*** board)
{
	int x = 0;
	int y;
	int***	new_board;

	if (!board)
		board = grid->board;
	new_board = copy_board(grid, board);
	if (grid->iter == ITER_COUNT)
		update_progress(grid, new_board);
	grid->iter++;
	while (x < SIZE)
	{
		y = 0;
		while (y < SIZE)
		{
			if (new_board[x][y][0] == 0)
			{
				for (int try = SIZE; try >= 1; try--)
				{
					if (new_board[x][y][try] != 0 && check_if_possible(grid, x, y, try) == true)
					{
						new_board[x][y][0] = try;
						logic_solve(grid, new_board);
						// print_board(grid, new_board);
						if (solve_puzzle(grid, new_board) == true)
						{
							free_board(new_board);
							return (true);
						}
					}
				}
				free_board(new_board);
				return (false);
			}
			y++;
		}
		x++;
	}
	grid->final_board = copy_board(grid, new_board);
	free_board(new_board);
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
	
	#define SIZE ((argc - 1) / 4)

	parse_input(&grid, argv);
	printf("Initial board:");
	print_board(&grid, grid.board);
	start_time = clock();
	logic_solve(&grid, grid.board);
	printf("After pre-solving:");
	print_everything(&grid, grid.board);
	print_board(&grid, grid.board);
	if (solve_puzzle(&grid, NULL) == true)
	{
		printf("\nSolved!\nFinal board:\n\n");
		print_board(&grid, grid.final_board);
	}
	else
	{
		printf("Couldn't solve :-(\n");
		print_board(&grid, grid.board);
	}
	end_time = clock();
	printf("Running time (seconds): %.2f\n", (float)(end_time - start_time) / CLOCKS_PER_SEC);
	printf("Iterations: %lu\n", (size_t) grid.iter_count * ITER_COUNT + grid.iter);
}