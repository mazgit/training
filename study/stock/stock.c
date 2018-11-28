#include <stdio.h>
#include <stdlib.h>


int getMaxProfit(int * price, size_t size)
{

  int max, min;
  
  if(size < 2)
      return;

  max = price[0];
  min = price[1];
  if(price[0] < price[1])
  {
    max = price[1];
    min = price[0];
  }

  int i;
  
  for(i = 2; i < size; i ++)
  {
    if(price[i] < min)
    {
      min = price[i];
    }
    if(price[i] > max)
    {
      max = price[i];
    }
    
  }

  return max - min;
  
}


int getMaxProfitGreedy(int * price, size_t size)
{
  
  
}

int main()
{
  int stockPrices[6] = {10, 7, 5, 8, 11, 9};
  size_t numStockPrices = 6;

  printf("%d\n", getMaxProfit(stockPrices, numStockPrices));
  return 0;
}
