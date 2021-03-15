#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// Utility Functions

bool intArrayContainsElement(size_t size, int *arr, int element) {
  for(int i = 0; i < size; i++) if (arr[i] == element) return true; 
  return false;
}

bool isEven(int number) {
  return !(number & 1);
}

int intLength(int number) {
  for(int i = 1;;i++) {
    if (number < 10) return i;
    number /= 10;
  }
}

int randomNumber() {
  srand((unsigned int) time(NULL));
  return rand();
}


// Game Functions

bool canMove (int *gameboard) {
  for (int i = 0; i < 16; i++) {
    if (i > 3 && gameboard[i - 4] == gameboard[i]) return true;
    if (i < 12 && gameboard[i + 4] == gameboard[i]) return true;
    if (((i + 1) % 4) != 1 && gameboard[i - 1] == gameboard[i]) return true;
    if (((i + 1) % 4) != 0 && gameboard[i + 1] == gameboard[i]) return true;
  }
  return false;
}

int checkWinLoss(int *gameboard) {
  if (intArrayContainsElement(16, gameboard, 2048)) return 1;
  if (!(intArrayContainsElement(16, gameboard, 0)) && !(canMove(gameboard))) return 0;
  return 2;
}

void printBoard(int *gameboard) {
  clear();
  for (int row = 0; row < 16; row += 4) {
    printw("+------+------+------+------+\n");
    for(int column = 0; column < 4; column++) {
      printw("|");
      printw("%*s", ((6 - intLength(gameboard[row + column]))/2), " ");
      if (gameboard[row + column] == 0) printw(" ");
      else printw("%i", gameboard[row + column]);
      if (isEven(intLength(gameboard[row + column]))) printw("%*s", ((6 - intLength(gameboard[row + column]))/2), " "); 
      else printw("%*s", (((6 - intLength(gameboard[row + column]))/2) + 1), " ");
    }
    printw("|\n");
  }
  printw("+------+------+------+------+\n");
  printw("\n\nControls: WASD / Esc or q\n");
  refresh();
  return;
}

int twoOrFour() {
  if(randomNumber() % 10 == 0) return 4;
  return 2;
}

void computerTurn(int *gameboard) {
  for (int i = (randomNumber() % 16); i < 16; i++) {
    if (gameboard[i] == 0) {
      gameboard[i] = twoOrFour();
      return;
    }
  }
  if (isEven(randomNumber())) {
    for (int i = 0; i < 16; i++) {
       if (gameboard[i] == 0) {
         gameboard[i] = twoOrFour();
         return;
       }
    }
  }
  else {
    for (int i = 15; i > -1; i--) {
       if (gameboard[i] == 0) {
         gameboard[i] = twoOrFour();
         return;
       }
    }
  }
}

void moveTilesUp(int *gameboard) {
  for (int column = 0; column < 4; column++) {
    for (int row = 0; row < 16; row += 4) {
      if (gameboard[row + column] != 0) {
        for (int checkrow = row + 4; checkrow < 16; checkrow += 4) {
          if (gameboard[row + column] == gameboard[checkrow + column]) {
            gameboard[row + column] <<= 1;
            gameboard[checkrow + column] = 0;
            break;
          }
          else if (gameboard[checkrow + column] != 0) break;
        }
      }
      else {
        for (int checkrow = row + 4; checkrow < 16; checkrow += 4) {
          if (gameboard[checkrow + column] != 0) {
            gameboard[row + column] = gameboard[checkrow + column];
            gameboard[checkrow + column] = 0;
            break;
          }
        }
      }
    }
  }
  return;
}

void moveTilesDown (int *gameboard) {
  for (int column = 0; column < 4; column++) {
    for (int row = 15; row > -1; row -= 4) {
      if (gameboard[row - column] != 0) {
        for (int checkrow = row - 4; checkrow > -1; checkrow -= 4) {
          if (gameboard[row - column] == gameboard[checkrow - column]) {
            gameboard[row - column] <<= 1;
            gameboard[checkrow - column] = 0;
            break;
          }
          else if (gameboard[checkrow - column] != 0) break;
        }
      }
      else {
        for (int checkrow = row - 4; checkrow > -1; checkrow -= 4) {
          if (gameboard[checkrow - column] != 0) {
            gameboard[row - column] = gameboard[checkrow - column];
            gameboard[checkrow - column] = 0;
            break;
          }
        }
      }
    }
  }
  return;
}

void moveTilesLeft(int *gameboard) {
  for (int row = 0; row < 16; row += 4) {
    for (int column = 0; column < 4; column++) {
      if (gameboard[row + column] != 0) {
        for (int checkcolumn = column + 1; checkcolumn < 4; checkcolumn++) {
          if (gameboard[row + column] == gameboard[row + checkcolumn]) {
            gameboard[row + column] <<= 1;
            gameboard[row + checkcolumn] = 0;
            break;
          }
          else if (gameboard[row + checkcolumn] != 0) break;
        }
      }
      else {
        for (int checkcolumn = column + 1; checkcolumn < 4; checkcolumn++) {
          if (gameboard[row + checkcolumn] != 0) {
            gameboard[row + column] = gameboard[row + checkcolumn];
            gameboard[row + checkcolumn] = 0;
            break;
          }
        }
      }
    }
  }
  return;
}

void moveTilesRight(int *gameboard) {
  for (int row = 0; row < 16; row += 4) {
    for (int column = 3; column > -1; column--) {
      if (gameboard[row + column] != 0) {
        for (int checkcolumn = column - 1; checkcolumn > -1; checkcolumn--) {
          if (gameboard[row + column] == gameboard[row + checkcolumn]) {
            gameboard[row + column] <<= 1;
            gameboard[row + checkcolumn] = 0;
            break;
          }
          else if (gameboard[row + checkcolumn] != 0) break;
        }
      }
      else {
        for (int checkcolumn = column - 1; checkcolumn > -1; checkcolumn--) {
          if (gameboard[row + checkcolumn] != 0) {
            gameboard[row + column] = gameboard[row + checkcolumn];
            gameboard[row + checkcolumn] = 0;
            break;
            }
          }
        }
    }
  }
  return;
}

void playerTurn(int *gameboard) {
  switch (getch()) {
    case 119 /* w */:
      moveTilesUp(gameboard);
      return;
    case 115 /* s */:
      moveTilesDown(gameboard);
      return;
    case 97 /* a */:
      moveTilesLeft(gameboard);
      return;
    case 100 /* d */:
      moveTilesRight(gameboard);
      return;
    case 27 /* Esc */: 
    case 113 /* q */:
      gameboard[0] = -1;
      return;
    default:
      playerTurn(gameboard);
  }
}

void gameloop() {
  int gameboard[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
  computerTurn(gameboard);
  computerTurn(gameboard);
  printBoard(gameboard);
  while(true) {
    playerTurn(gameboard);
    if (intArrayContainsElement(16, gameboard, -1)) return;
    computerTurn(gameboard);
    printBoard(gameboard);
    switch(checkWinLoss(gameboard)){
     case 1:
      printw("\nYou Win!\n");
      return;
     case 0:
      printw("\nYou Lose!\n");
      return;
    }
  }
}

void menu() {
  while(true) {
    clear();
    printw("Welcome to\n");
    printw(" ___ ___ ___ ___ \n|_  |   | | | . |\n|  _| | |_  | . |\n|___|___| |_|___|\n");
    printw("Press and key to start or q/Esc to quit!");
    refresh();
    switch(getch()) {
      case 27 /* Esc */:
      case 113 /* q */:
        return;
      default :
        gameloop();
        printw("Press any key to continue");
        refresh();
        getch();
        break;
    }
  }
  return;
}


// Main

int main() {
  initscr();
  noecho();
  menu();
  endwin();
  return 0;
}
