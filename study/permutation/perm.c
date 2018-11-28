#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void print(int * nums, int size)
{
  int i;
  printf("{");
  for(i=0;i<size;i++)
      printf("%d ",nums[i]);
  printf("}\n");
}

void swap(int * one, int*two)
{
  int tmp;
  tmp = *two;
  *two = *one;
  *one = tmp;
}


void perm2(int * nums, int size, int lock)
{
  int tmp;
  int i = 0;
  if(lock == size)
  {
    //print(nums,size);
    return;
  }
  
  for(i=0; i<size;i++)
  {
    if(lock != i)
    {
      tmp = nums[i];
      nums[i] = nums[lock];
      perm2(nums,size,lock+1);
      nums[i] = tmp;
    }

    print(nums,size);
    //perm(nums,size,0);
    
  }
  
}

void perm(int * nums, int size, int set, int lock)
{
  int i = 0;
  int tmp;
  
  if(lock == set)
  {
    print(nums,set);
    return;
  }
  
  for(i=lock; i<size;i++)
  {
    //printf("[%d,%d]-> ", lock,i);
    swap(&nums[lock], &nums[i]);
    perm(nums,size,set, lock+1);
    swap(&nums[lock], &nums[i]);

  }
}

int** permute(int* nums, int numsSize, int set, int* returnSize)
{
  perm(nums, numsSize, set, 0);  
  return NULL;
}


void combinations(int* nums, int size, int set, int lock, int * combs)
{

  if(lock == set)
  {
    print(combs,set);
    return;
  }

  //printf("lock: %d\n", lock);
  
  int i;
  for(i = 0; i < size; i++)
  {
    //printf("i:%d size:%d\n", i, size);
    combs[lock] = nums[i];
    combinations(nums, size, set, lock+1, combs);
    
  }
  
}

int main()
{
  int nums[]= {1,2,3, 4};
  int size = sizeof(nums)/sizeof(nums[0]);
  int* returnSize;
  int set = 3;
  printf("size: %d\n", size);
  
  permute(nums, size, set, returnSize);

  printf("---Attempting Combinations---\n");
  int combs[size];
  combinations(nums, size, set, 0, combs);
  return 0;
}
