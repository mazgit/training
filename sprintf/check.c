
#include <stdio.h>
#include <string.h>

char string [] = {'A', 'm', 'a', 'n', 0, 'G', 'a', 'r', 'c', 'h', 'a', '\0'};
int main()
{
  char first  [100];
  char last [100];
  
  printf("Original Printout:(note there is a NULL in the middle after the first name)\n");
  printf("\t%s\n\n", string);

  printf("Splitting the string using pointers into the string buffer & sprintf()\n");
  printf("Now first and last are showing\n");
  sprintf(first, "%s", string);
  sprintf(last, "%s", string+strlen(first)+1/*account for null character*/);
  
  printf("\t%s\n", first);
  printf("\t%s\n", last);
  
  
  return 0;
}
