// main.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//Test battery for adt_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_stack.h"

int main()
{
  Stack *stack = NULL;
  stack = STACK_Create(5);
  char data[1024];
  
  if(NULL == stack){
    printf("\n create returned a null stack");
    return 1;
  }
  printf("\ncapacity: %d", stack->ops_->capacity(stack));
  printf("\nlength: %d", stack->ops_->length(stack));
  printf("\n isEmpty: %d", stack->ops_->isEmpty(stack));
  printf("\n isFull: %d", stack->ops_->isFull(stack));

  stack->ops_->push(stack, "Let's store strings", 20);
  stack->ops_->push(stack, "go", 3);
  stack->ops_->push(stack, "You are too slow",17); //out of range
  stack->ops_->push(stack, "You are too slow",17); 

  memset(data, 0, sizeof(data));
  memcpy(data, stack->ops_->first(stack), 9);
  printf("\n %s", data);

  printf("\ncapacity: %d", stack->ops_->capacity(stack));
  printf("\nlength: %d", stack->ops_->length(stack));
  printf("\n isEmpty: %d", stack->ops_->isEmpty(stack));
  printf("\n isFull: %d \n", stack->ops_->isFull(stack));

  stack->ops_->print(stack);
  stack->ops_->resize(stack, 7);
  stack->ops_->push(stack, "Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  stack->ops_->print(stack); 
  stack->ops_->push(stack, " inserting at 3", 16);
  printf("\n \n||||Third print:||||\n");
  stack->ops_->print(stack); 
  printf("\ncapacity: %d", stack->ops_->capacity(stack));
  printf("\nlength: %d", stack->ops_->length(stack));
  printf("\n isEmpty: %d", stack->ops_->isEmpty(stack));
  printf("\n isFull: %d \n", stack->ops_->isFull(stack));

  Stack *stack2 = NULL;
  stack2 = STACK_Create(2);

  Stack *stack3 = NULL;
  stack3 = STACK_Create(3);

  stack2->ops_->push(stack2, "Let's concatenate", 18);
  stack2->ops_->push(stack2, "now", 4);

  stack3->ops_->push(stack3, "Concatenate with me", 20);
  stack3->ops_->push(stack3, "come on!", 9);


  stack2->ops_->concat(stack2, stack3);
  stack3->ops_->destroy(&stack3);
  printf("\n \n|||| Fourth print: |||| \n");
  stack2->ops_->print(stack2); 
  printf("\ncapacity: %d", stack2->ops_->capacity(stack2));
  printf("\nlength: %d", stack2->ops_->length(stack2));
  printf("\n isEmpty: %d", stack2->ops_->isEmpty(stack2));
  printf("\n isFull: %d", stack2->ops_->isFull(stack2));

  memset(data, 0, sizeof(data));
  memcpy(data, stack2->ops_->pop(stack2), 18);
  printf("\n %s", data);
  stack2->ops_->pop(stack2);
  printf("\n \n|||stack2 after extract||| \n");
  stack2->ops_->print(stack2);
  stack2->ops_->push(stack2, "I see you lost something", 25);
  printf("\n \n|||stack2||| \n");
  stack2->ops_->print(stack2);

  stack2->ops_->push(stack2, "go", 3);
  stack2->ops_->push(stack2, "again", 6);
  stack2->ops_->pop(stack2);
  stack2->ops_->pop(stack2);
  printf("\n \n|||stack2 ready to resize||| \n");
  stack2->ops_->print(stack2);
  stack2->ops_->resize(stack2, 3);
  printf("\n \n|||stack2 after resize||| \n");
  stack2->ops_->print(stack2);
  stack2->ops_->resize(stack2, 1);
  printf("\n \n|||stack2 after second resize||| \n");
  stack2->ops_->print(stack2);


  memset(data, 0, sizeof(data));
  memcpy(data, stack->ops_->pop(stack), 20);
  printf("\n %s \n", data);
  printf("\n \n|||stack before extract||| \n");
  stack->ops_->print(stack);
  stack->ops_->pop(stack);
  printf("\n \n|||stack after extract||| \n");
  stack->ops_->print(stack);

  stack->ops_->reset(stack);
  printf("\n \n|||stack after reset||| \n");
  stack->ops_->print(stack);
  stack->ops_->push(stack, "Let's store strings", 20);
  printf("\n \n|||stack after insert||| \n");
  stack->ops_->print(stack);
  stack->ops_->destroy(&stack);
  stack2->ops_->destroy(&stack2);
}