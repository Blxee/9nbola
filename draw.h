#ifndef DRAW
# define DRAW

#include <ncurses.h>
#include "logic.h"

#define BOMB_COLOR (1)
#define LOCKED_COLOR (2)
#define FLAG_COLOR (3)
#define EMPTY_COLOR (4)
#define WALL_COLOR (5)
#define NUMBER_COLOR (100)

typedef struct s_draw
{
  WINDOW *stdscr;
  int cursor_pos[2];
} t_draw;

typedef enum e_event {
  EVENT_MOVE_LEFT,
  EVENT_MOVE_RIGHT,
  EVENT_MOVE_UP,
  EVENT_MOVE_DOWN,
  EVENT_OPEN,
  EVENT_FLAG,
  EVENT_QUIT,
  EVENT_NONE,
} t_event;

t_draw *draw_create();
t_event draw_get_event(t_draw *draw);
void draw_board(t_draw *draw, t_board *board);
void draw_destroy(t_draw **draw);

#endif
