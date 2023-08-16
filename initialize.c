#include "sudoku.h"

static void	paste_input(int* clue, char** argv, int i)
{
	if (strlen(argv[i + 1]) != 1 || (!isdigit(*argv[i + 1])))
	{
		puts("Invalid input");
		exit(EXIT_FAILURE);
	}
	clue[i % SIZE] = atoi(argv[i + 1]);
}

void	free_board(int*** board)
{
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
			free(board[x][y]);
		free(board[x]);
	}
	free(board);
	board = NULL;
}

int***	malloc_board(void)
{
	int*** board;

	board = malloc(SIZE * sizeof(int**));
	for (int x = 0; x < SIZE; x++)
	{
		board[x] = malloc(SIZE * sizeof(int*));
		if (!board[x])
			some_error();
		for (int y = 0; y < SIZE; y++)
		{
			board[x][y] = malloc((SIZE + 1) * sizeof(int));
			if (!board[x][y])
				some_error();
			for (int z = 0; z < SIZE + 1; z++)
				board[x][y][z] = z;
		}
	}
	return (board);
}

void	parse_input(t_grid* grid, char** argv)
{
	int i = 0;

	grid->sky_up = malloc(SIZE * sizeof(int));
	grid->sky_down = malloc(SIZE * sizeof(int));
	grid->sky_left = malloc(SIZE * sizeof(int));
	grid->sky_right = malloc(SIZE * sizeof(int));
	grid->row = malloc(SIZE * sizeof(int));
	grid->rev_row = malloc(SIZE * sizeof(int));
	grid->col = malloc(SIZE * sizeof(int));
	grid->rev_col = malloc(SIZE * sizeof(int));
	grid->board = malloc_board();
	if (!grid->sky_up || !grid->sky_down || !grid->sky_left || !grid->sky_right \
		|| !grid->row || !grid->col || !grid->rev_row || !grid->rev_col || !grid->board)
		some_error();

	/* Insert user input into clues */

	for (int x = 0; x < SIZE; x++)
		paste_input(grid->sky_up, argv, i + x, SIZE);
	i += SIZE;
	for (int x = 0; x < SIZE; x++)
		paste_input(grid->sky_down, argv, i + x, SIZE);
	i += SIZE;
	for (int x = 0; x < SIZE; x++)
		paste_input(grid->sky_left, argv, i + x, SIZE);
	i += SIZE;	
	for (int x = 0; x < SIZE; x++)
		paste_input(grid->sky_right, argv, i + x, SIZE);
	i += SIZE;

	/* Basic check whether input is valid */

	for (int i = 0; i < SIZE; i++)
	{
		if (grid->sky_left[i] + grid->sky_right[i] > SIZE + 1)
		{
			printf("Can't solve with these clues\n");
			exit(EXIT_FAILURE);
		}
		if (grid->sky_up[i] + grid->sky_down[i] > SIZE + 1)
		{
			printf("Can't solve with these clues\n");
			exit(EXIT_FAILURE);
		}
	}
	grid->iter = 0;
	grid->iter_count = 0;
	remove_options(grid, grid->board);
}