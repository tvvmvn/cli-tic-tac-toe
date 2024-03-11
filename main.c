#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void chktarget(char board[9], int* target, int a, int b, int c) {
  if (
    board[b] != ' '
    && board[b] == board[c]
    && board[a] == ' '
  ) {
    *target = a;
  } else if (
    board[a] != ' '
    && board[a] == board[c]
    && board[b] == ' '
  ) {
    *target = b;
  } else if (
    board[a] != ' '
    && board[a] == board[b]
    && board[c] == ' '
  ) {
    *target = c;
  }
}

void chkbingo(char board[9], int* bingo, int a, int b, int c) {
  if (
    board[a] != ' '
    && board[a] == board[b] 
    && board[b] == board[c]
  ) {
    *bingo = board[a];
  }
}

void drawboard(char board[9]) {
  printf("\n");
  printf(" %c | %c | %c \n", board[0], board[1], board[2]);
  printf("---+---+---\n");
  printf(" %c | %c | %c \n", board[3], board[4], board[5]);
  printf("---+---+---\n");
  printf(" %c | %c | %c \n", board[6], board[7], board[8]);
  printf("\n");
};

void game() {
  // constants
  enum Player { USER = 1, COM };
  enum Symbol { O = 'O', X = 'X' };

  // variables
  char board[9];

  for (int i = 0; i < 9; i++) {
    board[i] = ' ';
  }

  enum Player turn;
  int winner;
  int count = 0;

  // lot 
  turn = (rand() % 2) + 1;

  if (turn == USER) {
    printf("\nYou first\n");
  } else {
    printf("\nCom first\n");
  }

  // playing
  while (1) {
    // user
    if (turn == USER) {
      // user input
      int input;
      int idx;

      while (1) { 
        drawboard(board);
        printf("▶︎ Choose a number from 1 to 9: ");
        
        scanf("%d", &input);

        idx = input - 1;

        if (board[idx] != O && board[idx] != X) {
          board[idx] = O;
          count++;
          break;
        } else {
          printf("▶︎ Occupied. try again\n");
        }
      }
    } 
    
    // com
    if (turn == COM) {
      int target = -1;
      int com_idx;

      chktarget(board, &target, 0, 1, 2);
      chktarget(board, &target, 3, 4, 5);
      chktarget(board, &target, 6, 7, 8);
      chktarget(board, &target, 0, 3, 6);
      chktarget(board, &target, 1, 4, 7);
      chktarget(board, &target, 2, 5, 8);
      chktarget(board, &target, 0, 4, 8);
      chktarget(board, &target, 2, 4, 6);

      if (target > -1) {
        board[target] = X;
        target = -1;
      } else {
        while (1) { 
          com_idx = rand() % 9;

          if (board[com_idx] == ' ') {
            board[com_idx] = X;
            break;
          } 
        }
      }

      count++;
    }

    // check bingo
    {
      int bingo;

      chkbingo(board, &bingo, 0, 1, 2);
      chkbingo(board, &bingo, 3, 4, 5);
      chkbingo(board, &bingo, 6, 7, 8);
      chkbingo(board, &bingo, 0, 3, 6);
      chkbingo(board, &bingo, 1, 4, 7);
      chkbingo(board, &bingo, 2, 5, 8);
      chkbingo(board, &bingo, 0, 4, 8);
      chkbingo(board, &bingo, 2, 4, 6);

      if (bingo == O) {
        winner = USER;
        break;
      }
      
      if (bingo == X) { 
        winner = COM;
        break;
      } 

      if (count > 8) {
        break;
      }
    }

    // change turn
    turn = (turn == USER) ? COM : USER;
  }

  // end
  drawboard(board);

  if (winner == USER) {
    printf("▶︎ YOU WIN\n");
  } else if (winner == COM) {
    printf("▶︎ YOU LOSE\n");
  } else {
    printf("▶︎ DRAW!\n");
  }

  // continue
  char c;

  printf("▶︎ play again? y/n: ");
  scanf(" %c", &c);

  if (c == 'y') {
    game();
  } else if (c == 'n') {
    printf("▶︎ ok. bye\n");
  } else {
    printf("▶︎ wrong input. terminated\n");
  }
}

int main() {
  srand(time(NULL));
  
  // intro
  char start;

  printf("*** TIC TAC TOE ***\n");
  printf("Press any key to start game: ");
  scanf(" %c", &start);

  game();
}


