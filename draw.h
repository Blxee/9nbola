#ifndef DRAW
# define DRAW

#include <ncurses.h>
#include "logic.h"

#define BOMB_COLOR (1)
#define LOCKED_COLOR (2)
#define FLAG_COLOR (3)
#define NUMBER_COLOR (4)
#define EMPTY_COLOR (5)
#define WALL_COLOR (6)

typedef struct s_draw
{
  WINDOW *stdscr;
} t_draw;

t_draw *draw_create();
void draw_board(WINDOW *stdscr, t_board *board);
void draw_destroy(t_draw **draw);

#endif
