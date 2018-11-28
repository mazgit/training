#include <stdlib.h>
#include <stdio.h>

typedef struct
{
  int val;
  typedef struct hash_element_t * next;
} hash_element_t;

typedef struct
{
  int size;
  hash_element_t * map;
} hash_t;

hash_t * create(int size)
{
  hash_t * 
}

void get(hash_t * obj, int key, int val)
{

}

void put(hash_t * obj, int key, int val)
{

}


int main()
{
  return 0;
}
