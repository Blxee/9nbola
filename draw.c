#include "draw.h"
#include "logic.h"
#include <ncurses.h>



t_draw *draw_create()
{
  t_draw *draw = malloc(sizeof(t_draw));

  if (!draw)
    return (NULL);
  draw->stdscr = initscr();
  draw->cursor_pos[0] = COLS / 2;
  draw->cursor_pos[1] = ROWS / 2;
  start_color();
  keypad(draw->stdscr, true);
  init_pair(BOMB_COLOR, COLOR_RED, COLOR_BLACK);
  init_pair(LOCKED_COLOR, COLOR_BLACK, COLOR_WHITE);
  init_pair(FLAG_COLOR, COLOR_GREEN, COLOR_WHITE);
  init_pair(EMPTY_COLOR, COLOR_WHITE, COLOR_BLACK);
  init_pair(WALL_COLOR, COLOR_YELLOW, COLOR_BLACK);
  init_pair(BANNER_COLOR, COLOR_MAGENTA, COLOR_BLACK);

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
    addstr("==");
  addstr("=+");
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
    addch('.' | COLOR_PAIR(EMPTY_COLOR) | A_DIM);
}

t_event draw_get_event(t_draw *draw)
{
  WINDOW *stdscr;
  int input;

  stdscr = draw->stdscr;
  input = getch();

  switch (input)
  {
    case 'a':
    case 'h':
    case KEY_LEFT:
      return EVENT_MOVE_LEFT;
    case 'd':
    case 'l':
    case KEY_RIGHT:
      return EVENT_MOVE_RIGHT;
    case 'w':
    case 'k':
    case KEY_UP:
      return EVENT_MOVE_UP;
    case 's':
    case 'j':
    case KEY_DOWN:
      return EVENT_MOVE_DOWN;
    case '\n':
      return EVENT_FLAG;
    case ' ':
      return EVENT_OPEN;
    case 27:
    case 'q':
      return EVENT_QUIT;
    default:
      return EVENT_NONE;
  }
}

static void draw_banner(t_draw *draw, int max_x)
{
  WINDOW *stdscr;
  
  stdscr = draw->stdscr;
  attron(COLOR_PAIR(BANNER_COLOR) | A_BOLD);
  move(1, max_x / 2 - 16);
  addstr("  ___        _           _       ");
  move(2, max_x / 2 - 16);
  addstr(" / _ \\ _ __ | |__   ___ | | __ _ ");
  move(3, max_x / 2 - 16);
  addstr("| (_) | '_ \\| '_ \\ / _ \\| |/ _` |");
  move(4, max_x / 2 - 16);
  addstr(" \\__, | | | | |_) | (_) | | (_| |");
  move(5, max_x / 2 - 16);
  addstr("   /_/|_| |_|_.__/ \\___/|_|\\__,_|");
  attroff(COLOR_PAIR(BANNER_COLOR) | A_BOLD);
}

void draw_board(t_draw *draw, t_board *board)
{
  WINDOW *stdscr;
  int max_x, max_y;
  int x, y;
  int offset[2];

  stdscr = draw->stdscr;
  getmaxyx(stdscr, max_y, max_x);
  offset[0] = max_x / 2 - COLS;
  offset[1] = max_y / 2 - ROWS / 2 + 2;
  clear();
  draw_banner(draw, max_x);
  move(offset[1] - 1, offset[0]);
  draw_wall(stdscr);
  y = 0;
  while (y < ROWS)
  {
    move(offset[1] + y, offset[0]);
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
  move(offset[1] + 12, offset[0]);
  draw_wall(stdscr);
  move(offset[1] + draw->cursor_pos[1], offset[0] + draw->cursor_pos[0] * 2 + 1);
  refresh();
}

void draw_destroy(t_draw **draw)
{
  endwin();
  free(*draw);
  *draw = NULL;
}
