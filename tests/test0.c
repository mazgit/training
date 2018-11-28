#include <stdlib.h>
#include <stdio.h>

int low_case(char c)
{

  printf("enter %c '%d'\n", c, (int)c);
  if(c < (int)'a')
  {
    c += (int)'a'-(int)'A';
  }
  printf("exit %c\n", c);
  return (int)c;
}


int is_palindrome(char *str)
{
  char c = str[0];
  int i = 0;
  int word_length = 0;
  int half_word = 0;

  //determine length
  while(str[word_length] != '\0')
  {
    printf("%d %c\n", word_length, str[word_length]) ;
    word_length++;
  }

  
  //odd will be middle letter. so ok
  half_word = word_length / 2;
  printf("hwl %d\n", half_word);

  word_length--;
  printf("last %c %d\n",str[word_length-1], word_length);
  
  
  char beg, end;
  for(i = 0;  i < half_word; i++)
  {
    //make sure lower case all letters
    beg = low_case(str[i]);
    end = low_case(str[word_length-i]);

    printf("%c / %c\n", beg, end);
    
    if(beg - end)
    {
      return 0;
    }
  }
  return 1;
}

#ifndef RunTests
int main()
{
  char *str = "rraaRr";
  printf("%d", is_palindrome(str));
}
#endif
