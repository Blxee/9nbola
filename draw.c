#include "draw.h"
#include <ncurses.h>

void draw_board(WINDOW *stdscr, t_board *board)
{
  int max_x, max_y;
  int x, y;

  (void)board;
  getmaxyx(stdscr, max_y, max_x);

  y = 0;
  while (y < max_y)
  {
    x = 0;
    while (x < max_x)
    {
      addstr("+---------------+\n");
      addstr("+---------------+\n");
    }
  }
}
