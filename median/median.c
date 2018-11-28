#include <stdio.h>
#include <stdlib.h>


typedef int bool;

enum{
  false,
  true 
};

int DEBUG = 1;

double median(int * a, int * b, int a_size, int b_size)
{
  int ai = 0;
  int bi = 0;
  
  //note this is the floor if even then need to account for 2 locations
  //int half = (a_size + b_size)/2;

  int i;
  
  int * tmp = malloc(sizeof(int)*(a_size+b_size));

  int half = (a_size+b_size)/2+2;
  
  for(i = 0; i < (a_size+b_size); i++)
  //for(i = 0; i < half; i++)
  {
    if(ai < a_size && bi < b_size)
    {
      if(a[ai] <= b[bi])
      {
        tmp[i] = a[ai];
        ai++;
      }
      else
      {
        tmp[i] = b[bi];
        bi++;
      }
    }
    else if(ai < a_size)
    {
      tmp[i] = a[ai];
      ai++;
    }
    else if(bi < b_size)
    {
      tmp[i] = b[bi];
      bi++;
    }
    else
    {
      if(DEBUG) printf("ERROR");
      return 1;
    }
    if(i == half+2)
    {
      break;
    }
        
  }

  //print
  for(i = 0; i < (a_size + b_size); i++)
  {
    if(DEBUG) printf("%d ", tmp[i]);
  }
  if(DEBUG) printf("\n");

  if(DEBUG) printf("total size: %d\n", a_size + b_size);
  
  double median = tmp[(a_size + b_size)/2];
  if(!((a_size + b_size) % 2))
  {
    
    median += tmp[((a_size + b_size)/2-1)];
    median = median / 2;
  }

  return median;
}

//find less than equal & return index
bool search_value(int search_val, int * array, int size, int * retVal, int * retIndex)
{
  int start = 0;
  int end = size;
  int range = end - start;

  
  do
  {
    range = end - start;
    
    int mid = range/2;

    if(DEBUG) printf("start[%d] end[%d] range[%d] mid[%d] \n", start, end, range, mid);

    int index = mid + start;

    
    if(array[index] == search_val)
    {
      if(index)
      {
        *retIndex = index - 1;
      }
      else
      {
        *retIndex = 0;
      }
      *retVal = array[index];
      return false;
    }
    else if(array[index] <= search_val)
    {
      start = index;
      continue;
    }
    else if(array[index] > search_val)
    {
      end = index;
      continue;
    }
  }while(range > 1);

  //min of start and end
  if(array[end] < search_val)
  {
      *retIndex = end;
      *retVal = array[end];
      return true;
  }
  else if(array[start] < search_val)
  {
      *retIndex = start;
      *retVal = array[start];
      return true;
  }
  else
  {
    return false;
  }

}

//find less than equal & return index
bool search_index(int median_index, int * a, int * b, int a_size, int b_size, int * return_index)
{
  int start = 0;
  int end = a_size;
  int range = end - start;
  int mid = 0;
  int index = 0;
  int b_index = 0;
  int b_val = 0;
  
  //reset of array check
  do
  {
    range = end - start;
    
    mid = range/2;
    
    //if(range <= 1)
    //{
    //  break;
    //}

    index = mid + start;

    if(DEBUG) printf("search index[%d]\n", index);
    b_index = 0;
    b_val;
    if(true == search_value(a[index], b, b_size,&b_val, &b_index))
    {
      if(DEBUG) printf("here\n");
    }
    if(DEBUG) printf("new index[%d]\n", index);
    
    if((index+b_index+1) == median_index)
    {
      * return_index = index;
      return true;
    }
    else if((index+b_index+1) < median_index)
    {
      start = index;
      continue;
    }
    else if((index+b_index+1) > median_index)
    {
      end = index;
      continue;
    }
  }  while(range > 1);

  return false; 
}



int helper_median_find(int median_index, int * a, int * b, int a_size, int b_size)
{
  //pick an array
  
  //search a
  int return_index;
    
  if(true == search_index(median_index, a, b, a_size, b_size, &return_index) && (a_size > 0))
  {
    return a[return_index];
  }
    
  //search b
  if(true == search_index(median_index, b, a, b_size, a_size, &return_index) && (b_size > 0))
  {
    return b[return_index];
  }
  
  if(DEBUG) printf("ERROR!\n");
  return 0;
}


//binary search case
double findMedianSortedArrays(int* a, int a_size, int* b, int b_size)
{
  //int search_val = 25;
  //int index = bin_find_lte(search_val, b, b_size);
  //if(DEBUG) printf("search_val(%d) >= array[%d](%d) \n", search_val, index, b[index]);
  //return -1.0;


  int median_index;
  //search for midian index
  median_index = (a_size+b_size)/2;
  if(DEBUG) printf("search median index (%d+%d)/2=[%d]\n", a_size,b_size,median_index);
  
  //for now assume max size is odd
  if((a_size+b_size)%2)
  {
    return helper_median_find(median_index, a, b, a_size, b_size);
  }
  else
  {

    int one = helper_median_find(median_index, a, b, a_size, b_size);
    int two = helper_median_find(median_index-1, a, b, a_size, b_size);

    if(DEBUG) printf("one[%d] two[%d]\n", one, two);
    
    return ((double)one+(double)two)/2.0;
  }
  
  return -2;  
  
}




int main()
{
  int  a[] = {1};
  int  b[] = {1};
  
  int a_size = sizeof(a)/sizeof(int);
  int b_size = sizeof(b)/sizeof(int);

  printf("median: %f\n", median(a, b, a_size, b_size));

  printf("median: %f\n", findMedianSortedArrays(a, a_size, b, b_size));

  return 0;
}
