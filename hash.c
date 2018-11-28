#include <stdlib.h>
#include <stdio.h>



typedef struct hash_element_t hash_element_t;
typedef int bool;
enum
{
  true = 1,
  false = 0
};

bool DEBUG = false;

struct hash_element_t
{
  int key;
  int val;
  hash_element_t * next;
  
  hash_element_t * lru; //next
  hash_element_t * mru; //prev
};

typedef struct
{
  int size;
  hash_element_t ** map;
} hash_t;

typedef struct {
  int size;
  hash_element_t * head; //LRU
  hash_element_t * tail; //MRU
  hash_t * cache;
} LRUCache;

hash_t * hashCreate(int size)
{
  int i;
  hash_t * newHash = (hash_t *) malloc(sizeof(hash_t));
  newHash->map = (hash_element_t**)malloc(sizeof(hash_element_t*)*size);
  newHash->size = size;

  //initialize hash
  for(i = 0; i < size; i++)
  {
    newHash->map[i] = NULL;
  }
          
  return newHash;
}

hash_element_t * hashGet(hash_t * obj, int key)
{
  //determine hash position
  int pos = key % obj->size;

  hash_element_t * next;
  
  //search through list if any
  for(next = obj->map[pos]; next != NULL ; next = next->next)
  {
    if(key == next->key)
    {
      return next;
    }
  }
  
  return NULL;
}

hash_element_t* hashPut(hash_t * obj, int key, int val, bool * replacedFlag)
{

  int pos = key % obj->size;
  hash_element_t * search = obj->map[pos];

  *replacedFlag = false;
  
  if(obj->map[pos] == NULL)
  {
    search = (hash_element_t*)malloc(sizeof(hash_element_t));
    search->val = val;
    search->key = key;
    search->lru = NULL;
    search->mru = NULL;
    search->next = NULL;
    obj->map[pos] = search;
  }
  else
  {
    hash_element_t * prev = NULL;
    while(search != NULL)
    {
      if(search->key == key)
      {
        if(DEBUG==true) printf("\t~RPL K[%d] V[%d -> %d]\n", key, search->val, val);
        search->val = val;
        *replacedFlag = true;
        break;
      }

      if(search->next == NULL)
      {          
        search->next = (hash_element_t*)malloc(sizeof(hash_element_t));
        search->next->val = val;
        search->next->key = key;
        search->next->lru = NULL;
        search->next->mru = NULL;
        search->next->next = NULL;
      
        search = search->next;
        break;
      }
      
      search = search->next;
    }
  }
  if(DEBUG==true) printf("\t+K[%d] / V[%d] / I[%d]\n", key, val,pos);
  return search;
}


void hashRemove(hash_t * obj, int key)
{
  int pos = key % obj->size;
  hash_element_t * search = obj->map[pos];
  hash_element_t * prev = NULL;

  
  //search to find key
  while(search != NULL)
  {
    if(search->key == key)
    {
      //remove item
      if(prev != NULL)
      {
        //not first element
        prev->next = search->next;
        free(search);
      }
      else
      {
        //first element
        obj->map[pos] = search->next;
        free(search);
      }
      return;
    }
    prev = search;
    search = search->next;
  }
  
}

LRUCache* lRUCacheCreate(int capacity)
{
  LRUCache* lru = (LRUCache* )malloc(sizeof(LRUCache));
  lru->cache = hashCreate(capacity);

  lru->head = NULL;
  lru->tail = NULL;

  lru->size = capacity;

  if(DEBUG==true) printf("Creating LRU Cache size %d\n", lru->size);
  
  return lru;
}


void adjustMru(LRUCache* obj, hash_element_t * element)
{
  if(DEBUG==true) printf("\tMRU K[%d]\n", element->key);

  if(element == obj->tail)
  {
    //it is already mru
    return;
  }
  
  if(obj->head == NULL && obj->tail == NULL)
  {
    //first item in LRU
    obj->head = element;
    obj->tail = element;
  }
  else if(element == obj->head)
  {
      
    //adjust LRU head
    obj->head = obj->head->mru; 
 
    //adjust MRU tail
    obj->tail->mru = element;
    element->lru = obj->tail;
    element->mru = NULL;
    obj->tail = element;
  }
  else
  {
    //replace lru and make it mru
    if(element->lru && element->mru)
    {
      //element is from the list
      //remove from lru list
      element->lru->mru = element->mru;
      element->mru->lru = element->lru;
    }
    
    //element is not apart of the list
    //adjust MRU tail
    obj->tail->mru = element;
    element->lru = obj->tail;
    element->mru = NULL;
    obj->tail = element;        
  }
}

void LRUPrint(LRUCache* obj)
{
  hash_element_t * tmp = obj->head;

  if(DEBUG==true) printf("\tLRU[");
  
  while(tmp != NULL)
  {
    if(DEBUG==true) printf("(%d,%d) ", tmp->key, tmp->val);
    tmp = tmp->mru;
  }
  if(DEBUG==true) printf("]\n");

}

void lRUCachePut(LRUCache* obj, int key, int value) 
{
  hash_element_t * element;
  bool replaced = false;
  //add new element if there is space else evict something

  if(DEBUG==true) printf("PUT K[%d] / V[%d]\n", key, value);
  
  if(obj->size > 0)
  {
    //add new element and make it MRU
    if((obj->head == NULL) && (obj->tail == NULL))
    {
      
      element = hashPut(obj->cache, key, value, &replaced);
      adjustMru(obj, element);
    }
    else
    {
      element = hashPut(obj->cache, key, value, &replaced);
      adjustMru(obj, element);
    }

    if(replaced == false)
    {
      obj->size--;
    }
  }
  else
  {

    element = hashGet(obj->cache, key);
    if(element)
    {
      //replace current value with new one
      element->val = value;
      adjustMru(obj, element);      
    }
    else
    {
      //evict
      if(DEBUG==true) printf("\tEVCT K[%d]\n", obj->head->key);
      
      //remove from lru
      hash_element_t *evict = obj->head;
      
      obj->head = obj->head->mru;
      
      if(evict == obj->tail)
      {
        obj->tail = NULL;
      }
      
      //remove from memory
      hashRemove(obj->cache, evict->key);
      
      //place new element
      element = hashPut(obj->cache, key, value, &replaced);

      //adjust mru
      adjustMru(obj, element);      
    }
  }

  LRUPrint(obj);
  
}



int lRUCacheGet(LRUCache* obj, int key) {
  int val;
  hash_element_t * element = hashGet(obj->cache, key);
  if(element)
  {
    val =  element->val;
    if(DEBUG==true) printf("GET K[%d] / V[%d]\n", key, val);
    adjustMru(obj, element);
  }
  else
  {
    val =  -1;
    if(DEBUG==true) printf("GET K[%d] / V[%d]\n", key, val);
  }

  LRUPrint(obj);
  
  return val;
}

void hashGetPrint(hash_t * obj, int key)
{

  hash_element_t * element = hashGet(obj, key);
  if(element)
  {
    if(DEBUG==true) printf("%d\n",element->val);
  }
  else
  {
    if(DEBUG==true) printf("key %d does not exist\n", key);
  }
  
}

int main()
{
  //hash_t * hash = hashCreate(10);
  //hashPut(hash,10,5);
  //hashPut(hash,10,5);
  //hashPut(hash,10,5);
  //hashPut(hash,10,5);
  //
  //hashGetPrint(hash,10);
  //hashGetPrint(hash,10);
  //hashGetPrint(hash,10);
  //hashGetPrint(hash,10);
  //hashGetPrint(hash,10);
  //
  //hashPut(hash,12,123);
  //hashGetPrint(hash,2);
  //hashPut(hash,2,122);
  //hashGetPrint(hash,10);
  //hashRemove(hash,2);
  //hashGetPrint(hash,2);
  //hashPut(hash,2,122);
  //hashPut(hash,12,123);
  //hashGetPrint(hash,2);
  //hashGetPrint(hash,12);


  /*
    LRUCache * lru = lRUCacheCreate(10);
    lRUCachePut(lru,10,13);
    lRUCachePut(lru,3,17);
    lRUCachePut(lru,6,11);
    lRUCachePut(lru,10,5);
    lRUCachePut(lru,9,10);
    lRUCacheGet(lru,13);
    lRUCachePut(lru,2,19);
    lRUCacheGet(lru,2);
    lRUCacheGet(lru,3);
    lRUCachePut(lru,5,25);
    lRUCacheGet(lru,8);
    lRUCachePut(lru,9,22);
    lRUCachePut(lru,5,5);
    lRUCachePut(lru,1,30);
    lRUCacheGet(lru,11);
    lRUCachePut(lru,9,12);
    lRUCacheGet(lru,7);
    lRUCacheGet(lru,5);
    lRUCacheGet(lru,8);
    lRUCacheGet(lru,9);
    lRUCachePut(lru,4,30);
    lRUCachePut(lru,9,3);
    lRUCacheGet(lru,9);
    lRUCacheGet(lru,10);
    lRUCacheGet(lru,10);
    lRUCachePut(lru,6,14);
    lRUCachePut(lru,3,1);
    lRUCacheGet(lru,3);
    lRUCachePut(lru,10,11);
    lRUCacheGet(lru,8);
    lRUCachePut(lru,2,14);
    lRUCacheGet(lru,1);
    lRUCacheGet(lru,5);
    lRUCacheGet(lru,4);
    lRUCachePut(lru,11,4);
    lRUCachePut(lru,12,24);
    lRUCachePut(lru,5,18);
    lRUCacheGet(lru,13);
    lRUCachePut(lru,7,23);
    lRUCacheGet(lru,8);
    lRUCacheGet(lru,12);
    lRUCachePut(lru,3,27);
    lRUCachePut(lru,2,12);
    lRUCacheGet(lru,5);
    lRUCachePut(lru,2,9);
    lRUCachePut(lru,13,4);
    lRUCachePut(lru,8,18);
    lRUCachePut(lru,1,7);
    lRUCacheGet(lru,6);
    lRUCachePut(lru,9,29);
    lRUCachePut(lru,8,21);
    lRUCacheGet(lru,5);
    lRUCachePut(lru,6,30);
    lRUCachePut(lru,1,12);
    lRUCacheGet(lru,10);
    lRUCachePut(lru,4,15);
    lRUCachePut(lru,7,22);
    lRUCachePut(lru,11,26);
    lRUCachePut(lru,8,17);
    lRUCachePut(lru,9,29);
    lRUCacheGet(lru,5);
    lRUCachePut(lru,3,4);
    lRUCachePut(lru,11,30);
    lRUCacheGet(lru,12);
    lRUCachePut(lru,4,29);
    lRUCacheGet(lru,3);
    lRUCacheGet(lru,9);
    lRUCacheGet(lru,6);
    lRUCachePut(lru,3,4);
    lRUCacheGet(lru,1);
    lRUCacheGet(lru,10);
    lRUCachePut(lru,3,29);
    lRUCachePut(lru,10,28);
    lRUCachePut(lru,1,20);
    lRUCachePut(lru,11,13);
    lRUCacheGet(lru,3);
    lRUCachePut(lru,3,12);
    lRUCachePut(lru,3,8);
    lRUCachePut(lru,10,9);
    lRUCachePut(lru,3,26);
    lRUCacheGet(lru,8);
    lRUCacheGet(lru,7);
    lRUCacheGet(lru,5);
    lRUCachePut(lru,13,17);
    lRUCachePut(lru,2,27);
    lRUCachePut(lru,11,15);
    lRUCacheGet(lru,12);
    lRUCachePut(lru,9,19);
    lRUCachePut(lru,2,15);
    lRUCachePut(lru,3,16);
    lRUCacheGet(lru,1);
    lRUCachePut(lru,12,17);
    lRUCachePut(lru,9,1);
    lRUCachePut(lru,6,19);
    lRUCacheGet(lru,4);
    lRUCacheGet(lru,5);
    lRUCacheGet(lru,5);
    lRUCachePut(lru,8,1);
    lRUCachePut(lru,11,7);
    lRUCachePut(lru,5,2);
    lRUCachePut(lru,9,28);
    lRUCacheGet(lru,1);
    lRUCachePut(lru,2,2);
    lRUCachePut(lru,7,4);
    lRUCachePut(lru,4,22);
    lRUCachePut(lru,7,24);
    lRUCachePut(lru,9,26);
    lRUCachePut(lru,13,28);
    lRUCachePut(lru,11,26);  
  */

  LRUCache * lru = lRUCacheCreate(1);
  lRUCachePut(lru,2,1);
  lRUCacheGet(lru,2);
  lRUCachePut(lru,3,2);
  lRUCacheGet(lru,2);
  lRUCacheGet(lru,3);

  
  return 0;
}
