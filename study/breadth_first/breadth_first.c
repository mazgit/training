#include <stdio.h>

typedef struct node_t node_t;

struct node_t
{
  int val;
  node_t * left;
  node_t * right;
};


typedef struct
{
  node_t * container[10];
  int head;
  int tail;
}queue_t;

queue_t gQueue;
queue_t gQueueRev;


void pushQueue(node_t * pNode, queue_t* queue)
{
  queue->container[queue->head] = pNode;
  queue->head++;
}


node_t * popQueue(queue_t * queue)
{
  node_t * pNodeReturn;
  //pNodeReturn = gQueue.container[gQueue.head-1];
  //gQueue.head--;
  
  pNodeReturn = queue->container[queue->tail];
  queue->tail++;
  
  return pNodeReturn;
}

node_t * popStack(queue_t * queue)
{
  node_t * pNodeReturn;
  pNodeReturn = gQueue.container[queue->head-1];
  queue->head--;
  
  //pNodeReturn = queue->container[queue->tail];
  //queue->tail++;
  
  return pNodeReturn;
}

int emptyStack(queue_t *queue)
{
  return !(queue->head);
}


int emptyQueue(queue_t *queue)
{
  return (queue->head == queue->tail);
}

void bredth_first(node_t * pNode)
{
  node_t * pCurrentNode;
  if(pNode == NULL)
  {
    return;
  }

  pushQueue(pNode, &gQueue);
  pushQueue(pNode, &gQueueRev);

  while(!emptyQueue(&gQueue))
  {
    pNode = popQueue(&gQueue);

    printf("%d ", pNode->val);
    
    if(pNode->left != NULL)
    {
      pushQueue(pNode->left,&gQueue);
      pushQueue(pNode->left, &gQueueRev);
    }
    if(pNode->right != NULL)
    {
      pushQueue(pNode->right,&gQueue);
      pushQueue(pNode->right, &gQueueRev);
    }
  }

  printf("\n---\n");
  
  while(!emptyStack(&gQueueRev))
  {
    pNode = popStack(&gQueueRev);
    printf("%d ", pNode->val);    
  }

}

int main()
{
  node_t root[10];
  int i;

  //init
  gQueue.head = 0;
  gQueue.tail = 0;

  gQueueRev.head = 0;
  gQueueRev.tail = 0;
  
  for(i = 0; i <10; i++)
  {
    root[i].val = i;
  }
  
  root[0].left = &root[1];
  root[0].right = &root[2];
  
  root[1].left = &root[3];
  root[1].right = &root[4];
  
  root[2].left = &root[5];
  root[2].right = &root[6];

  root[3].left= NULL;
  root[3].right= NULL;
  root[4].left= NULL;
  root[4].right= NULL;
  root[5].left= NULL;
  root[5].right= NULL;
  root[6].left= NULL;
  root[6].right= NULL;

  bredth_first(root);  
  return 0;
}
