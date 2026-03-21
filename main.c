#include <stdio.h>
#include <ncurses.h>
#include "draw.h"
#include "logic.h"


int main(void)
{
  t_board *board = board_create();
  WINDOW *stdscr = initscr();

  draw_board(stdscr, board);
  refresh();
  getch();
  endwin();
}
