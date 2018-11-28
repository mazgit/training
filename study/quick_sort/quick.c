#include <stdio.h>


void print(char * info, int * array, int size)
{
  int i = 0;

  printf("%s: ", info);
  
  for(i = 0; i<size; i++)
  {
    printf("%d, ", array[i]);
  }
  printf("\n");
  
}

void quickSort(char * info, int * array, int size)
{
  char newInfo [100];
  //base case
  if(size == 1 || size == 0)
  {
    return;
  }
  
  int * pivot = &(array[0]);
  int * left = &(array[1]);
  int * right = &(array[size-1]);
  
  int tmp;

  sprintf(newInfo, "%s (size:%d [L:%d , P: %d, R:%d])", info, size, *left, *pivot, *right);
  print(newInfo, array, size);
  
  //end of search when left > right
  while(left != right)
  {
    //search for left which is not <= pivot
    if(*left <= *pivot)
    {
      left++;
      continue;
    }

    //search for right which is not > pivot
    if(*right > *pivot)
    {
      right--;
    }

    printf("{%d < %d < %d} ", *left, *pivot, *right);
    
    //swap if both cases found
    if((*right <= *pivot) && (*left > *pivot) && (left != right))
    {
      sprintf(newInfo, "%s [swap(%d,%d)]", info, *left, *right);
      print(newInfo, array, size);
      tmp = *right;
      *right = *left;
      *left = tmp;
    }
    else
    {
      printf("\n");
    }
  }

  //swap pivot with left if needed
  if(*pivot > *left)
  {

    sprintf(newInfo, "%s [swap(%d,%d)]", info, *pivot, *left);
    print(newInfo, array, size);
    
    tmp = *pivot;
    *pivot = *left;
    *left = tmp;
  }

  sprintf(newInfo, "%s", info);
  print(newInfo, array, size);
  
  int leftSize = right - &(array[0]);
  //printf("LS:%d\n", leftSize);
  quickSort("LS", array, leftSize);

  int rightSize =  &(array[size - 1]) - left;
  //printf("RS:%d\n", leftSize);
  quickSort("RS", left, rightSize);


}



int main()
{

  int array [] = {13,0,23,4,5,67,8,9,14};
  int size = sizeof(array)/sizeof(array[0]);
  
  quickSort("begin", array, size);
  print("end", array, size);
  
  return 0;
}
