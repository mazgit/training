#include <stdio.h>
#include <math.h>
#include <time.h>

#define PRIMES_FROM_3_TO_128 (30)

typedef enum
{
  MXL_PRIME_MATRIX_PRIME,
  MXL_PRIME_MATRIX_VAL,
  MXL_PRIME_MATRIX_MAX
} MXL_PRIME_MATRIX_E;

float log2matrix [PRIMES_FROM_3_TO_128][MXL_PRIME_MATRIX_MAX]=
{
  {3      ,1.584962501},
  {5      ,2.321928095},
  {7      ,2.807354922},
  {11     ,3.459431619},
  {13     ,3.700439718},
  {17     ,4.087462841},
  {19     ,4.247927513},
  {23     ,4.523561956},
  {29     ,4.857980995},
  {31     ,4.95419631 },
  {37     ,5.209453366},
  {41     ,5.357552005},
  {43     ,5.426264755},
  {47     ,5.554588852},
  {53     ,5.727920455},
  {59     ,5.882643049},
  {61     ,5.930737338},
  {67     ,6.06608919 },
  {71     ,6.14974712 },
  {73     ,6.189824559},
  {79     ,6.303780748},
  {83     ,6.375039431},
  {89     ,6.475733431},
  {97     ,6.599912842},
  {101    ,6.658211483},
  {103    ,6.686500527},
  {107    ,6.741466986},
  {109    ,6.768184325},
  {113    ,6.820178962},
  {127    ,6.988684687},
};

float log_2(int i)
{
  int base2count = 0;
  int prime;
  
  //divide until prime
  while(!(i%2) && i != 0)
  {
    i = i >> 1;
    base2count++;
  }

  printf("\tdiv 2 count[%d]\n", base2count);
  printf("\tsearching for [%d]\n", i);
  
  for(prime = 0; prime < PRIMES_FROM_3_TO_128; prime++)
  {
    if(log2matrix[prime][MXL_PRIME_MATRIX_PRIME] == i)
    {
        break;
    }
  }

  printf("\tfound prime[%d]\n", (int)log2matrix[prime][MXL_PRIME_MATRIX_PRIME]);
  
  return log2matrix[prime][MXL_PRIME_MATRIX_VAL] + (float)base2count;
}


//val > 1/2
float taylorSeries1(float val)
{
  int ITERATIONS = 350;
  float base = 1;
  float ln = 0;
  int i;

  val = ((val) - 1.0)/(val);
  
  for(i = 1; i <= ITERATIONS; i++)
  {
    base = base * val;
    ln = ln + ((1.0/(float)i) * base);
  }

  return ln/0.69314718;
}


int main()
{
  int i = 0;
  float mine;
  float math_lib;
  float taylor;

  clock_t begin;
  clock_t end;
  double math_lib_time;
  double taylor_time;
  
  for(i = 1; i < 128; i++)
  {
    mine = log_2(i);

    begin = clock();
    math_lib = log10f((float)i)/log10f(2);
    end = clock();
    math_lib_time = (double)(end - begin) / CLOCKS_PER_SEC;

    begin = clock();
    taylor = taylorSeries1(i);
    end = clock();
    taylor_time = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("i[%d] mine[%f] math[%f] taylor[%f] delta[%f/%fs]\n", i, mine, math_lib, taylor, math_lib - taylor, math_lib_time-taylor_time);
  }
  
  return 0;
}
