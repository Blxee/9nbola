#include <stdio.h>
#include <ncurses.h>
#include "draw.h"
#include "logic.h"


int main(void)
{
  t_board *board = board_create(12);
  t_draw *draw = draw_create();
  t_event event;
  

  while (1)
  {
    draw_board(draw, board);
    event = draw_get_event(draw);

    switch (event) {
      case EVENT_MOVE_LEFT:
        if (draw->cursor_pos[0] > 0)
          draw->cursor_pos[0]--;
        break;
      case EVENT_MOVE_RIGHT:
        if (draw->cursor_pos[0] < COLS - 1)
          draw->cursor_pos[0]++;
        break;
      case EVENT_MOVE_UP:
        if (draw->cursor_pos[1] > 0)
          draw->cursor_pos[1]--;
        break;
      case EVENT_MOVE_DOWN:
        if (draw->cursor_pos[1] < ROWS - 1)
          draw->cursor_pos[1]++;
        break;
      case EVENT_OPEN:
        board_open_square(board, draw->cursor_pos[1], draw->cursor_pos[0]);
        break;
      case EVENT_FLAG:
        board_flag_square(board, draw->cursor_pos[1], draw->cursor_pos[0]);
        break;
      case EVENT_QUIT:
        draw_destroy(&draw);
        return (0);
      case EVENT_NONE:
        break;
    }
  }
}
