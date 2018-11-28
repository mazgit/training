#include <stdio.h>
#include <stdlib.h>


/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int QmarkBoard(char ** board, int n, int start_y, int start_x)
{
  int new_x, new_y, b, row, col, Q;
  int x , y;
  int i_x, i_y;

  Q = 0;
  
  printf("x: %d y:%d\n", start_x, start_y);
  
  for(x=start_x, i_x =0; i_x<n; x = (x+1)%n, i_x++)
  {
    for(y=start_y, i_y = 0; i_y < n; y = (y+1)%n, i_y++)
    {
      if(board[y][x])
          continue;
  
      //board[row = y][col = x] = '.';
      for(new_y = 0; new_y < n ; new_y++)
      {
    
        for(new_x = 0; new_x < n ; new_x++)
        {
          if((board[new_y][new_x] == '.') || (board[new_y][new_x] =='Q'))
          {
            continue;
          }

          else if(x == new_x && y == new_y)
          {
            board[new_y][new_x] = 'Q';
            Q++;
            continue;
          }

          //mark row
          else if(y == new_y)
          {
            board[new_y][new_x] = '.';
            continue;
          }

          //mark col
          else if(x == new_x)
          {
            board[new_y][new_x] = '.';

          }

          //mark -1 slope
          //b = y - x*-1;
          else if(new_y == new_x*-1+(y - x*-1))
          {
            board[new_y][new_x] = '.';
            
          }

          //mark +1 slope
          //b = y - x;
          else if(new_y == new_x+(y-x))
          {
            board[new_y][new_x] = '.';

          }
        }

      }
    }
  }

  return Q;
  
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

char*** solveNQueens(int n, int* returnSize) {
  char ** board = (char**)calloc(n, sizeof(char*));
  int row, col;
  int Q; //number of queens on board
  
  *returnSize = 0;

  //search the board until either there are no more spaces or number of queens are found
  //create and clear board
  int i;
  
  for(row=0 ; row < n ; row++)
  {
    for(col=0 ; col < n ; col++)
    {
      
      for(i=0 ; i < n ; i++)
      {
        board[i] = (char*)calloc(n+1, sizeof(char));
      }
      
      *returnSize = QmarkBoard(board, n, row, col);

      if(*returnSize == n)
      {
        printf("\n---\nQ: %d\n", *returnSize);
        print(board, n);
        }
    }
  }

  return NULL;

}

int main()
{
  int returnSize = 0;
  solveNQueens(5, &returnSize);
  return 0;
}
