// adt_stack.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_stack.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_stack.h"
#include "common_def.h"

static s16 STACK_init(Stack *stack, u16 capacity);
static s16 STACK_destroy(Stack **stack);
static s16 STACK_reset(Stack *stack);
static s16 STACK_resize(Stack *stack, u16 new_size);
static u16 STACK_capacity(Stack *stack);
static u16 STACK_length(Stack *stack);
static bool STACK_isEmpty(Stack *stack);
static bool STACK_isFull(Stack *stack);
static void* STACK_first(Stack *stack);
static s16 STACK_push(Stack *stack, void *data, u16 data_size);
static void* STACK_pop(Stack *stack);
static s16 STACK_concat(Stack *stack, Stack *src);
static u16 STACK_traverse(Stack *stack, void(*callback) (MemoryNode *));
static void STACK_print(Stack *stack);

struct adt_stack_ops_s adt_stack_ops =
{
  //.init = STACK_init,
  .destroy = STACK_destroy,
  .reset = STACK_reset,
  .resize = STACK_resize,
  .capacity = STACK_capacity,
  .length = STACK_length,
  .isEmpty = STACK_isEmpty,
  .isFull = STACK_isFull,
  .first = STACK_first,
  .push = STACK_push,
  .pop = STACK_pop,
  .concat = STACK_concat,
  .traverse = STACK_traverse,
  .print = STACK_print
};

Stack* STACK_Create(u16 capacity)
{
  Stack *stack = malloc(sizeof(Stack));
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  s16 status = STACK_init(stack, capacity);
  if(kErrorCode_Ok != status){
    free(stack);
    stack = NULL;
  }
  return stack;
}

s16 STACK_init(Stack *stack, u16 capacity)
{
  //This function will only be called from Create so we don't need to check
  //the pointer.
  stack->vector_ = VECTOR_Create(capacity);
  stack->ops_ = &adt_stack_ops;
  if( NULL == stack->vector_){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  return kErrorCode_Ok;
}

s16 STACK_destroy(Stack **stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to stack is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  if(NULL == *stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Stack;
  }
  s16 status = (*stack)->vector_->ops_->destroy(&((*stack)->vector_));
  free(*stack);
  *stack = NULL;
  return status;
}

s16 STACK_reset(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Stack;
  }
  return stack->vector_->ops_->reset(stack->vector_);
}

s16 STACK_resize(Stack *stack, u16 new_size)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Stack;
  }
  s16 status = stack->vector_->ops_->resize(stack->vector_, new_size);
  return status;
}

u16 STACK_capacity(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return stack->vector_->ops_->capacity(stack->vector_);  
}

u16 STACK_length(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return stack->vector_->ops_->length(stack->vector_);  
}

bool STACK_isEmpty(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return false;
  }  
  return stack->vector_->ops_->isEmpty(stack->vector_);  
}

bool STACK_isFull(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return true;
  }
  return stack->vector_->ops_->isFull(stack->vector_);
}

void* STACK_first(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(STACK_isEmpty(stack)){
    return NULL;
  }
  return stack->vector_->ops_->last(stack->vector_);
}

s16 STACK_push(Stack *stack, void *data, u16 data_size)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Stack;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(STACK_isFull(stack)){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is full\n", __FUNCTION__);
#endif
    return kErrorCode_Stack_Is_Full;    
  }
  return stack->vector_->ops_->insertLast(stack->vector_, data, data_size);
}

void* STACK_pop(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(STACK_isEmpty(stack)){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is empty\n", __FUNCTION__);
#endif
    return NULL;
  }
  return stack->vector_->ops_->extractLast(stack->vector_);
}

s16 STACK_concat(Stack *stack, Stack *src)
{
  if(NULL == stack){
#ifdef VERBOSE_ 
      printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
      return kErrorCode_Null_Stack;
  }
  if(NULL == src){
#ifdef VERBOSE_ 
    printf("Error: [%s] The source stack is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }

  return stack->vector_->ops_->concat(stack->vector_, src->vector_);
}

u16 STACK_traverse(Stack *stack, void(*callback) (MemoryNode *))
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return stack->vector_->ops_->traverse(stack->vector_, callback);
}

void STACK_print(Stack *stack)
{
  if(NULL == stack){
#ifdef VERBOSE_
    printf("Error: [%s] The stack is null\n", __FUNCTION__);
#endif
    printf("NULL");
    return;
  }
  stack->vector_->ops_->print(stack->vector_);
}