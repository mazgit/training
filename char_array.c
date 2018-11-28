#include <stdio.h>
char * c [] = {"IllegalInstruction",
                "Syscall"};

int main()
{
  printf("%s", c[0]);
  return 0;
}
