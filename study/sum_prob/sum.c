#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


void sum(int * nums, int size, int total, int currentSum, int position)
{
  if(currentSum == total)
  {
    printf("found sum: %d\n ", currentSum);
    return;
  }
  else if(currentSum > total)
  {
    printf("sum > total: %d\n ", currentSum);
    return;
  }
  else
  {
    return sum(nums, size, total, currentSum + nums[position], position + 1);
  }
  
}

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int main()
{
  int nums[]= {0,3,4,2,1,3,45,6,4,22,3,1,3,4,533,3,56};
  
  qsort(nums, sizeof(nums)/sizeof(nums[0]), sizeof(int), cmpfunc);
  
  sum(nums, sizeof(nums)/sizeof(nums[0]), 35, 0, 0);
  return 0;
}
