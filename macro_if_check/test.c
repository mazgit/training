#include <stdio.h>

#define HWD_SET_FIELD_S_OFFSET(addr, lsbloc, nbits,regType, str ,o,v) \
        do{                                                           \
          if(regType == 0x08U)                                        \
          {                                                           \
            printf("hit1\n");                                                 \
          }                                                           \
          else                                                        \
          {                                                           \
            printf("hit2\n");                                                 \
          }                                                           \
        }while(0);


int main()
{
  int i = 1;
  if(i)
      HWD_SET_FIELD_S_OFFSET(0, 0, 0,0, 0 ,0,0)
  else
      HWD_SET_FIELD_S_OFFSET(0, 0, 0,0, 0 ,0,0)

  if(i)
      do{
        if(i)
        {
        printf("hey\n");
        }
        else
        {
          printf("bye\n");
        }
      }while(0);
  
  else
      do{
        if(i)
        {
        printf("hey\n");
        }
        else
        {
          printf("bye\n");
        }
      }while(0);

  return 0;
}

