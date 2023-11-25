#ifndef SUDOKU_H
#define SUDOKU_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
# include <string.h>
# include <time.h>

# define ITER_COUNT 100000

extern int size;

typedef enum	e_nums
{
	DEAD_END = -1,
	SUCCESS,
}	t_nums;

typedef struct s_grid
{
	int****	board;
	int***	main_board;
	int*	sky_up;
	int*	sky_down;
	int*	sky_left;
	int*	sky_right;
	int**	row;
	int**	col;
	int		iter;
	int		iter_count;
}	t_grid;

/* Parsing */

void	parse_input(t_grid* grid, char** argv);
int***	malloc_board(void);
void	free_board(int*** board);
void	free_everything(t_grid* grid);

/* Utilities */

void	print_board(t_grid* grid, int*** board);
void	print_everything(int*** board);
void	print_single_line(int** line);
void	some_error(char* msg);
void	update_progress(t_grid* grid, int*** board);

/* Solver functions */

bool	logic_solve(t_grid* grid, int*** board);
int		place_single_row(int*** board);
int		place_single_col(int*** board);
int		place_single_cell(int*** board);
void	remove_options(t_grid* grid, int*** board);
bool	check_if_possible(t_grid* grid, int*** board, int x, int y, int try);

/* Vision stuff */

int		count_vision(int** line, int clue);
int		count_rev_vision(int** line, int clue);
bool	double_vision(int** line, int clue1, int clue2);

void	delete_rowcol_cell(int*** board, int x, int y, int num);

/*	Vision checkers	*/

int		alone_in_cell(int* cell);
int		alone_in_column(int*** board, int col, int num);
int		alone_in_row(int** row, int num);
bool	in_column(int*** board, int col, int num);
bool	in_row(int** line, int num);

#endif