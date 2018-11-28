#include <stdio.h>
#include <stdlib.h>


int frog(int distance, int jumps)
{
  
  if(distance == 0)
  {
    return 1; //true
  }

  if(distance < 0)
      return 0;
  
  return frog(distance -1 , 1) + frog(distance -2 , 2);
}



int main()
{
  int distance = 11;
  printf("distance = %d, jumps = %d\n", distance, frog(distance, 0));
  return 0;
}
