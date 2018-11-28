#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */



int add(char * mainString )
{
  return 0;
}

int append(char * mainString, char* subString)
{
  
  return 0;
}

int moves(char * mainString, int lengthMainString ,char* subString, int subIndex)
{
  //add
  if(subIndex == 0)
  {
    subString[subIndex] = mainString[subIndex];
    subIndex++;
    printf("'start' add (%s)\n", subString);
  }

  while(subIndex < lengthMainString)
  {
    //append
    int i;
    int append = 1;
    for(i = 0; i < subIndex; i++)
    {
      if(mainString[subIndex+i] != 0)
      {
        if(mainString[subIndex+i] == mainString[i])
        {
          continue;
        }
        else
        {
          //cannot append
          append = 0;
          break;
        }
      }
      else
      {
        // cannot append
        append = 0;
        break;
      }
    }

    if(append)
    {
      int j;
      for(j = subIndex; j< (subIndex*2); j++)
      {
        subString[j] = mainString[j];
      }
      printf("append (%s)\n", subString);
      subIndex += subIndex;
    }
    else
    {
      //add
      subString[subIndex] = mainString[subIndex];
      subIndex++;
      printf("add (%s)\n", subString);    
    }
  }
  
}

int main()
{
  char * inputString = "abcabcabcabc";
  char  *  subString;
  int i = 0;
  int length = 0;



  while(inputString[length] != 0)
  {
    length++;
  }


  subString = (char*) malloc(sizeof(char)*length);
  
  for(i = 0; i < length; i++)
  {
    subString [i] = 0;
  }

  
  moves(inputString, length, subString, 0);
  
  return 0;
}
