#include <stdio.h>
#include <stdlib.h>


void swap(int * num1, int * num2)
{

  int tmp = *num1;
  *num1 = *num2;
  *num2 = tmp;
  
}


void product(int * num, int size, int * res, int j)
{
  if(j == size)
  {
      return;
  }

  *res = *res * num[j];
  product(num, size, res, j + 1);
}



int main()
{
  int num[] = {1, 7, 3, 4};
  int size = sizeof(num)/sizeof(num[0]);
  int i, j;
  
  int * res = (int*)malloc(sizeof(int) * size);

  //////////////////////// Basic iterative 
  for(i = 0; i<size; i++)
  {
    res[i] = 1;
    
    for(j = 0; j < size; j++)
    {
      if(!(i == j))
      {
        res[i] = res[i]*num[j];
      }
    }
  }

  
  for(i = 0; i<size; i++)
  {
    printf("%d ", res[i]);
  }
  printf("\n");

  //////////////////////// Swap iterative 

  for(i = 0; i<size; i++)
  {
    res[i] = 1;
    swap(&num[0], &num[i]);
    for(j = 1; j < size; j++)
    {
      res[i] = res[i]*num[j];
    }
    swap(&num[0], &num[i]);
  }
  
  for(i = 0; i<size; i++)
  {
    printf("%d ", res[i]);
  }
  printf("\n");


  //////////////////////// Swap recursion 

  for(i = 0; i<size; i++)
  {
    res[i] = 1;
    swap(&num[0], &num[i]);
    product(num, size, &res[i], 1);
    swap(&num[0], &num[i]);
  }

  for(i = 0; i<size; i++)
  {
    printf("%d ", res[i]);
  }
  printf("\n");

  //////////////////////// iterative new approach
  int total=1;

  for(i = 0; i<size; i++)
  {
    total = total * num[i];
  }

  for(i = 0; i<size; i++)
  {
    res[i] = total / num[i];
  }

  for(i = 0; i<size; i++)
  {
    printf("%d ", res[i]);
  }
  printf("\n");
  
  return 0;
}
     


