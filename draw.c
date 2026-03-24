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
  init_pair(EMPTY_COLOR, COLOR_WHITE, COLOR_BLACK);
  init_pair(WALL_COLOR, COLOR_YELLOW, COLOR_BLACK);

  init_pair(NUMBER_COLOR + 1, COLOR_CYAN, COLOR_BLACK);
  init_pair(NUMBER_COLOR + 2, COLOR_BLUE, COLOR_BLACK);
  init_pair(NUMBER_COLOR + 3, COLOR_GREEN, COLOR_BLACK);
  init_pair(NUMBER_COLOR + 4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(NUMBER_COLOR + 5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(NUMBER_COLOR + 6, COLOR_RED, COLOR_BLACK);
  init_pair(NUMBER_COLOR + 7, COLOR_RED, COLOR_BLACK);
  init_pair(NUMBER_COLOR + 8, COLOR_RED, COLOR_BLACK);
  return (draw);
}

static void draw_wall(WINDOW *stdscr)
{
  int i = 0;

  attron(COLOR_PAIR(WALL_COLOR));
  addch('+');
  while (i++ < COLS - 1)
    addstr("--");
  addstr("-+");
  attroff(COLOR_PAIR(WALL_COLOR));
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
    addch(('0' + square.bombs % 9) | COLOR_PAIR(NUMBER_COLOR + square.bombs % 9) | A_BOLD);
  else
    addch('.' | COLOR_PAIR(EMPTY_COLOR));
}

void draw_board(WINDOW *stdscr, t_board *board)
{
  int max_x, max_y;
  int x, y;

  (void)board;
  getmaxyx(stdscr, max_y, max_x);

  move(max_y / 2 - ROWS / 2 - 1, max_x / 2 - COLS);
  draw_wall(stdscr);
  y = 0;
  while (y < ROWS)
  {
    move(max_y / 2 - ROWS / 2 + y, max_x / 2 - COLS);
    addch('|' | COLOR_PAIR(WALL_COLOR));
    x = 0;
    while (x < COLS)
    {
      draw_square(stdscr, board->grid[y][x]);
      if (x < COLS - 1)
      {
        if (board->grid[y][x].locked || (x < COLS && board->grid[y][x + 1].locked))
          addch(' ' | COLOR_PAIR(LOCKED_COLOR));
        else
          addch(' ' | COLOR_PAIR(EMPTY_COLOR));
      }
      x++;
    }
    addch('|' | COLOR_PAIR(WALL_COLOR));
    addch('\n');
    y++;
  }
  move(max_y / 2 - ROWS / 2 + 12, max_x / 2 - COLS);
  draw_wall(stdscr);
  refresh();
}

void draw_destroy(t_draw **draw)
{
  endwin();
  free(*draw);
  *draw = NULL;
}
