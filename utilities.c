#include "sudoku.h"

void	some_error(t_grid* grid)
{
	puts("Some error occured");
	free_everything(grid);
	exit(EXIT_FAILURE);
}

static void	print_bot_clues(t_grid* grid)
{
	printf("x | ");
	for (int i = 0; i < size; i++)
		printf("%d ", grid->sky_down[i]);
	printf("| x\n");
}

static void	print_top_clues(t_grid* grid)
{
	printf("x | ");
	for (int i = 0; i < size; i++)
		printf("%d ", grid->sky_up[i]);
	printf("| x\n");
}

void	print_board(t_grid* grid, int*** board)
{
	int x = 0; int y = 0;

	puts("\n");
	print_top_clues(grid);
	printf("--------------------------");
	printf("\n%d | ", grid->sky_left[x]);
	while (x < size)
	{
		while (y < size)
		{
			printf("%d ", board[x][y][0]);
			y++;
			if (y == size && x < size - 1)
			{
				printf("| %d\n%d | ", grid->sky_right[x], grid->sky_left[x + 1]);
			}
		}
		x++;
		y = 0;
	}
	printf("| %d", grid->sky_right[x - 1]);
	printf("\n--------------------------\n");
	print_bot_clues(grid);
	puts("\n");
}

void	print_everything(int*** board)
{
	printf("\n");
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			for (int z = 0; z < size + 1; z++)
				printf("%d", board[x][y][z]);
			printf(" | ");
		}
		printf("\n");
	}
	printf("\n");
}

void	update_progress(t_grid* grid, int*** board)
{
	grid->iter_count++;
	grid->iter = 0;
	printf("Iterations: %.2f million\n", (float) (grid->iter_count * ITER_COUNT + grid->iter) / 1000000);
	print_board(grid, board);
	print_everything(board);
}

void	print_single_line(int* line)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d", line[i]);
	}
	printf("\n\n");
}