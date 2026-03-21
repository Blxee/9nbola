#include <stdio.h>
#include "logic.h"


int main(void)
{
  t_board *board = board_create(12);
  printf("bombs: %d\n", board->grid[0][0].bombs);
  board_draw(board);
}
