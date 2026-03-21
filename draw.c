#include "draw.h"
#include "logic.h"
#include <ncurses.h>



t_draw *draw_create()
{
  t_draw *draw = malloc(sizeof(t_draw));

  if (!draw)
    return (NULL);
  initscr();
  return (draw);
}

void draw_board(WINDOW *stdscr, t_board *board)
{
  int max_x, max_y;
  int x, y;

  (void)board;
  getmaxyx(stdscr, max_y, max_x);

  y = 0;
  while (y < ROWS)
  {
    move(max_y / 2 - ROWS / 2 + y, max_x / 2 - COLS);
    x = 0;
    while (x < COLS)
    {
      addch('.');
      addch('|');
      x++;
    }
    addstr("\n");
    y++;
  }
  refresh();
}

void draw_destroy(t_draw **draw)
{
  endwin();
  free(*draw);
  *draw = NULL;
}
