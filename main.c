#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// Utility Functions

bool intArrayContainsElement(size_t size, int *arr, int element) {
  for(int i = 0; i < size; i++) {
    if (arr[i] == element) {
      return true;
    }
  }
  return false;
}

bool isEven(int number) {
  return !(number & 1);
}

int intLength(int number) {
  for(int i = 1;;i++) {
    if (number < 10) {
      return i;
    }
    number /= 10;
  }
}

int randomNumber() {
  srand((unsigned int) time(NULL));
  return rand();
}


// Game Functions

bool canMove (size_t size, int *gameboard) {
  for (int i = 0; i < size; i++) {
    if (i > 3 && gameboard[i - 4] == gameboard[i]) {
      return true;
    }
    if (i < 12 && gameboard[i + 4] == gameboard[i]) {
      return true;
    }
    if (((i + 1) % 4) != 1 && gameboard[i - 1] == gameboard[i]) {
      return true;
    }
    if (((i + 1) % 4) != 0 && gameboard[i + 1] == gameboard[i]) {
      return true;
    }
  }
  return false;
}

int checkWinLoss(size_t size, int *gameboard) {
  if (intArrayContainsElement(size, gameboard, 2048)) {
    return 1;
  }
  else if (!(intArrayContainsElement(size, gameboard, 0)) && !(canMove(size, gameboard))) {
    return 0;
  }
  else {
     return 2;
  }
}

void printBoard(size_t size, int *gameboard) {
  clear();
  for (int row = 0; row < 16; row += 4) {
    printw("+------+------+------+------+\n");
    for(int column = 0; column < 4; column++) {
      printw("|");
      printw("%*s", ((6 - intLength(gameboard[row + column]))/2), " ");
      if (gameboard[row + column] == 0) {
        printw(" ");
      }
      else {
        printw("%i", gameboard[row + column]);
      }
      if (isEven(intLength(gameboard[row + column]))) {
        printw("%*s", ((6 - intLength(gameboard[row + column]))/2), " "); 
      }
      else {
        printw("%*s", (((6 - intLength(gameboard[row + column]))/2) + 1), " ");
      }
    }
    printw("|\n");
  }
  printw("+------+------+------+------+\n");
  printw("\n\nControls: WASD / Esc or q\n");
  refresh();
  return;
}

int twoOrFour() {
  if(randomNumber() % 10 == 0) {
    return 4;
  }
  return 2;
}

void computerTurn(size_t size, int *gameboard) {
  for (int i = (randomNumber() % size); i < size; i++) {
    if (gameboard[i] == 0) {
      gameboard[i] = twoOrFour();
      return;
    }
  }
  if (isEven(randomNumber())) {
    for (int i = 0; i < size; i++) {
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
  return;
}

void playerTurn(size_t size, int *gameboard) {
  int userinput;
  for (;;) {
    userinput = getch();
    if (userinput == 119 /* w */) {
      for (int column = 0; column < 4; column++) {
        for (int row = 0; row < 16; row += 4) {
          if (gameboard[row + column] != 0) {
            for (int checkrow = row + 4; checkrow < 16; checkrow += 4) {
              if (gameboard[row + column] == gameboard[checkrow + column]) {
                gameboard[row + column] <<= 1;
                gameboard[checkrow + column] = 0;
                break;
              }
              else if (gameboard[checkrow + column] != 0) {
                break;
              }
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
    else if (userinput == 115 /* s */) {
      for (int column = 0; column < 4; column++) {
        for (int row = 15; row > -1; row -= 4) {
          if (gameboard[row - column] != 0) {
            for (int checkrow = row - 4; checkrow > -1; checkrow -= 4) {
              if (gameboard[row - column] == gameboard[checkrow - column]) {
                gameboard[row - column] <<= 1;
                gameboard[checkrow - column] = 0;
                break;
              }
              else if (gameboard[checkrow - column] != 0) {
                break;
              }
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
    else if (userinput == 97 /* a */) {
      for (int row = 0; row < 16; row += 4) {
        for (int column = 0; column < 4; column++) {
          if (gameboard[row + column] != 0) {
            for (int checkcolumn = column + 1; checkcolumn < 4; checkcolumn++) {
              if (gameboard[row + column] == gameboard[row + checkcolumn]) {
                gameboard[row + column] <<= 1;
                gameboard[row + checkcolumn] = 0;
                break;
              }
              else if (gameboard[row + checkcolumn] != 0) {
                break;
              }
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
    else if (userinput == 100 /* d */) {
      for (int row = 0; row < 16; row += 4) {
        for (int column = 3; column > -1; column--) {
          if (gameboard[row + column] != 0) {
            for (int checkcolumn = column - 1; checkcolumn > -1; checkcolumn--) {
              if (gameboard[row + column] == gameboard[row + checkcolumn]) {
                gameboard[row + column] <<= 1;
                gameboard[row + checkcolumn] = 0;
                break;
              }
              else if (gameboard[row + checkcolumn] != 0) {
                break;
              }
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
    else if (userinput == 27 /* Esc */ || userinput == 113 /* q */) {
      gameboard[0] = -1;
      return;
    }
  }
  return;
}

void gameloop() {
  int winloss;
  int gameboard[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  computerTurn(16, gameboard);
  computerTurn(16, gameboard);
  printBoard(16, gameboard);
  for(;;) {
    playerTurn(16, gameboard);
    if (intArrayContainsElement(16, gameboard, -1)) {
      break;
    }
    computerTurn(16, gameboard);
    printBoard(16, gameboard);
    winloss = checkWinLoss(16, gameboard);
    if (winloss == 1) {
      printw("\nYou Win!\n");
      break;
    }
    else if (winloss == 0) {
      printw("\nYou Lose!\n");
      break;
    }
  }
  printw("Press any key to continue");
  getch();
  return;
}

void menu() {
  for (;;) {
    clear();
    printw("Welcome to\n");
    printw(" ___ ___ ___ ___ \n|_  |   | | | . |\n|  _| | |_  | . |\n|___|___| |_|___|\n");
    printw("Press and key to start or q/Esc to quit!");
    refresh();
    int userinput = getch();
    if (userinput == 27 /* Esc */ || userinput == 113 /* q */) {
      return;
    } 
    gameloop();
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
