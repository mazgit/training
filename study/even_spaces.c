#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */


void evenSpace(char * string, int stringLen, int pageLen)
{
  //find number of total spaces per location
  int totalSpaces = pageLen - stringLen;
  
  
  //search for number of space locations
  int spaceLocations = 0;
  int i; 
  for(i = 0; i<stringLen; i++)
  {
    if(string[i] == ' ')
        spaceLocations++;
  }
  
  //determine number of spaces per location
  totalSpaces += spaceLocations;
  int totalSpacePerLoc = totalSpaces / spaceLocations;

  //extra space
  //int extraSpace = totalSpaces - totalSpacePerLoc*spaceLocations
  
  //print buffer
  char * pageString = (char*)calloc(pageLen+1, sizeof(char));

  //run through string and apply all the spaces needed to each space location. Note the last space location may require an additional space.

  int stringTracker = 0;
  int j = 0;
  int space;
  for(i = 0; i<stringLen; i++)
  {
    if(string[i] != ' ')
    {
      pageString[j] = string[i];
      j++;
    }
    else
    {
      //add spaces
      for(space = 0; space <totalSpacePerLoc; space++)
      {
        pageString[j] = ' ';
        j++;
      }
      //account for last space if applicable
      if((spaceLocations == 1) && (totalSpaces % 2))
      {
        pageString[j] = ' ';
        j++;        
      }
      
      spaceLocations--;
    }
    
  }

  printf("%s", pageString);
}

int main()
{
  char string[]="Dog is cu tes";
  int len = sizeof(string)/sizeof(string[0])-1;

  printf("string len: %d\n", len);
  
  evenSpace(string, len, 15);
  
  return 0;
}
