#include "logic.h"
t_board *board_create(int bomb_amount)
{
  int i;
  int j;
  t_board *temp = (t_board*)malloc(sizeof(t_board));

  if(!temp)
    return NULL;
  i = 0;
  while(i < ROWS){
  j = 0;
    while(j < COLS){
      temp->grid[i][j].locked = true;
      temp->grid[i][j].flag = true;
      temp->grid[i][j].is_bomb = true;
      temp->grid[i][j].bombs = bomb_amount;
      j++;
    }
    i++;
  }
  return (temp);
}
