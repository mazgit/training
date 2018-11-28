#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int pal_number(int x)
{
  int * vals;
  int count = 0; 
  int i , j;
  
  count = (int)(log10(x)+1.0);
  printf("count = %d\n",count);
  vals = calloc(count, sizeof(int));
  
  //extract num
  for(i = 0; i<count; i++)
  {
    vals[i] = x%10; //extract num - 3, 1, 2, 1
    x = x/10; //remove tens unit - 121, 12, 1, 0, 
  }

  //determine if palendrom  
  for(i = 0, j= count-1; i < count/2; i++, j--) //count = 4/2 = 2
  {
    if(vals[i] != vals[j]) //(0,3) (1,2)
    {
        return 0;
    }
  }

  return 1;
}

//stopped, doesn't fully work -- need to compare from the middle out
int pal_number2(int x)
{
  int * vals;
  int count = 0; 
  int i , j;
  
  count = (int)(log10f(x)+1.0);
  printf("count = %d\n",count);
  vals = calloc(count, sizeof(int));

  int half = count/2 + (count%2); //skip over odd middle case 1+1 = 2
  
  //extract num
  for(i = 0; i<count; i++)
  {
    vals[i] = x%10; //extract num - 3, 1, 2, 1
    x = x/10; //remove tens unit - 121, 12, 1, 0,

    printf("i[%d]\n", i);
    
    //compare
    if(i >= half) //3-2
    {
      printf("i-half[%d]\n", i-half);
      
      if(vals[i-half] != vals[i])
          printf("vals[%d](%d) != vals[%d](%d)", i-half, vals[i-half], i, vals[i]);
          return 0;
    }
  }

  return 1;
}

int main()
{
  printf("%d\n", pal_number(1001));
  printf("%d\n", pal_number2(1001));
  return 0;
}
