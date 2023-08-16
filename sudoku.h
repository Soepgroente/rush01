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

# define ITER_COUNT 10000000

typedef struct s_grid
{
	int***	board;
	int***	final_board;
	int*	sky_up;
	int*	sky_down;
	int*	sky_left;
	int*	sky_right;
	int*	row;
	int*	rev_row;
	int*	col;
	int*	rev_col;
	int		iter;
	int		iter_count;
}	t_grid;

/* Parsing */

void	parse_input(t_grid* grid, char** argv);
int***	malloc_board(int n);
void	free_board(int*** board, int n);

/* Utilities */

void	clean_up(int*** board);
void	print_board(t_grid* grid, int*** board);
void	print_everything(t_grid* grid, int*** board);
void	print_single_line(int* line, int n);
void	some_error(void);
void	update_progress(t_grid* grid, int*** board);

/* Solver functions */

void	logic_solve(t_grid* grid, int*** board);
void	place_single_row(int*** board);
void	place_single_col(int*** board);
void	place_single_cell(int*** board);
void	remove_options(t_grid* grid, int*** board);
bool	check_if_possible(t_grid* grid, int x, int y, int try);

#endif