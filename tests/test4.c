#include <stdlib.h>
#include <stdio.h>

int inspect_bits(unsigned int number)
{
  int i;
  int val = 0;
  for(i = 0; i < 32; i++)
  {
    
    if(val & ((number >> i) & 0x1))
        return 1;
    if(!(number >> i))
        return 0;

    val = ((number >> i) & 0x1);
  }
  return 0;
}


#ifndef RunTests
int main ()
{
  printf("%d", inspect_bits(8));
}
#endif
