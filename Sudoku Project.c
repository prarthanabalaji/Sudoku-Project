#include <stdio.h>

// setting up one example of a sudoku game
int puzzle[9][9] = {
  {0,0,0,0,1,0,0,3,0},
  {0,0,9,0,0,5,0,0,8},
  {8,0,4,0,0,6,0,2,5},
  {0,0,0,0,0,0,6,0,0},
  {0,0,8,0,0,4,0,0,0},
  {1,2,0,0,8,7,0,0,0},
  {3,0,0,9,0,0,2,0,0},
  {0,6,5,0,0,8,0,0,0},
  {9,0,0,0,0,0,0,0,0},
};

// setting up function declarations 
void print_puzzle(int puzzle[9][9]);
int valid_guess(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);

// includes messages, calls functions, and prints results
int main() {

  printf("\n\tWelcome to Solve Your Sudoku!");
  printf("\n\nOriginal Puzzle:");
  print_puzzle(puzzle);
  if (solve_puzzle(puzzle, 0, 0)) {
    printf("\n The puzzle is solved: ");
    print_puzzle(puzzle);
  } else {
    printf("\n This puzzle is not solvable. Try a new puzzle!\n");
  }
  return 0;
  
}

// implementing solving puzzle function using backtracking algorithm
int solve_puzzle(int puzzle[9][9], int row, int col) {

  if (col == 9) {
    if (row == 8) {
      return 1; // gone through entire board, puzzle has been solved
    }

    // on last column but not last row so goes to new row and resets the column
    row++;
    col = 0;
  }

  // checks if some cells are already filled. 
  // if so, skips them and moves to next col
  if (puzzle[row][col] > 0) {
    return solve_puzzle(puzzle, row, col + 1);
  }

  // backtracking alogorithm for solving puzzle
  for (int i = 1; i <= 9; i++) {
    if (valid_guess(puzzle, row, col, i)) {
      puzzle[row][col] = i; // temporarily puts the number in the grid

      // attempts to solve entire puzzle with the previous guess placed
      if (solve_puzzle(puzzle, row, col + 1)) {
        return 1;
      }

      // resets the temporarily filled cell with 0 if answer was not correct.
      puzzle[row][col] = 0;
    }
  }
  return 0;
}

int valid_move(int puzzle[9][9], int row, int col, int val) {

  // checking every column for a given row. invalid returns 0
  for (int i = 0; i < 9; i++) {
    if (puzzle[row][i] == val) {
      return 0;
    }
  }

  // checking every row for a given column
  for (int i = 0; i < 9; i++) {
    if (puzzle[i][col] == val) {
      return 0;
    }
  }

  // checking if the val selected can be placed in the square
  int r = row - row % 3; 
  int c = col - col % 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (puzzle[r+i][c+j] == val) // checking for duplicates
      {
        return 0;
      }
    }
  }

  return 1;
}

// formatting for printing the puzzle in a 9x9 grid
void print_puzzle(int puzzle[9][9]) {
  printf("\n+-------+-------+-------+");
  for (int row = 0; row < 9; row++) {
    if (row % 3 == 0 && row != 0) {
      printf("\n|-------+-------+-------|");
    }
    printf("\n");
    for (int col = 0; col < 9; col++) {
      if (col % 3 == 0) {
        printf("| ");
      }
      if (puzzle[row][col] != 0) {
        printf("%d ", puzzle[row][col]);
      } else {
        printf("  ");
      }
    }
    printf("|");
  }
  printf("\n+-------+-------+-------+\n");
}