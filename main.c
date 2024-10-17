#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define USER 1
#define COM 2

int lot();
int rowCrossed(char board[3][3]);
int columnCrossed(char board[3][3]);
int diagonalCrossed(char board[3][3]);
int isCrossed(char board[3][3]);
void drawBoard(char board[3][3]);

int main() {
  srand(time(NULL));

  // variables
  int whoseTurn;
  int gameCount = 0;
  char board[3][3];
  // initilaize board variables
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      board[r][c] = ' ';
    }
  }

  // lot 
  whoseTurn = lot();
  printf("%s First\n", whoseTurn == USER ? "You" : "Com");

  // playing
  while (!isCrossed(board) && gameCount < 9) {
    if (whoseTurn == USER) {
      drawBoard(board);

      int input;
      printf("▶︎ Choose a number from 1 to 9: ");
      scanf("%d", &input);

      int r = (input - 1) / 3;
      int c = (input - 1) % 3;

      if (board[r][c] == ' ') {
        board[r][c] = 'O';
      } else {
        printf("▶︎ Occupied. try again\n");
        continue;
      }

      whoseTurn = COM;
      gameCount++;

    } else {
      int com_idx = rand() % 9;
      int r = com_idx / 3;
      int c = com_idx % 3;

      if (board[r][c] != ' ') {
        continue;
      } 

      board[r][c] = 'X';
      whoseTurn = USER;
      gameCount++;
    }
  }

  // get result
  drawBoard(board);

  if (!isCrossed(board)) {
    printf("▶︎ DRAW\n");
  } else {
    if (whoseTurn == COM) {
      printf("▶︎ YOU WIN!\n");
    } else if (whoseTurn == USER) {
      printf("▶︎ YOU LOSE\n");
    } 
  }
}

int lot() {
  return (rand() % 2) + 1;
}

int rowCrossed(char board[3][3]) {
  for (int r = 0; r < 3; r++) {
    if (board[r][0] != ' ' && board[r][0] == board[r][1] && board[r][1] == board[r][2]) {
      return 1;
    }
  }

  return 0;
}

int columnCrossed(char board[3][3]) {
  for (int c = 0; c < 3; c++) {
    if (board[0][c] != ' ' && board[0][c] == board[1][c] && board[1][c] == board[2][c]) {
      return 1;
    }
  }

  return 0;
}

int diagonalCrossed(char board[3][3]) {
  // cross bingo (\)
  if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return 1;
  }

  // cross bingo (/)
  if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return 1;
  }

  return 0;
}

int isCrossed(char board[3][3]) {
  if (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board)) {
    return 1;
  }

  return 0;
}

void drawBoard(char board[3][3]) {
  printf("-----\n");

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      printf("%c ", board[r][c]);
    }

    printf("\n");
  }

  printf("-----\n");
};
