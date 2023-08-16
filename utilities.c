#include "sudoku.h"

void	some_error(void)
{
	puts("Some error occured");
	exit(EXIT_FAILURE);
}

static void	print_bot_clues(t_grid* grid)
{
	printf("x | ");
	for (int i = 0; i < grid->n; i++)
		printf("%d ", grid->sky_down[i]);
	printf("| x\n");
}

static void	print_top_clues(t_grid* grid)
{
	printf("x | ");
	for (int i = 0; i < grid->n; i++)
		printf("%d ", grid->sky_up[i]);
	printf("| x\n");
}

void	print_board(t_grid* grid, int*** board)
{
	int x = 0; int y = 0; int n = grid->n;

	puts("\n");
	print_top_clues(grid);
	printf("--------------------------");
	printf("\n%d | ", grid->sky_left[x]);
	while (x < n)
	{
		while (y < n)
		{
			printf("%d ", board[x][y][0]);
			y++;
			if (y == n && x < n - 1)
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

void	print_everything(t_grid* grid, int*** board)
{
	printf("\n");
	for (int x = 0; x < grid->n; x++)
	{
		for (int y = 0; y < grid->n; y++)
		{
			for (int z = 0; z < grid->n + 1; z++)
				printf("%d", board[x][y][z]);
			printf(" | ");
		}
		printf("\n");
	}
	puts("");
}

void	update_progress(t_grid* grid, int*** board)
{
	grid->iter_count++;
	grid->iter = 0;
	printf("Iterations: %.2f billion\n", (float) (grid->iter_count * ITER_COUNT + grid->iter) / 1000000000);
	print_board(grid, board);
}

void	print_single_line(int* line, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d", line[i]);
	}
	printf("\n\n");
}