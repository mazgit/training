#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if 0
void sort_words(char *words[], int count)
{
  int index;
  int iteration;
  int charIndex;
  char * container;
  int i;
  int swapFlag = 1;
  int cmp_val = 0;
            
  for(iteration = 0; iteration < count; iteration++)
  {
    printf("sawp(%d) ", swapFlag);
    
    if(swapFlag == 0) 
        break;
    
    swapFlag = 0;
    
    for(index = 0 ; index < count-1-iteration; index++)
    {

      cmp_val = strcmp(words[index], words[index+1]);
      printf("cmp(%s, %s) = %d\n", words[index], words[index+1], cmp_val);
                
      if(0>cmp_val)
      {
        swapFlag = 1;
        container = words[index];
        words[index] = words[index+1];
        words[index+1] = container;
      }

    }
  }
  printf("iterations: %d\n", iteration);
}
#else

/* qsort C-string comparison function */
int cstring_cmp(const void *a, const void *b)
{
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return -1*strcmp(*ia, *ib);
  /* strcmp functions works exactly as expected from
     comparison function */
}

void sort_words(char *words[], int count)
{

  int i, half_count;
  char* tmp;

  qsort(words, count, sizeof(char*), cstring_cmp);

  //half_count = (count)/2;
  //for(i = 0; i<=half_count; i++)
  //{
  //  tmp = words[i];
  //  words[i] = words[count-i-1];
  //  words[count - i-1] = tmp;
  //}
  
}
#endif

#ifndef RunTests
int main()
{
  int i;
  char *words[] = { "cherry",//0
                    "orange",//1
                    "apple",//2
                    "banna",//3
                    "aman" ,//4
                    "test",//5
                    "what",//6
                    "cherry",//7
                    "orange",//8
                    "app",//9
                    "bann",//10
                    "ama" ,//11
                    "tes"};//12

  sort_words(words, 13);

  for (i = 0; i < 13; i++)
  {
    printf("%s ", words[i]);
  }
}
#endif
