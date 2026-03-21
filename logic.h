#ifndef LOGIC_H
# define LOGIC_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 12
#define COLS 12

typedef struct s_square
{
  bool locked; // msdod
  bool flag; // raya
  bool is_bomb; // wach 9nbola
  int  bombs; // how much 9nable?
} t_square;

typedef struct s_board
{
  t_square grid[12][12];
  int bomb_amount; // l3adad dial 9nabl
} t_board;

t_board *board_create(int bomb_amount);
void     board_draw(t_board *board);
void     board_open_square(t_board *board, int x, int y);
void     board_flag_square(t_board *board, int x, int y);
void     board_destroy(t_board *board);

#endif
