// memory_node.c : 
// Toni Barella
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at memory_node.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_node.h"
#include "common_def.h"

static s16 MEMNODE_init(MemoryNode *node);
static s16 MEMNODE_reset(MemoryNode *node);
static s16 MEMNODE_free (MemoryNode **node);
static void* MEMNODE_data(MemoryNode *node);
static u16 MEMNODE_size(MemoryNode *node);
static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memSet(MemoryNode *node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memMask(MemoryNode *node, u8 mask);
static void MEMNODE_print (MemoryNode *node);


struct memory_node_ops_s memory_node_ops =
{
  .reset = MEMNODE_reset,
  .free = MEMNODE_free,
  .data = MEMNODE_data,
  .size = MEMNODE_size,
  .setData = MEMNODE_setData,
  .memSet = MEMNODE_memSet,
  .memCopy = MEMNODE_memCopy,
  .memConcat = MEMNODE_memConcat,
  .memMask = MEMNODE_memMask,
  .print = MEMNODE_print
};


MemoryNode* MEMNODE_create()
{
  MemoryNode *node = malloc(sizeof(MemoryNode));
  if (NULL == node)
  {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  MEMNODE_init(node);
  //As init can only called from create it can't return other error code than
  //ok
  return node;
}

s16 MEMNODE_createFromRef(MemoryNode **node){
  if(NULL == node){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  if(NULL != *node){
#ifdef VERBOSE_
    printf("Warning: [%s] The reference passed already had a value\n",
           __FUNCTION__);
#endif
    return kWarningCode_Strange_Operation;
  }

  *node = MEMNODE_create();
  if(NULL == *node){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  return kErrorCode_Ok;
}

s16 MEMNODE_init(MemoryNode *node)
{
  //This function will only by called from Create so we don't need to check
  //the pointer.
  node->data_ = NULL;
  node->size_ = 0;
  node->ops_ = &memory_node_ops;
  return kErrorCode_Ok;
}

static s16 MEMNODE_reset(MemoryNode *node){
  if (NULL == node)
  {
#ifdef VERBOSE_
    printf("Error: [%s] the memory node is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Memory_Node;
  }
  node->size_ = 0;
  if(NULL == node->data_){
    return kErrorCode_Ok;
  }
  free(node->data_);
  node->data_ = NULL;
  return kErrorCode_Ok;
}

s16 MEMNODE_free (MemoryNode **node){
  if(NULL == node){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  //We don't need to check if the pointer to node is null as reset will do it
  s16 status = MEMNODE_reset(*node);
  //We check if all went well and free the node in that case, if the node we
  //sent to reset was already null it's already free.
  if(kErrorCode_Ok == status){
    free(*node);
    *node = NULL;
  }
  return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node) // returns a reference to data
{
  if(NULL == node){
#ifdef VERBOSE_
      printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
      return NULL;
  }
  return node->data_;
}

u16 MEMNODE_size(MemoryNode *node) // returns data size
{
  if(NULL == node){
#ifdef VERBOSE_
      printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
      return 0;
  }
  return node->size_;
}

s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes) 
{
  if(NULL == src){
#ifdef VERBOSE_
    printf("Warning: [%s] The data passed is null\n", __FUNCTION__);
#endif
    return kWarningCode_Strange_Operation;
  }
  s16 status = MEMNODE_reset(node);
  if(kErrorCode_Null_Memory_Node == status){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return status;
  }
  node->size_ = bytes; 
  node->data_ = src;
  return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value){
  if(NULL == node){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Memory_Node;
  }
  if(NULL == node->data_){
#ifdef VERBOSE_
    printf("Error: [%s] Trying to do a memset to null data\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  memset(node->data_, (s16)value, node->size_);
  return kErrorCode_Ok;
}

s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes){
  //We want to make sure the size of the new data to copy is greater than 0
  //before anything else
  if(0 == bytes){
#ifdef VERBOSE_
    printf("Warning: [%s] Asking to do a memcopy of 0 bytes\n", __FUNCTION__);
#endif
    return kWarningCode_Strange_Operation;
  }

  if(NULL == src){
#ifdef VERBOSE_
  printf("Error: [%s] the src passed is null\n", __FUNCTION__);
#endif
  return kErrorCode_Null_Pointer_Parameter_Received;
  }

  //We don't need to check if node is null as reset will do it
  s16 status = MEMNODE_reset(node);
  if(kErrorCode_Null_Memory_Node == status){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return status;
  }
  node->data_ = malloc(bytes);
  if(NULL == node->data_){
#ifdef VERBOSE_
    printf("Error: [%s] malloc failed\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  memcpy(node->data_, src, bytes);
  node->size_ = bytes;
  return kErrorCode_Ok;
}

s16 MEMNODE_memConcat (MemoryNode *node, void *src, u16 bytes){
  if(NULL == node){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Memory_Node;
  }
  if(NULL == node->data_){
#ifdef VERBOSE_
    printf("Error: [%s] Trying to concat with null data\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(NULL == src){
#ifdef VERBOSE_
    printf("Warning: [%s] Trying to concat with null source\n", __FUNCTION__);
#endif
    return kWarningCode_Strange_Operation;
  }
  u8 *aux;
  aux = (u8*)malloc(node->size_ + bytes);
  if(NULL == aux){
#ifdef VERBOSE_
    printf("Error: [%s] malloc failed\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  memcpy(aux, node->data_, node->size_);
  memcpy(aux + (node->size_), src, bytes);
  //We have already checked that data is not null.
  free(node->data_);
  node->data_ = aux;
  node->size_ = node->size_ + bytes;
  return kErrorCode_Ok;
}

s16 MEMNODE_memMask(MemoryNode *node, u8 mask){
  if(NULL == node){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Memory_Node;
  }
  u8 *aux;
  aux = (u8*)node->data_;
  for(u8 i = 0; i < node->size_; i++){
    aux[i] &= mask;
  }
  return kErrorCode_Ok;
}

void MEMNODE_print(MemoryNode *node){
  if(NULL == node){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    printf("The node is null\n");
    return;
  }
  if(NULL == node->data_){
#ifdef VERBOSE_
    printf("Error: [%s] The data of memory node is null \n", __FUNCTION__);
#endif
    printf("The data is null\n");
    return;
  }
  u8 *aux;
  aux = (u8*)node->data_;
  for(u8 i = 0; i < node->size_; i++){
    printf("%c", aux[i]);
  }
  printf("\n");
}