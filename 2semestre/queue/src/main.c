// main.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//Test battery for adt_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_queue.h"

int main()
{
  Queue *queue = NULL;
  queue = QUEUE_Create(5);
  char data[1024];
  
  if(NULL == queue){
    printf("\n create returned a null queue");
    return 1;
  }
  printf("\ncapacity: %d", queue->ops_->capacity(queue));
  printf("\nlength: %d", queue->ops_->length(queue));
  printf("\n isEmpty: %d", queue->ops_->isEmpty(queue));
  printf("\n isFull: %d", queue->ops_->isFull(queue));

  queue->ops_->enqueue(queue, "Let's store strings", 20);
  queue->ops_->enqueue(queue, "go", 3);
  queue->ops_->enqueue(queue, "You are too slow",17); //out of range
  queue->ops_->enqueue(queue, "You are too slow",17); 

  memset(data, 0, sizeof(data));
  memcpy(data, queue->ops_->first(queue), 9);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, queue->ops_->last(queue), 8);
  printf("\n %s", data);

  printf("\ncapacity: %d", queue->ops_->capacity(queue));
  printf("\nlength: %d", queue->ops_->length(queue));
  printf("\n isEmpty: %d", queue->ops_->isEmpty(queue));
  printf("\n isFull: %d \n", queue->ops_->isFull(queue));

  queue->ops_->print(queue);
  queue->ops_->resize(queue, 7);
  queue->ops_->enqueue(queue, "Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  queue->ops_->print(queue); 
  queue->ops_->enqueue(queue, " inserting at 3", 16);
  printf("\n \n||||Third print:||||\n");
  queue->ops_->print(queue); 
  printf("\ncapacity: %d", queue->ops_->capacity(queue));
  printf("\nlength: %d", queue->ops_->length(queue));
  printf("\n isEmpty: %d", queue->ops_->isEmpty(queue));
  printf("\n isFull: %d \n", queue->ops_->isFull(queue));

  Queue *queue2 = NULL;
  queue2 = QUEUE_Create(2);

  Queue *queue3 = NULL;
  queue3 = QUEUE_Create(3);

  queue2->ops_->enqueue(queue2, "Let's concatenate", 18);
  queue2->ops_->enqueue(queue2, "now", 4);

  queue3->ops_->enqueue(queue3, "Concatenate with me", 20);
  queue3->ops_->enqueue(queue3, "come on!", 9);


  queue2->ops_->concat(queue2, queue3);
  queue3->ops_->destroy(&queue3);
  printf("\n \n|||| Fourth print: |||| \n");
  queue2->ops_->print(queue2); 
  printf("\ncapacity: %d", queue2->ops_->capacity(queue2));
  printf("\nlength: %d", queue2->ops_->length(queue2));
  printf("\n isEmpty: %d", queue2->ops_->isEmpty(queue2));
  printf("\n isFull: %d", queue2->ops_->isFull(queue2));

  memset(data, 0, sizeof(data));
  memcpy(data, queue2->ops_->dequeue(queue2), 18);
  printf("\n %s", data);
  queue2->ops_->dequeue(queue2);
  printf("\n \n|||queue2 after extract||| \n");
  queue2->ops_->print(queue2);
  queue2->ops_->enqueue(queue2, "I see you lost something", 25);
  printf("\n \n|||queue2||| \n");
  queue2->ops_->print(queue2);

  queue2->ops_->enqueue(queue2, "go", 3);
  queue2->ops_->enqueue(queue2, "again", 6);
  queue2->ops_->dequeue(queue2);
  queue2->ops_->dequeue(queue2);
  printf("\n \n|||queue2 ready to resize||| \n");
  queue2->ops_->print(queue2);
  queue2->ops_->resize(queue2, 3);
  printf("\n \n|||queue2 after resize||| \n");
  queue2->ops_->print(queue2);
  queue2->ops_->resize(queue2, 1);
  printf("\n \n|||queue2 after second resize||| \n");
  queue2->ops_->print(queue2);


  memset(data, 0, sizeof(data));
  memcpy(data, queue->ops_->dequeue(queue), 20);
  printf("\n %s \n", data);
  printf("\n \n|||queue before extract||| \n");
  queue->ops_->print(queue);
  queue->ops_->dequeue(queue);
  printf("\n \n|||queue after extract||| \n");
  queue->ops_->print(queue);

  queue->ops_->reset(queue);
  printf("\n \n|||queue after reset||| \n");
  queue->ops_->print(queue);
  queue->ops_->enqueue(queue, "Let's store strings", 20);
  printf("\n \n|||queue after insert||| \n");
  queue->ops_->print(queue);
  queue->ops_->destroy(&queue);
  queue2->ops_->destroy(&queue2);
  Queue *infinite_queue = NULL;
  infinite_queue = QUEUE_Create(0);
  infinite_queue->ops_->enqueue(infinite_queue, "I have infinite power", 22);
  infinite_queue->ops_->enqueue(infinite_queue, "and infinite space", 19);
  infinite_queue->ops_->enqueue(infinite_queue, "boy", 4);
  infinite_queue->ops_->enqueue(infinite_queue, "boy", 4);
  printf("\n \n|||infinite queue||| \n");
  infinite_queue->ops_->print(infinite_queue);
  printf("\n isEmpty: %d", infinite_queue->ops_->length_debug(infinite_queue));
  infinite_queue->ops_->resize(infinite_queue,2);
  infinite_queue->ops_->resize(infinite_queue,3);
  infinite_queue->ops_->enqueue(infinite_queue, "noo", 4);
  printf("\n %s", data);
  infinite_queue->ops_->destroy(&infinite_queue);
}