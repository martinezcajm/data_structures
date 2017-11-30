// adt_vector.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_vector.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_vector.h"
#include "common_def.h"

static s16 VECTOR_init(Vector *vector);
static s16 VECTOR_destroy(Vector **vector);
static s16 VECTOR_reset(Vector *vector);
static u16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *));
//static u16 VECTOR_resize(Vector *vector, u16 new_size);
static u16 VECTOR_capacity(Vector *vector);
static u16 VECTOR_length(Vector *vector);
static bool VECTOR_isEmpty(Vector *vector);
static bool VECTOR_isFull(Vector *vector);
static void* VECTOR_head(Vector *vector);
static void* VECTOR_last(Vector *vector);
/*static void* VECTOR_at(Vector *vector, u16 position);
static s16 VECTOR_insertFirst(Vector *vector, void *data);
static s16 VECTOR_insertLast(Vector *vector, void *data);
static s16 VECTOR_insertAt(Vector *vector, void *data, u16 position);
static s16 VECTOR_extractFirst(Vector *vector, void *data);
static s16 VECTOR_extractLast(Vector *vector, void *data);
static s16 VECTOR_extractAt(Vector *vector, void *data, u16 position);
static s16 VECTOR_concat(Vector *vector, Vector *src);
static void VECTOR_print(Vector *vector);*/

struct adt_vector_ops_s adt_vector_ops =
{
  .destroy = VECTOR_destroy,
  .reset = VECTOR_reset,
  .traverse = VECTOR_traverse,
  .capacity = VECTOR_capacity,
  .length = VECTOR_length,
  .isEmpty = VECTOR_isEmpty,
  .isFull = VECTOR_isFull,
  .head = VECTOR_head,
  .last = VECTOR_last
};

Vector* VECTOR_Create(u16 capacity)
{
  Vector *vector = malloc(sizeof(Vector));
  MemoryNode *storage = malloc(sizeof(MemoryNode)*capacity);
  if(NULL == vector || NULL == storage){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  VECTOR_init(vector);
  //As init can only called from create it can't return other error code than
  //ok
  vector->storage_ = storage;
  return vector;
}

s16 VECTOR_init(Vector *vector)
{
  //This function will only by called from Create so we don't need to check
  //the pointer.
  vector->head_ = 0;
  vector->tail_ = 0;
  vector->capacity_ = 0;
  vector->storage_ = NULL;
  return kErrorCode_Ok;
}

s16 VECTOR_destroy(Vector **vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to vector is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  //We don't need to check if the pointer to vecotr is null as reset will do it
  s16 status = VECTOR_reset(*vector);
  //We check if all went well and free the vector in case it was
  if(kErrorCode_Ok == status){
    free(*vector);
    *vector = NULL;
  }
  return kErrorCode_Ok;
}

s16 VECTOR_reset(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Vector;
  }
  VECTOR_traverse(vector, vector->storage_->ops_->reset);
  free(vector->storage_);
  vector->storage_ = NULL;
  vector->head_ = 0;
  vector->tail_ = 0;
  vector->capacity_ = 0;
  return kErrorCode_Ok;
}

u16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *))
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return 0;
  }
  MemoryNode *aux;
  aux = vector->storage_;
  u16 i;
  for(i = 0; i< vector->capacity_; i++){
    callback(aux);
    ++aux;
  }
  return i;
}

/*u16 VECTOR_resize(Vector *vector, u16 new_size)
{
  
}*/

u16 VECTOR_capacity(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return vector->capacity_;  
}

u16 VECTOR_length(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return 0;
  }
  //return vector->head_ - vector->tail_;
  return vector->tail_;  
}

bool VECTOR_isEmpty(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return true;
  }  
  return 0 == vector->tail_;
}

bool VECTOR_isFull(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return true;
  }  
  return vector->tail_ == vector->capacity_;
}

void* VECTOR_head(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(VECTOR_isEmpty(vector)){
    return NULL;
  }
  MemoryNode *aux = vector->storage_ + vector->head_;
  return aux->ops_->data(aux);
  //return vector->storage_ + vector->head_;
}

void* VECTOR_last(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(VECTOR_isEmpty(vector)){
    return NULL;
  }
  MemoryNode *aux = vector->storage_ + (vector->head_ + vector->tail_ -1);
  return aux->ops_->data(aux);
  //return vector->storage_ + (vector->head_ + vector->tail_ -1);
}

void* VECTOR_at(Vector *vector, u16 position)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(VECTOR_isEmpty(vector)){
    return NULL;
  }
  if(position >= vector->capacity_){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return NULL;    
  }
  MemoryNode *aux = vector->storage_ + position;
  return aux->ops_->data(aux);
  //return vector->storage_ + position;
}

s16 VECTOR_insertFirst(Vector *vector, void *data)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Vector;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(VECTOR_isFull(vector)){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is full\n", __FUNCTION__);
#endif
    return kErrorCode_Vector_Is_Full;    
  }
  /*MemoryNode *node = MEMNODE_create();
  if(NULL == node){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;    
  }
  s16 status = node->ops_->setData(node, data, 5); //size?
  if(kErrorCode_Null_Memory_Node == status || 
     kWarningCode_Strange_Operation == status){
#ifdef VERBOSE_
    printf("InternalError: [%s] Problem with memory node\n", __FUNCTION__);
#endif
    return status;
  }*/
  if(vector->head_ > 0){ //we don't need to move the content
    --vector->head_;
  }else{ //the head is at the first position so we need to move the elements
    memmove(vector->storage_ + 1, vector->storage_,
            sizeof(MemoryNode)*vector->tail_);
  }
  ++vector->tail_;
  MemoryNode *aux = (MemoryNode*)data;
  *(vector->storage_ + vector->head_) = *aux;
  //*(vector->storage_ + vector->head_) = *node;
  return kErrorCode_Ok;
}

s16 VECTOR_insertLast(Vector *vector, void *data)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Vector;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(VECTOR_isFull(vector)){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is full\n", __FUNCTION__);
#endif
    return kErrorCode_Vector_Is_Full;    
  }
  //we need to move the content
  if(vector->head_ + vector->tail_ == vector->capacity_){ 
    memmove(vector->storage_ + vector->head_ -1, 
            vector->storage_ + vector->head_,
            sizeof(MemoryNode)*vector->tail_);
    --vector->head_;
  }
  ++vector->tail_;
  MemoryNode *aux = (MemoryNode*)data;
  *(vector->storage_ + vector->head_ + vector->tail_) = *aux;
  return kErrorCode_Ok;  
}

/*s16 VECTOR_insertAt(Vector *vector, void *data, u16 position)
{
  
}

s16 VECTOR_extractFirst(Vector *vector, void *data)
{
  
}

s16 VECTOR_extractLast(Vector *vector, void *data)
{
  
}

s16 VECTOR_extractAt(Vector *vector, void *data, u16 position)
{
  
}

s16 VECTOR_concat(Vector *vector, Vector *src)
{
  
}

u16 VECTOR_taverse(Vector *vector, void(*callback) (MemoryNode *))
{
  
}

void VECTOR_print(Vector *vector)
{
  
}*/