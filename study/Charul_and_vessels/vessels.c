#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */


int compare (const void * a, const void * b)
{
  //return ( *(int*)a - *(int*)b );
  return ( *(int*)a < *(int*)b );
}

int fillContainer(int container, int * vessels, int vesselCount, int vesselIndex)
{
  int i;
  int leftover;

  printf("container %d / vessels[%d]=%d\n", container, vesselIndex, vessels[vesselIndex]);
  
  for(i = vesselIndex; i<vesselCount; i++)
  {
    if(vessels[i] <= container)
    {
      break;
    }
  }

  vesselIndex = i;
  
  if(vesselIndex == vesselCount)
  {
    //no vessels fit the container
    return 0;
  }

  leftover = container - (container/vessels[vesselIndex])*vessels[vesselIndex];
  printf("leftover: %d\n", leftover);
  
  if(leftover == 0)
      return 1;
  else
      if( fillContainer(leftover, vessels, vesselCount, vesselIndex+1))
          return 1;
      else
          return fillContainer(container, vessels, vesselCount, vesselIndex+1);
}

int main()
{
  int container = 24;

  int vessels [] = {35,16,88,53,85,16,79,18,81,59,27,90,72,25,94,46,32,51,72,47,98,60,72,56,37,29,33,73,25,100,21,55,13,46,49,72,22,97,46,17,56,75,92,96,50,15,57,77,66,87,68,57,15,88,87,22,21,56,49,44,20,10,14,18,30,73,25,58,18,61,30,42,78,42,19,19,7,11,52,62,56,61,52,30,66,55,68,98,83,90,57,81,27,43,47};


  qsort(vessels, 95, 4, compare);

  int i;
  for(i = 0; i < 95; i++)
  {
    printf("%d ", vessels[i]);
  }
          
  printf("\n%d\n", fillContainer(container, vessels, 95, 0));

  return 0;
}
