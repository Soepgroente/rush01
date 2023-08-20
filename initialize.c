#include "sudoku.h"

static void	paste_input(int* clue, char** argv, int i)
{
	if (strlen(argv[i + 1]) != 1 || (!isdigit(*argv[i + 1])))
	{
		puts("Invalid input");
		exit(EXIT_FAILURE);
	}
	clue[i % size] = atoi(argv[i + 1]);
}

void	free_everything(t_grid* grid)
{
	free(grid->col);
	free(grid->rev_col);
	free(grid->row);
	free(grid->rev_row);
	free(grid->sky_down);
	free(grid->sky_up);
	free(grid->sky_left);
	free(grid->sky_right);
	for (int i = 0; i < size * size; i++)
		free_board(grid->board[i]);
	free(grid->board);
}

void	free_board(int*** board)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
			free(board[x][y]);
		free(board[x]);
	}
	free(board);
}

int***	malloc_board(t_grid* grid)
{
	int*** board;

	board = malloc(size * sizeof(int**));
	if (!board)
		some_error(grid);
	for (int x = 0; x < size; x++)
	{
		board[x] = malloc(size * sizeof(int*));
		if (!board[x])
			some_error(grid);
		for (int y = 0; y < size; y++)
		{
			board[x][y] = malloc((size + 1) * sizeof(int));
			if (!board[x][y])
				some_error(grid);
			for (int z = 0; z < size + 1; z++)
				board[x][y][z] = z;
		}
	}
	return (board);
}

static void	malloc_the_things(t_grid* grid)
{
	grid->sky_up = malloc(size * sizeof(int));
	grid->sky_down = malloc(size * sizeof(int));
	grid->sky_left = malloc(size * sizeof(int));
	grid->sky_right = malloc(size * sizeof(int));
	grid->row = malloc(size * sizeof(int));
	grid->rev_row = malloc(size * sizeof(int));
	grid->col = malloc(size * sizeof(int));
	grid->rev_col = malloc(size * sizeof(int));
	if (!grid->sky_up || !grid->sky_down || !grid->sky_left || !grid->sky_right \
		|| !grid->row || !grid->col || !grid->rev_row || !grid->rev_col || !grid->board)
		some_error(grid);
	grid->board = malloc(size * size * sizeof(int***));
	if (!grid->board)
		some_error(grid);
	for (int x = 0; x < size * size + 1; x++)
		grid->board[x] = malloc_board(grid);
}

void	parse_input(t_grid* grid, char** argv)
{
	int i = 0;

	malloc_the_things(grid);
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_up, argv, i + x);
	i += size;
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_down, argv, i + x);
	i += size;
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_left, argv, i + x);
	i += size;	
	for (int x = 0; x < size; x++)
		paste_input(grid->sky_right, argv, i + x);
	grid->iter = 0;
	grid->iter_count = 0;
	remove_options(grid, grid->board[0]);
}