#include "logic.h"
t_board *board_create(int bomb_amount)
{
  int i;
  int j;
  t_board *temp = (t_board*)malloc(sizeof(t_board));

  if(!temp)
    return NULL;
  temp->bomb_amount = bomb_amount;
  i = 0;
  while(i < ROWS){
    j = 0;
    while(j < COLS){
      temp->grid[i][j].locked = false;
      temp->grid[i][j].flag = false;
      temp->grid[i][j].is_bomb = false;
      temp->grid[i][j].bombs = 0 ;
      j++;
    }
    i++;
  }
  srand(time(NULL));
  int k = 0;
  i = 0;
  while(k < temp->bomb_amount){
    int x = rand() % COLS;
    int y = rand() % ROWS;
    temp->grid[x][y].is_bomb = true;
    int x2, y2;
    i = -1;
    while(i <= 1){
      j = -1;
      while(j <= 1){
        x2 = x + i;
        y2 = y + j;
        j++;
        if(x2 == x&&y2 == y)
          continue;
        if(x2 < 0||x2 >= 12||y2 < 0||y2 >= 12)
          continue;
        temp->grid[x2][y2].bombs++;
      }
      i++;
    }
    k++;
  }
  return (temp);
}
void board_draw(t_board *board){
  int i;
  int j;
  i = 0;

  printf("+-----------------------+\n");
  while(i < ROWS){
    j = 0;
    printf("|");
    while(j < COLS){
      if(board->grid[i][j].locked)
        printf("#|");
      else if(board->grid[i][j].flag)
        printf(">|");
      else if(board->grid[i][j].is_bomb)
        printf("*|");
      else if(board->grid[i][j].bombs == 0)
        printf(" |");
      else
        printf("%d|",board->grid[i][j].bombs);
      j++;
    }
    printf("\n");
    i++;
  }
  printf("+-----------------------+\n");

}
