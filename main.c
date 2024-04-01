#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int getbingo(char board[3][3]) {
  // horizontal bingo
  for (int r = 0; r < 3; r++) {
    if (
      board[r][0] != ' '
      && board[r][0] == board[r][1]
      && board[r][1] == board[r][2]
    ) {
      return board[r][0];
    }
  }

  // vertical bingo
  for (int c = 0; c < 3; c++) {
    if (
      board[0][c] != ' '
      && board[0][c] == board[1][c]
      && board[1][c] == board[2][c]
    ) {
      return board[0][c];
    }
  }

  // cross bingo (\)
  if (
    board[0][0] != ' '
    && board[0][0] == board[1][1]
    && board[1][1] == board[2][2]
  ) {
    return board[0][0];
  }

  // cross bingo (/)
  if (
    board[0][2] != ' '
    && board[0][2] == board[1][1]
    && board[1][1] == board[2][0]
  ) {
    return board[0][2];
  }

  return 0;
}

void drawboard(char board[3][3]) {
  printf("-----\n");

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      printf("%c ", board[r][c]);
    }

    printf("\n");
  }

  printf("-----\n");
};

void game() {
  srand(time(NULL));

  // constants
  enum Player { USER = 1, COM };
  // variables
  enum Player turn;
  int count = 0;
  int bingo = 0;
  char board[3][3];

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      board[r][c] = ' ';
    }
  }

  // lot 
  turn = (rand() % 2) + 1;
  printf("%s First\n", turn == USER ? "You" : "Com");

  // playing
  while (!bingo && count < 9) {
    if (turn == USER) {
      int input;

      while (1) { 
        drawboard(board);
        printf("▶︎ Choose a number from 1 to 9: ");
        
        scanf("%d", &input);

        int x = (input - 1) / 3;
        int y = (input - 1) % 3;

        if (board[x][y] == ' ') {
          board[x][y] = 'O';
          break;
        } else {
          printf("▶︎ Occupied. try again\n");
        }
      }
    } else {
      int com_idx = 0;
      
      while (1) { 
        com_idx = rand() % 9;

        int x = com_idx / 3;
        int y = com_idx % 3;

        if (board[x][y] == ' ') {
          board[x][y] = 'X';
          break;
        } 
      }
    }

    turn = (turn == USER) ? COM : USER;
    
    bingo = getbingo(board);
    count++;
  }

  // get result
  drawboard(board);

  if (bingo == 'O') {
    printf("▶︎ YOU WIN!\n");
  } else if (bingo == 'X') {
    printf("▶︎ YOU LOSE\n");
  } else {
    printf("▶︎ DRAW\n");
  }
}

int main() {
  game();
}




