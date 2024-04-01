#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


int getbingo(char board[9], int lines[8][3]) {
  for (int i = 0; i < 8; i++) {
    int a = lines[i][0];
    int b = lines[i][1];
    int c = lines[i][2];

    if (
      board[a] != ' '
      && board[a] == board[b] 
      && board[b] == board[c]
    ) {
      return board[a];
    };
  }

  return 0;
}

int get_target(char board[9], int lines[8][3]) {
  for (int i = 0; i < 8; i++) {
    int a = lines[i][0];
    int b = lines[i][1];
    int c = lines[i][2];

    if (
      board[b] != ' '
      && board[b] == board[c]
      && board[a] == ' '
    ) {
      return a;
    } else if (
      board[a] != ' '
      && board[a] == board[c]
      && board[b] == ' '
    ) {
      return b;
    } else if (
      board[a] != ' '
      && board[a] == board[b]
      && board[c] == ' '
    ) {
      return c;
    }
  }

  return -1;
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
  int lines[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6},
  };

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
      int target = get_target(board, lines);
      int com_idx;

      if (target > -1) {
        board[target] = X;
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
    };

    // check bingo
    {
      int bingo = getbingo(board, lines);

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


