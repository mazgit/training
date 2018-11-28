#include <stdio.h>


int main()
{
  float num = .832;

  printf("float: %f\n", num);

  printf("int convert: %d.%d\n", (int)num, ((int)(num*1000))%1000);
  
  return 0;
}
