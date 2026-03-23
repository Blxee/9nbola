#include "draw.h"
#include "logic.h"
#include <ncurses.h>



t_draw *draw_create()
{
  t_draw *draw = malloc(sizeof(t_draw));

  if (!draw)
    return (NULL);
  initscr();
  start_color();
  init_pair(BOMB_COLOR, COLOR_RED, COLOR_BLACK);
  init_pair(LOCKED_COLOR, COLOR_BLACK, COLOR_WHITE);
  init_pair(FLAG_COLOR, COLOR_GREEN, COLOR_WHITE);
  init_pair(NUMBER_COLOR, COLOR_BLUE, COLOR_BLACK);
  init_pair(EMPTY_COLOR, COLOR_BLACK, COLOR_BLACK);
  return (draw);
}

static void draw_square(WINDOW *stdscr, t_square square)
{
  if (square.flag)
    addch('>' | COLOR_PAIR(FLAG_COLOR));
  else if (square.locked)
    addch('#' | COLOR_PAIR(LOCKED_COLOR));
  else if (square.is_bomb)
    addch('*' | COLOR_PAIR(BOMB_COLOR) | A_BOLD | A_BLINK);
  else if (square.bombs > 0)
    addch(('0' + square.bombs % 9) | COLOR_PAIR(NUMBER_COLOR) | A_BOLD);
  else
    addch(' ' | COLOR_PAIR(EMPTY_COLOR));
}

void draw_board(WINDOW *stdscr, t_board *board)
{
  int max_x, max_y;
  int x, y;

  (void)board;
  getmaxyx(stdscr, max_y, max_x);

  move(max_y / 2 - ROWS / 2 - 1, max_x / 2 - COLS);
  addstr("+-----------------------+");
  y = 0;
  while (y < ROWS)
  {
    move(max_y / 2 - ROWS / 2 + y, max_x / 2 - COLS);
    addch('|');
    x = 0;
    while (x < COLS)
    {
      draw_square(stdscr, board->grid[y][x]);
      addch('|');
      x++;
    }
    addstr("\n");
    y++;
  }
  move(max_y / 2 - ROWS / 2 + 12, max_x / 2 - COLS);
  addstr("+-----------------------+");
  refresh();
}

void draw_destroy(t_draw **draw)
{
  endwin();
  free(*draw);
  *draw = NULL;
}
