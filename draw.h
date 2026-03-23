#ifndef DRAW
# define DRAW

#include <ncurses.h>
#include "logic.h"

typedef struct s_draw
{
  WINDOW *stdscr;
} t_draw;

t_draw *draw_create();
void draw_board(WINDOW *stdscr, t_board *board);
void draw_destroy(t_draw **draw);

#endif
