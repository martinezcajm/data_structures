// main.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//Test battery for memory_node
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "memory_node.h"
#include "adt_list.h"
#include "adt_vector.h"
#include "adt_queue.h"
#include "adt_double_linked_list.h"
#include "adt_Stack.h"

int test_memory_node()
{
  MemoryNode *node = new MemoryNode();
  MemoryNode *node2 = new MemoryNode();
  if (nullptr == node) {
    printf("\n create returned a null node");
    return 1;
  }
  if (nullptr == node2) {
    printf("\n create returned a null node");
    return 1;
  }
  node->free_mn();
  //delete(node);
  //node->print();

  node = new MemoryNode();

  node->memCopy("hellos", 6);
  node->print();
  node->memSet('c');
  node->print();
  char *name = static_cast<char*>(malloc(sizeof(char) * 5));
  if (nullptr == name) {
    return 1;
  }
  memcpy(name, "Pepe", 5);
  node2->setData(name, 5);
  node2->print();

  MemoryNode *node3 = new MemoryNode();
  node3->memCopy("hello ", 6);
  node3->memConcat(node2->data(), node2->size());
  node3->print();

  node2->memMask('e');
  node2->print();

  node2->free_mn();

  char *test = static_cast<char*>(malloc(sizeof(char) * 65535));
  if (nullptr == test) {
    return 1;
  }
  node->memConcat(test, -1);
  node->memCopy("zero", 0);

  char *big_data = static_cast<char*>(malloc(sizeof(char) * 65535));
  if (nullptr == big_data) {
    return 1;
  }
  node->memCopy(big_data, 65535);
  node->print();
  node->reset();
  node->print();
  node->free_mn();
  node3->free_mn();
  return 0;
}

int test_vector()
{
  Vector *vector = new Vector(5);
  char data[1024];

  if (nullptr == vector) {
    printf("\n create returned a null vector");
    return 1;
  }
  printf("\ncapacity: %d", vector->capacity());
  printf("\nlength: %d", vector->length());
  printf("\n isEmpty: %d", vector->isEmpty());
  printf("\n isFull: %d", vector->isFull());

  vector->insertFirst("Let's store strings", 20);
  vector->insertLast("go", 3);
  vector->insertAt("You are too slow", 4, 17); //out of range
  vector->insertAt("You are too slow", 17, 0); 
  vector->insertFirst("good boy", 9);
  vector->insertLast(" my boy", 8);
  vector->insertLast(" my boy", 8); //full

  memset(data, 0, sizeof(data));
  memcpy(data, vector->head(), 9);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, vector->last(), 8);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, vector->at(3), 3);
  printf("\n %s", data);

  printf("\ncapacity: %d", vector->capacity());
  printf("\nlength: %d", vector->length());
  printf("\n isEmpty: %d", vector->isEmpty());
  printf("\n isFull: %d \n", vector->isFull());

  vector->print();
  vector->resize(7);
  vector->insertFirst("Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  vector->print();
  vector->insertAt(" inserting at 3", 16, 3);
  printf("\n \n||||Third print:||||\n");
  vector->print();
  printf("\ncapacity: %d", vector->capacity());
  printf("\nlength: %d", vector->length());
  printf("\n isEmpty: %d", vector->isEmpty());
  printf("\n isFull: %d \n", vector->isFull());

  Vector *vector2 = new Vector(2);

  Vector *vector3 = new Vector(3);

  vector2->insertFirst("Let's concatenate", 18);
  vector2->insertLast("now", 4);

  vector3->insertFirst("Concatenate with me", 20);
  vector3->insertLast("come on!", 9);


  vector2->concat(*vector3);
  delete(vector3);
  printf("\n \n|||| Fourth print: |||| \n");
  vector2->print();
  printf("\ncapacity: %d", vector2->capacity());
  printf("\nlength: %d", vector2->length());
  printf("\n isEmpty: %d", vector2->isEmpty());
  printf("\n isFull: %d", vector2->isFull());

  memset(data, 0, sizeof(data));
  memcpy(data, vector2->extractFirst(), 18);
  printf("\n %s", data);
  vector2->extractLast();
  printf("\n \n|||vector2 after extract||| \n");
  vector2->print();
  vector2->insertFirst("I see you lost something", 25);
  printf("\n \n|||vector2||| \n");
  vector2->print();

  vector2->insertLast("go", 3);
  vector2->insertLast("again", 6);
  vector2->extractFirst();
  vector2->extractFirst();
  printf("\n \n|||vector2 ready to resize||| \n");
  vector2->print();
  vector2->resize(3);
  printf("\n \n|||vector2 after resize||| \n");
  vector2->print();
  vector2->resize(1);
  printf("\n \n|||vector2 after second resize||| \n");
  vector2->print();


  memset(data, 0, sizeof(data));
  memcpy(data, vector->extractAt(4), 20);
  printf("\n %s \n", data);
  vector->extractAt(6);
  printf("\n \n|||vector after extract||| \n");
  vector->print();

  vector->reset();
  printf("\n \n|||vector after reset||| \n");
  vector->print();
  vector->insertFirst("Let's store strings", 20);
  printf("\n \n|||vector after insert||| \n");
  vector->print();

  Vector *vector4 = new Vector(*vector2);
  vector4->extractLast();

  delete(vector);
  delete(vector2);
  return 0;
}

int test_list()
{
  List *list = new List(5);
  char data[1024];

  if (nullptr == list) {
    printf("\n create returned a null list");
    return 1;
  }
  printf("\ncapacity: %d", list->capacity());
  printf("\nlength: %d", list->length());
  printf("\n isEmpty: %d", list->isEmpty());
  printf("\n isFull: %d", list->isFull());

  list->insertFirst("Let's store strings", 20);
  list->insertLast("go", 3);
  list->insertAt("You are too slow", 4, 17); //out of range
  list->insertAt("You are too slow", 0, 17);
  list->insertFirst("good boy", 9);
  list->insertLast(" my boy", 8);
  list->insertLast(" my boy", 8);

  memset(data, 0, sizeof(data));
  memcpy(data, list->head(), 9);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, list->last(), 8);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, list->at(3), 3);
  printf("\n %s", data);

  printf("\ncapacity: %d", list->capacity());
  printf("\nlength: %d", list->length());
  printf("\n isEmpty: %d", list->isEmpty());
  printf("\n isFull: %d \n", list->isFull());

  list->print();
  list->resize(7);
  list->insertFirst("Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  list->print();
  list->insertAt(" inserting at 3", 3, 16);
  printf("\n \n||||Third print:||||\n");
  list->print();
  printf("\ncapacity: %d", list->capacity());
  printf("\nlength: %d", list->length());
  printf("\n isEmpty: %d", list->isEmpty());
  printf("\n isFull: %d \n", list->isFull());

  List *list2 = new List(2);

  List *list3 = new List(3);

  list2->insertFirst("Let's concatenate", 18);
  list2->insertLast("now", 4);

  list3->insertFirst("Concatenate with me", 20);
  list3->insertLast("come on!", 9);


  list2->concat(list3);
  delete(list3);
  printf("\n \n|||| Fourth print: |||| \n");
  list2->print();
  printf("\ncapacity: %d", list2->capacity());
  printf("\nlength: %d", list2->length());
  printf("\n isEmpty: %d", list2->isEmpty());
  printf("\n isFull: %d", list2->isFull());

  memset(data, 0, sizeof(data));
  memcpy(data, list2->extractFirst(), 18);
  printf("\n %s", data);
  list2->extractLast();
  printf("\n \n|||list2 after extract||| \n");
  list2->print();
  list2->insertFirst("I see you lost something", 25);
  printf("\n \n|||list2||| \n");
  list2->print();

  list2->insertLast("go", 3);
  list2->insertLast("again", 6);
  list2->extractFirst();
  list2->extractFirst();
  printf("\n \n|||list2 ready to resize||| \n");
  list2->print();
  list2->resize(3);
  printf("\n \n|||list2 after resize||| \n");
  list2->print();
  list2->resize(1);
  printf("\n \n|||list2 after second resize||| \n");
  list2->print();


  memset(data, 0, sizeof(data));
  memcpy(data, list->extractAt(4), 20);
  printf("\n %s \n", data);
  printf("\n \n|||list before extract||| \n");
  list->print();
  list->extractAt(3);
  printf("\n \n|||list after extract||| \n");
  list->print();

  list->reset();
  printf("\n \n|||list after reset||| \n");
  list->print();
  list->insertFirst("Let's store strings", 20);
  printf("\n \n|||list after insert||| \n");
  list->print();
  delete(list);
  delete(list2);
  List *infinite_list = new List(0);
  infinite_list->insertLast("I have infinite power", 22);
  infinite_list->insertLast("and infinite space", 19);
  infinite_list->insertAt("boy", 3, 4);
  infinite_list->insertAt("boy", 1, 4);
  printf("\n \n|||infinite list||| \n");
  infinite_list->print();
  printf("\n isEmpty: %d", infinite_list->length_debug());
  infinite_list->resize(2);
  infinite_list->resize(3);
  infinite_list->insertLast("noo", 4);
  printf("\n %s", data);
  return 0;
}

int test_dllist()
{
  DLList *list = new DLList(5);
  char data[1024];

  if (nullptr == list) {
    printf("\n create returned a null list");
    return 1;
  }
  printf("\ncapacity: %d", list->capacity());
  printf("\nlength: %d", list->length());
  printf("\n isEmpty: %d", list->isEmpty());
  printf("\n isFull: %d", list->isFull());

  list->insertFirst("Let's store strings", 20);
  list->insertLast("go", 3);
  list->insertAt("You are too slow", 4, 17); //out of range
  list->insertAt("You are too slow", 0, 17);
  list->insertFirst("good boy", 9);
  list->insertLast(" my boy", 8);
  list->insertLast(" my boy", 8);

  memset(data, 0, sizeof(data));
  memcpy(data, list->head(), 9);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, list->last(), 8);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, list->at(3), 3);
  printf("\n %s", data);

  printf("\ncapacity: %d", list->capacity());
  printf("\nlength: %d", list->length());
  printf("\n isEmpty: %d", list->isEmpty());
  printf("\n isFull: %d \n", list->isFull());

  list->print();
  list->resize(7);
  list->insertFirst("Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  list->print();
  list->insertAt(" inserting at 3", 3, 16);
  printf("\n \n||||Third print:||||\n");
  list->print();
  printf("\ncapacity: %d", list->capacity());
  printf("\nlength: %d", list->length());
  printf("\n isEmpty: %d", list->isEmpty());
  printf("\n isFull: %d \n", list->isFull());

  DLList *list2 = new DLList(2);

  DLList *list3 = new DLList(3);

  list2->insertFirst("Let's concatenate", 18);
  list2->insertLast("now", 4);

  list3->insertFirst("Concatenate with me", 20);
  list3->insertLast("come on!", 9);


  list2->concat(list3);
  delete(list3);
  printf("\n \n|||| Fourth print: |||| \n");
  list2->print();
  printf("\ncapacity: %d", list2->capacity());
  printf("\nlength: %d", list2->length());
  printf("\n isEmpty: %d", list2->isEmpty());
  printf("\n isFull: %d", list2->isFull());

  memset(data, 0, sizeof(data));
  memcpy(data, list2->extractFirst(), 18);
  printf("\n %s", data);
  list2->extractLast();
  printf("\n \n|||list2 after extract||| \n");
  list2->print();
  list2->insertFirst("I see you lost something", 25);
  printf("\n \n|||list2||| \n");
  list2->print();

  list2->insertLast("go", 3);
  list2->insertLast("again", 6);
  list2->extractFirst();
  list2->extractFirst();
  printf("\n \n|||list2 ready to resize||| \n");
  list2->print();
  list2->resize(3);
  printf("\n \n|||list2 after resize||| \n");
  list2->print();
  list2->resize(1);
  printf("\n \n|||list2 after second resize||| \n");
  list2->print();


  memset(data, 0, sizeof(data));
  memcpy(data, list->extractAt(4), 20);
  printf("\n %s \n", data);
  printf("\n \n|||list before extract||| \n");
  list->print();
  list->extractAt(3);
  printf("\n \n|||list after extract||| \n");
  list->print();

  list->reset();
  printf("\n \n|||list after reset||| \n");
  list->print();
  list->insertFirst("Let's store strings", 20);
  printf("\n \n|||list after insert||| \n");
  list->print();
  delete(list);
  delete(list2);
  DLList *infinite_list = new DLList(0);
  infinite_list->insertLast("I have infinite power", 22);
  infinite_list->insertLast("and infinite space", 19);
  infinite_list->insertAt("boy", 3, 4);
  infinite_list->insertAt("boy", 1, 4);
  printf("\n \n|||infinite list||| \n");
  infinite_list->print();
  printf("\n isEmpty: %d", infinite_list->length_debug());
  infinite_list->resize(2);
  infinite_list->resize(3);
  infinite_list->insertLast("noo", 4);
  printf("\n %s", data);
  return 0;
}

int test_queue()
{
  Queue *queue = new Queue(5);
  char data[1024];

  if (nullptr == queue) {
    printf("\n create returned a null queue");
    return 1;
  }
  printf("\ncapacity: %d", queue->capacity());
  printf("\nlength: %d", queue->length());
  printf("\n isEmpty: %d", queue->isEmpty());
  printf("\n isFull: %d", queue->isFull());

  queue->enqueue("Let's store strings", 20);
  queue->enqueue("go", 3);
  queue->enqueue("You are too slow", 17); //out of range
  queue->enqueue("You are too slow", 17);

  memset(data, 0, sizeof(data));
  memcpy(data, queue->first(), 9);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, queue->last(), 8);
  printf("\n %s", data);

  printf("\ncapacity: %d", queue->capacity());
  printf("\nlength: %d", queue->length());
  printf("\n isEmpty: %d", queue->isEmpty());
  printf("\n isFull: %d \n", queue->isFull());

  queue->print();
  queue->resize(7);
  queue->enqueue("Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  queue->print();
  queue->enqueue(" inserting at 3", 16);
  printf("\n \n||||Third print:||||\n");
  queue->print();
  printf("\ncapacity: %d", queue->capacity());
  printf("\nlength: %d", queue->length());
  printf("\n isEmpty: %d", queue->isEmpty());
  printf("\n isFull: %d \n", queue->isFull());

  Queue *queue2 = new Queue(2);
  Queue *queue3 = new Queue(3);

  queue2->enqueue("Let's concatenate", 18);
  queue2->enqueue("now", 4);

  queue3->enqueue("Concatenate with me", 20);
  queue3->enqueue("come on!", 9);


  queue2->concat(queue3);
  delete(queue3);
  printf("\n \n|||| Fourth print: |||| \n");
  queue2->print();
  printf("\ncapacity: %d", queue2->capacity());
  printf("\nlength: %d", queue2->length());
  printf("\n isEmpty: %d", queue2->isEmpty());
  printf("\n isFull: %d", queue2->isFull());

  memset(data, 0, sizeof(data));
  memcpy(data, queue2->dequeue(), 18);
  printf("\n %s", data);
  queue2->dequeue();
  printf("\n \n|||queue2 after extract||| \n");
  queue2->print();
  queue2->enqueue("I see you lost something", 25);
  printf("\n \n|||queue2||| \n");
  queue2->print();

  queue2->enqueue("go", 3);
  queue2->enqueue("again", 6);
  queue2->dequeue();
  queue2->dequeue();
  printf("\n \n|||queue2 ready to resize||| \n");
  queue2->print();
  queue2->resize(3);
  printf("\n \n|||queue2 after resize||| \n");
  queue2->print();
  queue2->resize(1);
  printf("\n \n|||queue2 after second resize||| \n");
  queue2->print();


  memset(data, 0, sizeof(data));
  memcpy(data, queue->dequeue(), 20);
  printf("\n %s \n", data);
  printf("\n \n|||queue before extract||| \n");
  queue->print();
  queue->dequeue();
  printf("\n \n|||queue after extract||| \n");
  queue->print();

  queue->reset();
  printf("\n \n|||queue after reset||| \n");
  queue->print();
  queue->enqueue("Let's store strings", 20);
  printf("\n \n|||queue after insert||| \n");
  queue->print();
  delete(queue);
  delete(queue2);
  Queue *infinite_queue = new Queue(0);
  infinite_queue->enqueue("I have infinite power", 22);
  infinite_queue->enqueue("and infinite space", 19);
  infinite_queue->enqueue("boy", 4);
  infinite_queue->enqueue("boy", 4);
  printf("\n \n|||infinite queue||| \n");
  infinite_queue->print();
  printf("\n isEmpty: %d", infinite_queue->length_debug());
  infinite_queue->resize(2);
  infinite_queue->resize(3);
  infinite_queue->enqueue("noo", 4);
  printf("\n %s", data);
  return 0;
}

int test_stack()
{
  Stack *stack = new Stack(5);
  char data[1024];

  if (nullptr == stack) {
    printf("\n create returned a null stack");
    return 1;
  }
  printf("\ncapacity: %d", stack->capacity());
  printf("\nlength: %d", stack->length());
  printf("\n isEmpty: %d", stack->isEmpty());
  printf("\n isFull: %d", stack->isFull());

  stack->push("Let's store strings", 20);
  stack->push("go", 3);
  stack->push("You are too slow", 17);
  stack->push("You are too slow", 17);

  memset(data, 0, sizeof(data));
  memcpy(data, stack->first(), 9);
  printf("\n %s", data);

  printf("\ncapacity: %d", stack->capacity());
  printf("\nlength: %d", stack->length());
  printf("\n isEmpty: %d", stack->isEmpty());
  printf("\n isFull: %d \n", stack->isFull());

  stack->print();
  stack->resize(7);
  stack->push("Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  stack->print();
  stack->push(" inserting at 3", 16);
  printf("\n \n||||Third print:||||\n");
  stack->print();
  printf("\ncapacity: %d", stack->capacity());
  printf("\nlength: %d", stack->length());
  printf("\n isEmpty: %d", stack->isEmpty());
  printf("\n isFull: %d \n", stack->isFull());

  Stack *stack2 = new Stack(2);
  Stack *stack3 = new Stack(3);

  stack2->push("Let's concatenate", 18);
  stack2->push("now", 4);

  stack3->push("Concatenate with me", 20);
  stack3->push("come on!", 9);


  stack2->concat(*stack3);
  delete(stack3);
  printf("\n \n|||| Fourth print: |||| \n");
  stack2->print();
  printf("\ncapacity: %d", stack2->capacity());
  printf("\nlength: %d", stack2->length());
  printf("\n isEmpty: %d", stack2->isEmpty());
  printf("\n isFull: %d", stack2->isFull());

  memset(data, 0, sizeof(data));
  memcpy(data, stack2->pop(), 18);
  printf("\n %s", data);
  stack2->pop();
  printf("\n \n|||stack2 after extract||| \n");
  stack2->print();
  stack2->push("I see you lost something", 25);
  printf("\n \n|||stack2||| \n");
  stack2->print();

  stack2->push("go", 3);
  stack2->push("again", 6);
  stack2->pop();
  stack2->pop();
  printf("\n \n|||stack2 ready to resize||| \n");
  stack2->print();
  stack2->resize(3);
  printf("\n \n|||stack2 after resize||| \n");
  stack2->print();
  stack2->resize(1);
  printf("\n \n|||stack2 after second resize||| \n");
  stack2->print();


  memset(data, 0, sizeof(data));
  memcpy(data, stack->pop(), 20);
  printf("\n %s \n", data);
  printf("\n \n|||stack before extract||| \n");
  stack->print();
  stack->pop();
  printf("\n \n|||stack after extract||| \n");
  stack->print();

  stack->reset();
  printf("\n \n|||stack after reset||| \n");
  stack->print();
  stack->push("Let's store strings", 20);
  printf("\n \n|||stack after insert||| \n");
  stack->print();
  delete(stack);
  delete(stack2);
  return 0;
}

int main()
{
  //test_memory_node();
  //test_vector();
  //test_list();
  //test_dllist();
  //test_queue();
  test_stack();
  return 0;
}

