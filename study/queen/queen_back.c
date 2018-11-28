#include <stdio.h>
#include <stdlib.h>



int okToPlace(char ** board, int n , int x, int y)
{
  int xx = 0;
  int yy = 0;
  
  if(x >= n || y >= n)
      return 0;
  
  //check row
  for(xx = 0; xx < n; xx++)
  {
    if(board[y][xx] == 'Q')
        return 0;
  }
  
  //check col
  for(yy = 0; yy < n; yy++)
  {
    if(board[yy][x] == 'Q')
        return 0;
  }

  //check diag -1
  for(xx = x, yy = y; xx < n && yy >= 0; xx++, yy--)
      if(board[yy][xx] == 'Q')
          return 0;

  //check diag +1
  for(xx = x, yy = y; xx >= 0 && yy >=0; xx--, yy--)
      if(board[yy][xx] == 'Q')
          return 0;

  return 1;
}

//if ok to set then set
//move to next square and recurse
//if Q == n; solution found
//if x == n && y == n; solution not found
//if not ok to set; solution not found

int traverse(char** board, int n , int Q, int x_start, int y)
{

  if(Q == n)
      return 1;

  if(y == n)
      return 0;
  
  int x;
  for(x = x_start; x<n; x++)
  {
    if(okToPlace(board, n , x, y))
    {
      board[y][x] = 'Q';
      Q++;
    
      if(traverse(board, n, Q, 0, y+1))
      {
        return 1;
      }
      else
      {
        board[y][x] == '.';
        Q--;
      }
    
    }
  }
  
  return 0;
}
    



void print(char**board, int n)
{
  
  int row;
  //print
  for(row=0 ; row < n ; row++)
  {
    printf("%s\n", board[row]);
  }
  printf("\n");

}


void clear(char**board, int n)
{
  
  int row, col;
  
  for(row=0 ; row < n ; row++)
  {
    for(col = 0; col < n; col++)
    {
      board [row][col] = '.';
    }
  }
  

}


char*** solveNQueens(int n, int* returnSize) {
  char ** board = (char**)calloc(n, sizeof(char*));
  int row, col;
  int Q; //number of queens on board
  
  *returnSize = 0;

  
  int i;
  for(i=0 ; i < n ; i++)
  {
    board[i] = (char*)calloc(n+1, sizeof(char));
    for(col = 0; col < n ; col ++)
    {
      board[i][col] = '.';
    }
  }

  for(col = 0; col < n; col++)
  {
    clear(board, n);
    if(traverse(board, n , 0, col, 0))
        print(board, n);
  }
  
  return NULL;

}

int main()
{
  int returnSize = 0;
  solveNQueens(5, &returnSize);
  return 0;
}
