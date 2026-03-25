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
      temp->grid[i][j].locked = true;
      temp->grid[i][j].flag = false;
      temp->grid[i][j].is_bomb = false;
      temp->grid[i][j].bombs = 0 ;
      j++;
    }
    i++;
  }
  srand(time(NULL));
  int user[11] = {0};
  int k = 0;
  i = 0;
  while(k < temp->bomb_amount){
    int x = rand() % COLS;
    int y = rand() % ROWS;
    if(user[x]==0&&user[y] == 0){
    user[x] = 1;
    user[y] = 1;
    }
    temp->grid[x][y].is_bomb = true;
    int x2 ,y2;
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
void reveal_entire_board(t_board *board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board->grid[i][j].locked = false;
        }
    }
}
void board_open_square(t_board *board, int x, int y)
{
  if(x < 0 || x >= ROWS || y < 0 || y >= COLS)
    return;

  if(board->grid[x][y].flag == true)
    return;

  if(board->grid[x][y].locked == false)
    return;

  board->grid[x][y].locked = false;
  
  if(board->grid[x][y].is_bomb == true){
    reveal_entire_board(board);
    return;
  }

  if(board->grid[x][y].bombs == 0) {
    int i = -1;
    while(i <= 1) {
      int j = -1;
      while(j <= 1) {
        int x2 = x + i;
        int y2 = y + j;
        board_open_square(board, x2, y2);
        j++;
      }
      i++;
    }
  }
}
void board_flag_square(t_board *board, int x, int y)
{
  if(x < 0||x >= ROWS||y < 0||y >= COLS)
    return;
  else if(board->grid[x][y].locked == false)
    return;
  else if(board->grid[x][y].flag == true){
    board->grid[x][y].flag = false;
  }
  else{
    board->grid[x][y].flag = true;
  }
}
