
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



int charToInt(char c)
{
  int x;
  x = c - '0';
  //printf("%c == %x\n", c, x);
  return x;

}

char intToChar(int x)
{
  x = x + '0';
  return x;
}

int validateSelection(char** board, int boardRowSize, int boardColSize, int row, int col, int val)
{
  int y, x;

  //validate selection

  //check entire row
  for(x = 0; x<boardColSize; x++)
  {
    if(val == charToInt(board[row][x]))
    {
      return 0; //fails
    }
  }

  //check entire col
  for(y = 0; y<boardRowSize; y++)
  {
    if(val == charToInt(board[y][col]))
    {
      return 0; //fails
    }
  }

  //check block
  int blockX, blockY;
  blockX = col/3;
  blockY = row/3;
  for(x = 0; x<3;x++)
  {
    for(y = 0; y<3;y++)
    {
      printf("BLK[%d,%d] / BD[%d][%d] = %d / Val[%d]\n", blockX, blockY, y + blockY*3,x + blockX*3, charToInt(board[y + blockY*3][x + blockX*3]), val);
      if(charToInt(board[y + blockY*3][x + blockX*3]) == val)
      {
        return 0;
      }
    }
  }

  return 1;

}


int nextLocation(char** board, int boardRowSize, int boardColSize, int y, int x, int * nextRow, int * nextCol)
{
  int row, col;

  //if(y >= boardRowSize-1)
  //    y = 0;
  //if(x >= boardColSize-1)
  //    x = 0;

  //find the starting location '.' on board

  for(row = 0; row < boardRowSize; row++)
  {
    for(col = 0; col < boardColSize; col++)
    {
      if(board[row][col] == '.')
      {
        printf("row[%d]col[%d]\n", row,col);
        *nextRow = row;
        *nextCol = col;
        return 1;
      }
    }
  }

  //not more spaces on the board
  return 0;
}


int solveSudo(char** board, int boardRowSize, int boardColSize, int row, int col)
{
  int nextRow, nextCol;
  //success: exit condition
  if((row == boardRowSize) && (col == boardColSize))
  {
    return 1;
  }

  printf("(%d, %d)\n", row, col);

  int i;
  //solve square
  for(i = 1; i <=9; i++)
  {
    if(validateSelection(board,  boardRowSize,  boardColSize,  row,  col, i))
    {
      board[row][col] = intToChar(i);
      if(! nextLocation(board, boardRowSize, boardColSize, row, col, &nextRow,&nextCol)) //find the next empty location
      {
        //square is solved
        return 1;
      }
      if(solveSudo(board, boardRowSize, boardColSize, nextRow, nextCol))
      {
        //square is solved
        return 1;
      }
      else
      {
        board[row][col] = '.';
      }
    }
  }

  //not solvable
  return 0;
}

void solveSudoku(char** board, int boardRowSize, int boardColSize) {
  int row, col;

  //find the starting location '.' on board
  for(row = 0; row < boardRowSize; row++)
  {
    for(col = 0; col < boardColSize; col++)
    {
      if(board[row][col] == '.')
      {
        printf("solved: %d\n",solveSudo(board, boardRowSize, boardColSize, row, col));
        return;
      }
    }
  }
}

int main()
{
  char boardx [9][9] = {{'5','3','.','.','7','.','.','.','.'},
                       {'6','.','.','1','9','5','.','.','.'},
                       {'.','9','8','.','.','.','.','6','.'},
                       {'8','.','.','.','6','.','.','.','3'},
                       {'4','.','.','8','.','3','.','.','1'},
                       {'7','.','.','.','2','.','.','.','6'},
                       {'.','6','.','.','.','.','2','8','.'},
                       {'.','.','.','4','1','9','.','.','5'},
                       {'.','.','.','.','8','.','.','7','9'}};

char boardx2 [9][9] = {{'5','3','.','.','7','.','.','.','.'},
                       {'6','.','.','1','9','5','.','.','.'},
                       {'.','9','8','.','.','.','.','6','.'},
                       {'8','.','.','.','6','.','.','.','3'},
                       {'4','.','.','8','.','3','.','.','1'},
                       {'7','.','.','.','2','.','.','.','6'},
                       {'.','6','.','.','.','.','2','8','.'},
                       {'.','.','.','4','1','9','.','.','5'},
                       {'.','.','.','.','8','.','.','7','9'}};

  
  char ** board = (char**)calloc(9, sizeof(char*));
  int i, j; 

  for(i = 0; i < 9; i++)
  {
    board[i] = (char*)calloc(9, sizeof(char));

    for(j = 0; j < 9; j++)
    {
      board[i] = boardx[i];
    }
    
  }
  
  
  //char * test = &(board[0][0]);
  
  solveSudoku(board, 9, 9);

int row, col;
//find the starting location '.' on board
  for(row = 0; row < 9; row++)
  {
    for(col = 0; col < 9; col++)
    {
      printf("%c ", boardx2[row][col]);
    }
    printf("\n");
  }
  printf("+++++++++++++++++\n");
  
//find the starting location '.' on board
  for(row = 0; row < 9; row++)
  {
    for(col = 0; col < 9; col++)
    {
      printf("%c ", board[row][col]);
    }
    printf("\n");
  }
  
  return 0;
}
