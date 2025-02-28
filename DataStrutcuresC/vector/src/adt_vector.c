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

static s16 VECTOR_init(Vector *vector, u16 capacity);
static s16 VECTOR_destroy(Vector **vector);
static s16 VECTOR_reset(Vector *vector);
static s16 VECTOR_resize(Vector *vector, u16 new_size);
static u16 VECTOR_capacity(Vector *vector);
static u16 VECTOR_length(Vector *vector);
static bool VECTOR_isEmpty(Vector *vector);
static bool VECTOR_isFull(Vector *vector);
static void* VECTOR_head(Vector *vector);
static void* VECTOR_last(Vector *vector);
static void* VECTOR_at(Vector *vector, u16 position);
static s16 VECTOR_insertFirst(Vector *vector, void *data, u16 data_size);
static s16 VECTOR_insertLast(Vector *vector, void *data, u16 data_size);
static s16 VECTOR_insertAt(Vector *vector, void *data, u16 position,
                           u16 data_size);
static void* VECTOR_extractFirst(Vector *vector);
static void* VECTOR_extractLast(Vector *vector);
static void* VECTOR_extractAt(Vector *vector, u16 position);
static s16 VECTOR_concat(Vector *vector, Vector *src);
static u16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *));
static void VECTOR_print(Vector *vector);

struct adt_vector_ops_s adt_vector_ops =
{
  .destroy = VECTOR_destroy,
  .reset = VECTOR_reset,
  .resize = VECTOR_resize,
  .capacity = VECTOR_capacity,
  .length = VECTOR_length,
  .isEmpty = VECTOR_isEmpty,
  .isFull = VECTOR_isFull,
  .head = VECTOR_head,
  .last = VECTOR_last,
  .at = VECTOR_at,
  .insertFirst = VECTOR_insertFirst,
  .insertLast = VECTOR_insertLast,
  .insertAt = VECTOR_insertAt,
  .extractFirst = VECTOR_extractFirst,
  .extractLast = VECTOR_extractLast,
  .extractAt = VECTOR_extractAt,
  .concat = VECTOR_concat,
  .traverse = VECTOR_traverse,
  .print = VECTOR_print
};

Vector* VECTOR_Create(u16 capacity)
{
  Vector *vector = malloc(sizeof(Vector));
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  MemoryNode *storage = malloc(sizeof(MemoryNode)*capacity);
  if(NULL == storage){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    free(vector);
    return NULL;
  }
  vector->storage_ = storage;
  VECTOR_init(vector, capacity);
  //As init can only be called from create it can't return other error code 
  //than ok  
  return vector;
}

s16 VECTOR_init(Vector *vector,u16 capacity)
{
  //This function will only by called from Create so we don't need to check
  //the pointer.
  vector->head_ = 0;
  vector->tail_ = 0;
  vector->capacity_ = capacity;
  //We initialize the nodes of our storage
  VECTOR_traverse(vector, MEMNODE_init);
  vector->ops_ = &adt_vector_ops;
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
    free((*vector)->storage_);
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
  vector->head_ = 0;
  vector->tail_ = 0;
  return kErrorCode_Ok;
}

s16 VECTOR_resize(Vector *vector, u16 new_size)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Vector;
  }
  u16 old_capacity = vector->capacity_;
  //In case the new size is the same as the actual capacity we have finished
  if(new_size == old_capacity){
    return kErrorCode_Ok;
  }
  MemoryNode *new_storage = malloc(sizeof(MemoryNode)*new_size);
  if(NULL == new_storage){
  #ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }

  MemoryNode *old_storage = vector->storage_;
  
  vector->storage_ = new_storage;
  vector->capacity_ = new_size;

  //We initialize the memnodes of the new vector
  VECTOR_traverse(vector, MEMNODE_init);

  if(new_size > old_capacity){
    memcpy(new_storage,old_storage,sizeof(MemoryNode)*old_capacity);
  }else if(new_size < old_capacity){
    if(VECTOR_length(vector) >= new_size){
      memcpy(new_storage, old_storage + vector->head_, 
             sizeof(MemoryNode)*new_size);
      if(VECTOR_length(vector)>new_size){ //we need to free the remaining data
        for(u16 i = vector->head_ + new_size; i < old_capacity; ++i){
          old_storage->ops_->reset(old_storage + i);
        }
      }
      vector->head_ = 0;
      vector->tail_ = new_size;
    }else{
      memcpy(new_storage, old_storage + vector->head_, 
             sizeof(MemoryNode)*VECTOR_length(vector));
      vector->tail_ = VECTOR_length(vector);
      vector->head_ = 0;
    }
  }
  free(old_storage);
  return kErrorCode_Ok;
}

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
  return vector->tail_ - vector->head_;
}

bool VECTOR_isEmpty(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return true;
  }  
  return 0 == VECTOR_length(vector);
}

bool VECTOR_isFull(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return true;
  }  
  return VECTOR_length(vector) == vector->capacity_;
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
  MemoryNode *aux = vector->storage_ + (vector->tail_ -1);
  return aux->ops_->data(aux);
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
  if(position >= VECTOR_length(vector)){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return NULL;    
  }
  MemoryNode *aux = vector->storage_ + (vector->head_ + position);
  return aux->ops_->data(aux);
  //return vector->storage_ + position;
}

s16 VECTOR_insertFirst(Vector *vector, void *data, u16 data_size)
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
  if(VECTOR_isEmpty(vector)){//is empty so we just need to update the tail
    ++vector->tail_;
  }
  else if(vector->head_ > 0){ //we don't need to move the content
    --vector->head_;
  }else{ //the head is at the first position so we need to move the elements
    memmove(vector->storage_ + 1, vector->storage_,
            sizeof(MemoryNode)*VECTOR_length(vector));
    //As the elements were moved one position to the right the tail needs to 
    //be updated
    ++vector->tail_;
  }
  MemoryNode *aux = vector->storage_ + vector->head_;
  s16 status = aux->ops_->init(aux);
  //status = aux->ops_->setData(aux, data, data_size);
  status = aux->ops_->memCopy(aux, data, data_size);
  return status;
}

s16 VECTOR_insertLast(Vector *vector, void *data, u16 data_size)
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

  //As we know the vector is not full if the tail is equal to capacity
  //we have free space at the front
  if(vector->tail_ == vector->capacity_){ 
    memmove(vector->storage_ + vector->head_ -1, 
            vector->storage_ + vector->head_,
            sizeof(MemoryNode)*VECTOR_length(vector));
    --vector->head_;
  }else{//Tail is pointing to the next free node we increase the tail
    ++vector->tail_;
  }
  MemoryNode *aux = vector->storage_ + (vector->tail_-1);
  s16 status = aux->ops_->init(aux);
  status = aux->ops_->memCopy(aux, data, data_size);
  return status;  
}

s16 VECTOR_insertAt(Vector *vector, void *data, u16 position, u16 data_size)
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
  if(position > VECTOR_length(vector)){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return kErrorCode_Out_Of_Range_Index;    
  }

  s16 status;

  if(0 == position){ //Insertion at the start
    status = VECTOR_insertFirst(vector, data, data_size);
    return status;
  }else if(position == VECTOR_length(vector)){ //Insertion at the end
    status = VECTOR_insertLast(vector, data, data_size);
    return status;
  //we don't have space at the end
  }else if(vector->tail_ == vector->capacity_){ 
    memmove(vector->storage_ + (vector->head_ -1),
            vector->storage_ + vector->head_,
            sizeof(MemoryNode)* position);
    --vector->head_;
  }else{ //We can move to the right as we have space at the end
    memmove(vector->storage_ + (vector->head_ + position + 1),
            vector->storage_ + (vector->head_ + position),
            sizeof(MemoryNode)* (VECTOR_length(vector) - position) );
    ++vector->tail_;
  }
  MemoryNode *aux = vector->storage_ + position;
  //we initialize the memory node before doing the memcopy
  status = aux->ops_->init(aux);
  status = aux->ops_->memCopy(aux, data, data_size);
  return status;
}

void* VECTOR_extractFirst(Vector *vector)
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
  void *data = aux->ops_->data(aux);
  s16 status = aux->ops_->init(aux);
  if(kErrorCode_Null_Pointer_Reference_Received == status){
#ifdef VERBOSE_
    printf("Error: [%s] Strange behaviour, please inform us\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(1 != VECTOR_length(vector)){
    //If there's more than one element, we want to increase the head after the
    //extraction, the length can't be 0 as we checked the vector is not empty 
    //At the start
    ++vector->head_;
  }else{
    //If there's just one element we want to decrease the tail after the
    //extraction
    --vector->tail_;
  }
  return data;
}

void* VECTOR_extractLast(Vector *vector)
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
  MemoryNode *aux = vector->storage_ + (vector->tail_ - 1);
  void *data = aux->ops_->data(aux);
  s16 status = aux->ops_->init(aux);
  if(kErrorCode_Null_Pointer_Reference_Received == status){
#ifdef VERBOSE_
    printf("Error: [%s] Strange behaviour, please inform us\n", __FUNCTION__);
#endif
    return NULL;
  }
  --vector->tail_;
  return data;
}

void* VECTOR_extractAt(Vector *vector, u16 position)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(VECTOR_isEmpty(vector)){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is empty\n", __FUNCTION__);
#endif
    return NULL;    
  }
  if(position >= VECTOR_length(vector)){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return NULL;    
  } 

  if(0 == position){ //extraction of the first element
    return VECTOR_extractFirst(vector);
  }else if(position == VECTOR_length(vector) - 1){ //Extraction at the end
    return VECTOR_extractLast(vector);
  }else{ 
    MemoryNode *aux = vector->storage_ + (vector->head_+position);
    void *data = aux->ops_->data(aux);
    memmove(vector->storage_ + (vector->head_ + position),
            vector->storage_ + (vector->head_ + position + 1),
            sizeof(MemoryNode)* (VECTOR_length(vector)-(position+1)));
    //We have shifted the data to the left, so we need to initialize the last
    //element that will now be the new tail of the vector
    --vector->tail_;
    aux = vector->storage_ + (vector->tail_);
    s16 status = aux->ops_->init(aux);
    if(kErrorCode_Null_Pointer_Reference_Received == status){
#ifdef VERBOSE_
      printf("Error:[%s] Strange behaviour, please inform us\n", __FUNCTION__);
#endif
      return NULL;
    }
    
    return data;
  }
}

s16 VECTOR_concat(Vector *vector, Vector *src)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Vector;
  }
  if(NULL == src){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Parameter_Received;
  }

  s16 status = VECTOR_resize(vector, vector->capacity_ + src->capacity_);

  if(kErrorCode_Ok != status){
    return status;
  }

  for(u16 i = 0; i < VECTOR_length(src); ++i){
    VECTOR_insertLast(vector, src->storage_->ops_->data(src->storage_ + i),
                      src->storage_->ops_->size(src->storage_ + i));
  }

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

void VECTOR_print(Vector *vector)
{
  if(NULL == vector){
#ifdef VERBOSE_
    printf("Error: [%s] The vector is null\n", __FUNCTION__);
#endif
    printf("NULL");
    return;
  }
  VECTOR_traverse(vector, vector->storage_->ops_->print);
}