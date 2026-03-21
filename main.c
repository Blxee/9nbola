#include <stdio.h>
#include <ncurses.h>
#include "draw.h"
#include "logic.h"


int main(void)
{
  t_board *board = board_create(12);
  t_draw *draw = draw_create();

  draw_board(stdscr, board);
  getch();
  draw_destroy(&draw);
}
