#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct
{
  int decimal;
  char numeral[2];
} NUMERAL_T;


char * convertRoman( int x )
{
  //create all numerals
  NUMERAL_T numerals[13] =
  {
    [0] = {.decimal = 1, .numeral = "I"},
    [1] = {.decimal = 4, .numeral = "IV"},
    [2] = {.decimal = 5, .numeral = "V"},
    [3] = {.decimal = 9, .numeral = "IX"},
    [4] = {.decimal = 10, .numeral = "X"},
    [5] = {.decimal = 40, .numeral = "XL"},
    [6] = {.decimal = 50, .numeral = "L"},
    [7] = {.decimal = 90, .numeral = "XC"},
    [8] = {.decimal = 100, .numeral = "C"},
    [9] = {.decimal = 400, .numeral = "CD"},
    [10] = {.decimal = 500, .numeral = "D"},
    [11] = {.decimal = 900, .numeral = "CM"},
    [12] = {.decimal = 1000, .numeral = "M"},
  };

  int size = log(x)/log(2);
  char * roman = calloc(size, sizeof(char));
  int romanPtr = roman;
  int i;
  
  
  while(x)
  {
    //find starting point
    for(i = 12; i>=0; i--)
    {
      if((x - numerals[i].decimal) >= 0)
          break;
    }
    int numeralIndex = i;
    int count = x/numerals[i].decimal;
    x = x - count * numerals[i].decimal;

    for(i = 0; i < count; i++)
    {
      strcat(romanPtr, numerals[numeralIndex].numeral);
    }
  }

  printf("%s\n", roman);
  
}

int main()
{
  convertRoman(1994);
  return 0;
}
