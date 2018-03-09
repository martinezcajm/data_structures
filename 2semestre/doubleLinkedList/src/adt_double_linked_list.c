// adt_list.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_list.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_double_linked_list.h"
#include "common_def.h"

static s16 DLLIST_init(DLList *list, u16 capacity);
static s16 DLLIST_destroy(DLList **list);
static s16 DLLIST_reset(DLList *list);
static s16 DLLIST_resize(DLList *list, u16 new_size);
static u16 DLLIST_capacity(DLList *list);
static u16 DLLIST_length(DLList *list);
static bool DLLIST_length_debug(DLList *list);
static bool DLLIST_isEmpty(DLList *list);
static bool DLLIST_isFull(DLList *list);
static void* DLLIST_head(DLList *list);
static void* DLLIST_last(DLList *list);
static void* DLLIST_at(DLList *list, u16 position);
static s16 DLLIST_insertFirst(DLList *list, void *data, u16 data_size);
static s16 DLLIST_insertLast(DLList *list, void *data, u16 data_size);
static s16 DLLIST_insertAt(DLList *list, void *data, u16 position,
                           u16 data_size);
static void* DLLIST_extractFirst(DLList *list);
static void* DLLIST_extractLast(DLList *list);
static void* DLLIST_extractAt(DLList *list, u16 position);
static s16 DLLIST_concat(DLList *list, DLList *src);
static u16 DLLIST_traverse(DLList *list, void(*callback) (MemoryNode *));
static void DLLIST_print(DLList *list);

struct adt_double_linked_list_ops_s adt_double_linked_list_ops =
{
  .destroy = DLLIST_destroy,
  .reset = DLLIST_reset,
  .resize = DLLIST_resize,
  .capacity = DLLIST_capacity,
  .length = DLLIST_length,
  .length_debug = DLLIST_length_debug,
  .isEmpty = DLLIST_isEmpty,
  .isFull = DLLIST_isFull,
  .head = DLLIST_head,
  .last = DLLIST_last,
  .at = DLLIST_at,
  .insertFirst = DLLIST_insertFirst,
  .insertLast = DLLIST_insertLast,
  .insertAt = DLLIST_insertAt,
  .extractFirst = DLLIST_extractFirst,
  .extractLast = DLLIST_extractLast,
  .extractAt = DLLIST_extractAt,
  .concat = DLLIST_concat,
  .traverse = DLLIST_traverse,
  .print = DLLIST_print
};

DLList* DLLIST_Create(u16 capacity)
{
  DLList *list = malloc(sizeof(DLList));
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  DLLIST_init(list, capacity);
  //As init can only be called from create it can't return other error code 
  //than ok  
  return list;
}

s16 DLLIST_init(DLList *list, u16 capacity)
{
  //This function will only by called from Create so we don't need to check
  //the pointer.
  list->first_ = NULL;
  list->last_ = NULL;
  list->capacity_ = capacity;
  list->length_ = 0;
  list->ops_ = &adt_double_linked_list_ops;
  return kErrorCode_Ok;
}

s16 DLLIST_destroy(DLList **list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  if(NULL == *list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_DLList;
  }
  //list->first_ shouldn't be NULL if list isn't empty but to be safe we check
  //it
  if(!DLLIST_isEmpty(*list)  && NULL != (*list)->first_){
    //DLLIST_traverse(*list, (*list)->first_->ops_->s_free);
    while( NULL != (*list)->first_){
      (*list)->last_ = (*list)->first_;
      (*list)->first_ = (*list)->first_->ops_->next((*list)->first_);
      (*list)->last_->ops_->free(&((*list)->last_));
    }
  }
  free(*list);
  *list = NULL;
  return kErrorCode_Ok;
}

s16 DLLIST_reset(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_DLList;
  }
  //list->first_ shouldn't be NULL if list isn't empty but to be safe we check
  //it
  if(!DLLIST_isEmpty(list) && NULL != list->first_){
    DLLIST_traverse(list, list->first_->ops_->reset);
  }
  list->length_ = 0;
  list->first_ = NULL;
  list->last_ = NULL;
  return kErrorCode_Ok;
}

s16 DLLIST_resize(DLList *list, u16 new_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_DLList;
  }
  if(new_size < list->length_){
    return kErrorCode_Resize_Loss_Of_Data;
  }
  list->capacity_ = new_size;
  return kErrorCode_Ok;
}

u16 DLLIST_capacity(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return list->capacity_;  
}

u16 DLLIST_length(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return list->length_;
}

bool DLLIST_length_debug(DLList *list){
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return false;
  }
  MemoryNode *aux = list->first_;
  u16 elements_in_list = 0;
  while(aux->ops_->next(aux) != NULL){
    aux = aux->ops_->next(aux);
    elements_in_list ++;
  }
  return elements_in_list == list->length_;
}

bool DLLIST_isEmpty(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return false;
  }  
  return 0 == list->length_;
}

bool DLLIST_isFull(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return true;
  }
  if(0 == list->capacity_) return false; 
  return list->length_ == list->capacity_;
}

void* DLLIST_head(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(DLLIST_isEmpty(list)){
    return NULL;
  }
  return list->first_->ops_->data(list->first_);
}

void* DLLIST_last(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(DLLIST_isEmpty(list)){
    return NULL;
  }
  return list->last_->ops_->data(list->last_);
}

void* DLLIST_at(DLList *list, u16 position)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(DLLIST_isEmpty(list)){
    return NULL;
  }
  if(position >= list->length_){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return NULL;    
  }
  //In case the position is the last one we return directly the data pointed
  //by last
  if(position == list->length_ - 1){
    return list->last_->ops_->data(list->last_);
  }
  u16 index = 0;
  MemoryNode *aux = list->first_;
  while(index != position){
    aux = aux->ops_->next(aux);
    ++index;
  }
  return aux->ops_->data(aux);
}

s16 DLLIST_insertFirst(DLList *list, void *data, u16 data_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_DLList;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(DLLIST_isFull(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_DLList_Is_Full;    
  }
  MemoryNode *new_node = MEMNODE_create();
  if(NULL == new_node){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  } 
  if(NULL == list->last_){
    list->last_ = new_node;
  }
  new_node->ops_->setNext(new_node, list->first_);
  if(NULL != list->first_){
    list->first_->ops_->setPrev(list->first_, new_node);
  }
  list->first_ = new_node;
  ++list->length_;
  s16 status = list->first_->ops_->memCopy(list->first_, data, data_size);
  return status;
}

s16 DLLIST_insertLast(DLList *list, void *data, u16 data_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_DLList;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(DLLIST_isFull(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_DLList_Is_Full;    
  }
  MemoryNode *new_node = MEMNODE_create();
  if(NULL == new_node){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  } 
  if(NULL == list->first_){
    list->first_ = new_node;
  }
  if(NULL != list->last_){
    list->last_->ops_->setNext(list->last_, new_node);
  }
  new_node->ops_->setPrev(new_node, list->last_);
  list->last_ = new_node;
  ++list->length_;
  s16 status = list->last_->ops_->memCopy(list->last_, data, data_size);
  return status;
}

s16 DLLIST_insertAt(DLList *list, void *data, u16 position, u16 data_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_DLList;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(DLLIST_isFull(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_DLList_Is_Full;    
  }
  if(position >= list->length_){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return kErrorCode_Out_Of_Range_Index;    
  }
  s16 status = 0;
  if(0 == position){ //Insertion at the start
    status = DLLIST_insertFirst(list, data, data_size);
    return status;
  }else if(position == list->length_ - 1){ //Insertion at the end
    status = DLLIST_insertLast(list, data, data_size);
    return status;
  }
  MemoryNode *new_node = MEMNODE_create();
  if(NULL == new_node){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  MemoryNode *aux = list->first_;
  u16 index = 0;
  //We wish to found the node previous to the position we want to insert
  while(index != position-1){
    aux = aux->ops_->next(aux);
    ++index;
  }
  new_node->ops_->setNext(new_node, aux->ops_->next(aux));
  aux->ops_->setNext(aux,new_node);
  ++list->length_;
  status = new_node->ops_->memCopy(new_node, data, data_size);
  return status;
}

void* DLLIST_extractFirst(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(DLLIST_isEmpty(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is empty\n", __FUNCTION__);
#endif
    return NULL;
  }
  MemoryNode *node_to_extract = list->first_;
  void* data = list->first_->ops_->data(list->first_);
  list->first_ = list->first_->ops_->next(list->first_);
  //If the list only had one element we set last to NULL
  if(NULL == list->first_){
    list->last_ = NULL;
  } 
  else{
    list->first_->ops_->setPrev(list->first_, NULL);
  }
  //We free the node without affecting it's data
  node_to_extract->ops_->soft_free(&node_to_extract);
  --list->length_;
  return data;
}

void* DLLIST_extractLast(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(DLLIST_isEmpty(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is empty\n", __FUNCTION__);
#endif
    return NULL;
  }
  MemoryNode *node_to_extract = list->last_;
  list->last_ = node_to_extract->ops_->prev(node_to_extract);

  if(NULL == list->last_){//In case case tere was just an element
    list->first_ = NULL;
  }else{
    list->last_->ops_->setNext(list->last_, NULL);
  }
  void* data = node_to_extract->ops_->data(node_to_extract);
  node_to_extract->ops_->soft_free(&node_to_extract);
  --list->length_;
  return data;
}

void* DLLIST_extractAt(DLList *list, u16 position)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(DLLIST_isEmpty(list)){
    return NULL;
  }
  if(position >= list->length_){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return NULL;    
  }
  void* data = NULL;
  if(0 == position){ //Insertion at the start
    data = DLLIST_extractLast(list);
    return data;
  }else if(position == list->length_ - 1){ //Insertion at the end
    data = DLLIST_extractFirst(list);
    return data;
  }
  MemoryNode *node_to_extract = NULL;
  MemoryNode *aux = list->first_;
  u16 index = 0;
  //We wish to found the node previous to the position we want to insert
  while(index != position-1){
    aux = aux->ops_->next(aux);
    ++index;
  }
  node_to_extract = aux->ops_->next(aux);
  data = node_to_extract->ops_->data(node_to_extract);
  aux->ops_->setNext(aux, node_to_extract->ops_->next(node_to_extract));
  node_to_extract->ops_->soft_free(&node_to_extract);
  --list->length_;  
  return data;
}

s16 DLLIST_concat(DLList *list, DLList *src)
{
  if(NULL == list){
#ifdef VERBOSE_ 
      printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
      return kErrorCode_Null_DLList;
  }
  if(NULL == src){
#ifdef VERBOSE_ 
    printf("Error: [%s] The source list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  list->last_->ops_->setNext(list->last_, src->first_);
  list->last_ = src->last_;
  if(0 == list->capacity_ || 0 == src->capacity_){
    list->capacity_ = 0;
  }else{
    list->capacity_ = list->capacity_ + src->capacity_;
  }
  list->length_ = list->length_ + src->length_;
  src->first_ = NULL;
  src->last_ = NULL;
  src->length_ = 0;
  return kErrorCode_Ok;  
}

u16 DLLIST_traverse(DLList *list, void(*callback) (MemoryNode *))
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return 0;
  }
  u16 index = 0;
  MemoryNode *aux = list->first_;
  while( NULL != aux){
    callback(aux);
    //It shouldn't happen, reset is not allowed for traverse, but we assure
    //that aux is not null before the callback method
    if(NULL != aux) aux = aux->ops_->next(aux);
    index++;
  }
  return index;
}

void DLLIST_print(DLList *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    printf("NULL");
    return;
  }
  if(NULL == list->first_){
    printf("EMPTY");
    return;
  }
  DLLIST_traverse(list, list->first_->ops_->print);
}