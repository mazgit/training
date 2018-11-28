#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int min(int x, int y)
{

  if(x < y)
      return x;
  return y;
      
}

//n^2
int maxContainer(int *x, int size)
{
  int i, j;
  int len;
  int maxArea = 0;
  int area;

  //n^2
  for(i = 0; i< size-1; i++)
  {
      for(j = i+1; j< size; j++)
      {
        len = min(x[i],x[j]);
        area = len * (j - i);
        if(maxArea < area)
        {
          maxArea = area;
        }
      }
  }

  return maxArea;
}


//inside out O(n)
int maxContainer2(int * x, int size)
{
  int i, j;
  int area, len;
  int maxArea = 0;
  
  //for(i = 0, j = size-1; i < size; i++, j--)
  i = 0;
  j = size -1;
  while(i != j)
  {
    len  = min(x[i], x[j]);
    area = len * (j - i);
    
    if(maxArea < area)
    {
      maxArea = area;
    }

    //move the container walls to try to maximize area
    if(x[i] < x[j])
    {
      i++;
    }
    else
    {
      j--;
    }
    
  }
  
  return maxArea;
}


int main()
{
  int x [] =  {1,8,6,2,5,4,8,3,7};

  int size = sizeof(x) / sizeof(x[0]);
  
  printf("%d\n",maxContainer(x, size));
  printf("%d\n",maxContainer2(x, size));
  
  return 0;
}
