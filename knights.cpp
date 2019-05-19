    
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using std::string;
using std::cout;
using std::endl;

const int SIZE = 5;
int global_board[SIZE+4][SIZE+4];

void create_board(int board[SIZE+4][SIZE+4]) {
  for (int i = 0; i < SIZE + 4; i++) {
    for (int j = 0; j < SIZE + 4; j++) {
      if (i < 2 || j < 2 || i >= SIZE + 2 || j >= SIZE + 2) {
	board[i][j] = -1;      
      }
      else {
	board[i][j] = 0;
      }
    }
  }
}

void print_board(int board[SIZE+4][SIZE+4]) {
  std::cout << "^[[0;0H\n";
  for (int i = 0; i < SIZE + 4; i++) {
    for (int j = 0; j < SIZE + 4; j++) {
      cout << board[i][j] << "\t";
    }
    cout << endl;
  }
}

void solve(int board[SIZE+4][SIZE+4], int row, int col, int currNum, bool &solved) {
  //usleep(20000);
  int current = board[row][col];

  if (currNum == SIZE*SIZE + 1){ //donezo
    solved = true;
    return;
  }
  if (current != 0) { //off the board or already stepped on
    return;
  }

  /* recursively try to solve taking one step in each direction */
  board[row][col] = currNum;
  //print_board(board);

  if (!solved) solve(board,row+2,col+1, currNum + 1, solved);
  if (!solved) solve(board,row-2,col+1, currNum + 1, solved);
  if (!solved) solve(board,row+2,col-1, currNum + 1, solved);
  if (!solved) solve(board,row-2,col-1, currNum + 1, solved);
  if (!solved) solve(board,row+1,col+2, currNum + 1, solved);
  if (!solved) solve(board,row-1,col+2, currNum + 1, solved);
  if (!solved) solve(board,row+1,col-2, currNum + 1, solved);
  if (!solved) solve(board,row-1,col-2, currNum + 1, solved);
  if (!solved) board[row][col]=0;
}

int main() {
  int tracker = 1;  
  bool solved = false;
  create_board(global_board);
  solve(global_board, 2, 2, tracker, solved);
  print_board(global_board);
  return 0;
}