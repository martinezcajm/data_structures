// adt_vector.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_vector.h
#include <stdio.h>
#include <stdlib.h>

#include "adt_vector.h"
#include "common_def.h"

static s16 VECTOR_init(Vector *vector);
static s16 VECTOR_destroy(Vector **vector);
static s16 VECTOR_reset(Vector *vector);
static u16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *));
/*static u16 VECTOR_resize(Vector *vector, u16 new_size);
static u16 VECTOR_capacity(Vector *vector);
static u16 VECTOR_length(Vector *vector);
static bool VECTOR_isEmpty(Vector *vector);
static bool VECTOR_isFull(Vector *vector);
static void* VECTOR_head(Vector *vector);
static void* VECTOR_last(Vector *vector);
static void* VECTOR_at(Vector *vector, u16 position);
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
  .traverse = VECTOR_traverse
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
  //TODO use traverse function (when is done) to free the memory nodes
  free(vector->storage_);
  vector->storage_ = NULL;
  vector->head_ = 0;
  vector->tail_ = 0;
  vector->capacity_ = 0;
  return kErrorCode_Ok;
}

u16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *))
{
  
}

/*u16 VECTOR_resize(Vector *vector, u16 new_size)
{
  
}

u16 VECTOR_capacity(Vector *vector)
{
  
}

u16 VECTOR_length(Vector *vector)
{
  
}

bool VECTOR_isEmpty(Vector *vector)
{
  
}

bool VECTOR_isFull(Vector *vector)
{
  
}

void* VECTOR_head(Vector *vector)
{
  
}

void* VECTOR_last(Vector *vector)
{
  
}

void* VECTOR_at(Vector *vector, u16 position)
{
  
}

s16 VECTOR_insertFirst(Vector *vector, void *data)
{
  
}

s16 VECTOR_insertLast(Vector *vector, void *data)
{
  
}

s16 VECTOR_insertAt(Vector *vector, void *data, u16 position)
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