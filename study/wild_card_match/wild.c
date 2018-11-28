#include <stdio.h>
#include <stdbool.h>

int DEBUG = 1;

bool isMatch(char* s, char* p) {
  
  if(DEBUG) printf("%s %s\n", p, s);
  
  while(*p && *s)
  {
    if(DEBUG) printf("%c %c\n", *p, *s);
    if(*p == '*')
    {
      if(DEBUG) printf("p(%c) == *\n", *p);

      if(*(p+1) == '*')
      {
        printf("1");
        continue;
      }
      
      if(*(p+1) == '?')
      {
        printf("2");
        continue;
      }
      
      p++;
      if(DEBUG) printf("p+1(%c) == s(%c)\n", *(p), *s);
      int tmp = 0;
      int max = 0;
      while(*(s+tmp) != 0)
      {
        if(DEBUG) printf("p+1(%c) == s(%c)\n", *(p), *(s+tmp));

        //keep track if another of the same char is found
        if(*(p) ==  *(s+tmp))
        {
          printf("max(%d)\n", max);
          max = tmp;
        }
        tmp++;
      }

      s+=max+1;
      p++;
      continue;
      
    }
    if((*p == '?') ||(*p == *s))
    {
      if(DEBUG) printf("p == s or p == ?\n");
      s++;
      p++;
      continue;
    }
    if(*p != *s)
    {
      if(DEBUG) printf("p != s\n");
      break;
    }

  }

  if(DEBUG) printf("%c %c\n", *p, *s);
  
  if(*p || *s)
  {
    printf("patern left (%s) / string left(%s)\n", p, s);
    return false;
  }

  return true;

}

int main()
{
  //char s []= "abceb";
  //char p []= "*a*b";
  char s []= "aa";
  char p []= "a";
  
  printf("return[%d]\n", isMatch(s,p));
}
