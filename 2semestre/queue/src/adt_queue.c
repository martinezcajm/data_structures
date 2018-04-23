// adt_queue.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_queue.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_queue.h"
#include "common_def.h"

static s16 QUEUE_init(Queue *queue, u16 capacity);
static s16 QUEUE_destroy(Queue **queue);
static s16 QUEUE_reset(Queue *queue);
static s16 QUEUE_resize(Queue *queue, u16 new_size);
static u16 QUEUE_capacity(Queue *queue);
static u16 QUEUE_length(Queue *queue);
static bool QUEUE_length_debug(Queue *queue);
static bool QUEUE_isEmpty(Queue *queue);
static bool QUEUE_isFull(Queue *queue);
static void* QUEUE_first(Queue *queue);
static void* QUEUE_last(Queue *queue);
static s16 QUEUE_enqueue(Queue *queue, void *data, u16 data_size);
static void* QUEUE_dequeue(Queue *queue);
static s16 QUEUE_concat(Queue *queue, Queue *src);
static u16 QUEUE_traverse(Queue *queue, void(*callback) (MemoryNode *));
static void QUEUE_print(Queue *queue);

struct adt_queue_ops_s adt_queue_ops =
{
  //.init = QUEUE_init,
  .destroy = QUEUE_destroy,
  .reset = QUEUE_reset,
  .resize = QUEUE_resize,
  .capacity = QUEUE_capacity,
  .length = QUEUE_length,
  .length_debug = QUEUE_length_debug,
  .isEmpty = QUEUE_isEmpty,
  .isFull = QUEUE_isFull,
  .first = QUEUE_first,
  .last = QUEUE_last,
  .enqueue = QUEUE_enqueue,
  .dequeue = QUEUE_dequeue,
  .concat = QUEUE_concat,
  .traverse = QUEUE_traverse,
  .print = QUEUE_print
};

Queue* QUEUE_Create(u16 capacity)
{
  Queue *queue = malloc(sizeof(Queue));
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  s16 status = QUEUE_init(queue, capacity);
  if(kErrorCode_Ok != status){
    free(queue);
    queue = NULL;
  }
  return queue;
}

s16 QUEUE_init(Queue *queue, u16 capacity)
{
  //This function will only be called from Create so we don't need to check
  //the pointer.
  queue->list_ = LIST_Create(capacity);
  queue->ops_ = &adt_queue_ops;
  if( NULL == queue->list_){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  return kErrorCode_Ok;
  //return queue->list_->ops_->init(queue->list_, capacity);
}

s16 QUEUE_destroy(Queue **queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to queue is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  if(NULL == *queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Queue;
  }
  s16 status = (*queue)->list_->ops_->destroy(&((*queue)->list_));
  free(*queue);
  *queue = NULL;
  return s16;
}

s16 QUEUE_reset(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Queue;
  }
  return queue->list_->ops_->reset(queue->list_);
}

s16 QUEUE_resize(Queue *queue, u16 new_size)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Queue;
  }
  s16 status = queue->list_->ops_->resize(queue->list_, new_size);
  return status;
}

u16 QUEUE_capacity(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return queue->list_->ops_->capacity(queue->list_);  
}

u16 QUEUE_length(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return queue->list_->ops_->length(queue->list_);  
}

bool QUEUE_length_debug(Queue *queue){
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return false;
  }
  return queue->list_->ops_->length_debug(queue->list_);  
}

bool QUEUE_isEmpty(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return false;
  }  
  return queue->list_->ops_->isEmpty(queue->list_);  
}

bool QUEUE_isFull(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return true;
  }
  return queue->list_->ops_->isFull(queue->list_);
}

void* QUEUE_first(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(QUEUE_isEmpty(queue)){
    return NULL;
  }
  return queue->list_->ops_->head(queue->list_);
}

void* QUEUE_last(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(QUEUE_isEmpty(queue)){
    return NULL;
  }
  return queue->list_->ops_->last(queue->list_);
}

s16 QUEUE_enqueue(Queue *queue, void *data, u16 data_size)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Queue;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(QUEUE_isFull(queue)){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is full\n", __FUNCTION__);
#endif
    return kErrorCode_Queue_Is_Full;    
  }
  return queue->list_->ops_->insertLast(queue->list_, data, data_size);
}

void* QUEUE_dequeue(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(QUEUE_isEmpty(queue)){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is empty\n", __FUNCTION__);
#endif
    return NULL;
  }
  return queue->list_->ops_->extractFirst(queue->list_);
}

s16 QUEUE_concat(Queue *queue, Queue *src)
{
  if(NULL == queue){
#ifdef VERBOSE_ 
      printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
      return kErrorCode_Null_Queue;
  }
  if(NULL == src){
#ifdef VERBOSE_ 
    printf("Error: [%s] The source queue is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }

  return queue->list_->ops_->concat(queue->list_, src->list_);


  /*queue->last_->ops_->setNext(queue->last_, src->first_);
  queue->last_ = src->last_;
  if(0 == queue->capacity_ || 0 == src->capacity_){
    queue->capacity_ = 0;
  }else{
    queue->capacity_ = queue->capacity_ + src->capacity_;
  }
  queue->length_ = queue->length_ + src->length_;
  src->first_ = NULL;
  src->last_ = NULL;
  src->length_ = 0;
  return kErrorCode_Ok; */ 
}

u16 QUEUE_traverse(Queue *queue, void(*callback) (MemoryNode *))
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return queue->list_->ops_->traverse(queue->list_, callback);
}

void QUEUE_print(Queue *queue)
{
  if(NULL == queue){
#ifdef VERBOSE_
    printf("Error: [%s] The queue is null\n", __FUNCTION__);
#endif
    printf("NULL");
    return;
  }
  queue->list_->ops_->print(queue->list_);
}