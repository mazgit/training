#include <stdio.h>
#include <stdlib.h> 

struct ListNode {
    int val;
    struct ListNode *next;
};



struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

  struct ListNode* returnList;
  struct ListNode* current;
  struct ListNode* prev = NULL;
  int carry = 0;
  
  while(l1 != NULL || l2 != NULL || carry)
  {
    current = (struct ListNode*)malloc(sizeof(struct ListNode));
    current->next = NULL;
    current->val =0;

    if(prev == NULL)
    {
      prev = current;
      returnList = current;
    }
    else
    {
      prev->next = current;
      prev = current;
    }

    if(l1 && l2)
    {
      printf("adding %d + %d = %d\n", l1->val , l2->val, (l1->val + l2->val)%10);
      current->val = (l1->val + l2->val + carry)% 10;
      carry = (l1->val + l2->val)/10;
      l1 = l1->next;
      l2 = l2->next;
    }
    else if(l1)
    {
      //l1 only
      current->val = (l1->val + carry)% 10;
      carry = (l1->val + carry)/10;
      l1 = l1->next;
    }
    else if(l2)
    {
      //l2 only
      current->val = (l2->val + carry)% 10;
      carry = (l2->val + carry)/10;
      l2 = l2->next;
    }
    else
    {
      current->val = carry;
      carry = 0;
    }
    
  }

  return returnList;
}

void print(struct ListNode * root)
{
  while(root != NULL)
  {
    printf("%d\n", root->val);
    root = root->next;
  }
}

void add(struct ListNode ** root, int val)
{
  printf("adding %d\n", val);
  
  struct ListNode * new  = (struct ListNode * )malloc(sizeof(struct ListNode));
  new->val = val;
  
  if(*root == NULL)
  {
    *root = new;
    return;
  }

  struct ListNode *trav = *root;  
  while(trav->next != NULL)
  {
    trav = trav->next;
  }

  trav->next = new;
}


int main()
{
  struct ListNode * l1 = NULL;
  add(&l1, 1);
  add(&l1, 8);

  struct ListNode * l2 = NULL;
  add(&l2, 0);
  
  printf("\n\nl1:\n");
  print(l1);
  printf("\n\nl2:\n");
  print(l2);

  printf("\n\nl3:\n");
  struct ListNode * adding= addTwoNumbers(l1, l2);
  print(adding);  
  
}
