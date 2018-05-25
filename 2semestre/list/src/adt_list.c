// adt_list.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_list.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_list.h"
#include "common_def.h"

static s16 LIST_init(List *list, u16 capacity);
static s16 LIST_destroy(List **list);
static s16 LIST_reset(List *list);
static s16 LIST_resize(List *list, u16 new_size);
static u16 LIST_capacity(List *list);
static u16 LIST_length(List *list);
static bool LIST_length_debug(List *list);
static bool LIST_isEmpty(List *list);
static bool LIST_isFull(List *list);
static void* LIST_head(List *list);
static void* LIST_last(List *list);
static void* LIST_at(List *list, u16 position);
static s16 LIST_insertFirst(List *list, void *data, u16 data_size);
static s16 LIST_insertLast(List *list, void *data, u16 data_size);
static s16 LIST_insertAt(List *list, void *data, u16 position, u16 data_size);
static void* LIST_extractFirst(List *list);
static void* LIST_extractLast(List *list);
static void* LIST_extractAt(List *list, u16 position);
static s16 LIST_concat(List *list, List *src);
static u16 LIST_traverse(List *list, void(*callback) (MemoryNode *));
static void LIST_print(List *list);

struct adt_list_ops_s adt_list_ops =
{
  .destroy = LIST_destroy,
  .reset = LIST_reset,
  .resize = LIST_resize,
  .capacity = LIST_capacity,
  .length = LIST_length,
  .length_debug = LIST_length_debug,
  .isEmpty = LIST_isEmpty,
  .isFull = LIST_isFull,
  .head = LIST_head,
  .last = LIST_last,
  .at = LIST_at,
  .insertFirst = LIST_insertFirst,
  .insertLast = LIST_insertLast,
  .insertAt = LIST_insertAt,
  .extractFirst = LIST_extractFirst,
  .extractLast = LIST_extractLast,
  .extractAt = LIST_extractAt,
  .concat = LIST_concat,
  .traverse = LIST_traverse,
  .print = LIST_print
};

List* LIST_Create(u16 capacity)
{
  List *list = malloc(sizeof(List));
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  LIST_init(list, capacity);
  //As init can only be called from create it can't return other error code 
  //than ok  
  return list;
}

s16 LIST_init(List *list, u16 capacity)
{
  //This function will only by called from Create so we don't need to check
  //the pointer.
  list->first_ = NULL;
  list->last_ = NULL;
  list->capacity_ = capacity;
  list->length_ = 0;
  list->ops_ = &adt_list_ops;
  return kErrorCode_Ok;
}

s16 LIST_destroy(List **list)
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
    return kErrorCode_Null_List;
  }
  //list->first_ shouldn't be NULL if list isn't empty but to be safe we check
  //it
  if(!LIST_isEmpty(*list)  && NULL != (*list)->first_){
    //LIST_traverse(*list, (*list)->first_->ops_->s_free);
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

s16 LIST_reset(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_List;
  }
  //list->first_ shouldn't be NULL if list isn't empty but to be safe we check
  //it
  if (!LIST_isEmpty(list)) {
    while (NULL != list->first_) {
      list->last_ = list->first_;
      list->first_ = list->first_->ops_->next(list->first_);
      list->last_->ops_->free(&(list->last_));
    }
  }
  list->length_ = 0;
  list->first_ = NULL;
  list->last_ = NULL;
  return kErrorCode_Ok;
}

s16 LIST_resize(List *list, u16 new_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_List;
  }
  if(new_size < list->length_){
    return kErrorCode_Resize_Loss_Of_Data;
  }
  list->capacity_ = new_size;
  return kErrorCode_Ok;
}

u16 LIST_capacity(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return list->capacity_;  
}

u16 LIST_length(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return 0;
  }
  return list->length_;
}

bool LIST_length_debug(List *list){
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

bool LIST_isEmpty(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return false;
  }  
  return 0 == list->length_;
}

bool LIST_isFull(List *list)
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

void* LIST_head(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(LIST_isEmpty(list)){
    return NULL;
  }
  return list->first_->ops_->data(list->first_);
}

void* LIST_last(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(LIST_isEmpty(list)){
    return NULL;
  }
  return list->last_->ops_->data(list->last_);
}

void* LIST_at(List *list, u16 position)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(LIST_isEmpty(list)){
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

s16 LIST_insertFirst(List *list, void *data, u16 data_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_List;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(LIST_isFull(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_List_Is_Full;    
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
  list->first_ = new_node;
  ++list->length_;
  s16 status = list->first_->ops_->memCopy(list->first_, data, data_size);//set
  return status;
}

s16 LIST_insertLast(List *list, void *data, u16 data_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_List;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(LIST_isFull(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_List_Is_Full;    
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
  list->last_ = new_node;
  ++list->length_;
  s16 status = list->last_->ops_->memCopy(list->last_, data, data_size);
  return status;
}

s16 LIST_insertAt(List *list, void *data, u16 position, u16 data_size)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_List;
  }
  if(NULL == data){
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if(LIST_isFull(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_List_Is_Full;    
  }
  if(position >= list->length_){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return kErrorCode_Out_Of_Range_Index;    
  }
  s16 status = 0;
  if(0 == position){ //Insertion at the start
    status = LIST_insertFirst(list, data, data_size);
    return status;
  }else if(position == list->length_ - 1){ //Insertion at the end
    status = LIST_insertLast(list, data, data_size);
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

void* LIST_extractFirst(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(LIST_isEmpty(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is empty\n", __FUNCTION__);
#endif
    return NULL;
  }
  MemoryNode *node_to_extract = list->first_;
  void* data = list->first_->ops_->data(list->first_);
  list->first_ = list->first_->ops_->next(list->first_);
  //If the list only had one element we set last to NULL
  if(NULL == list->first_) list->last_ = NULL;
  //We free the node without affecting it's data
  node_to_extract->ops_->soft_free(&node_to_extract);
  --list->length_;
  return data;
}

void* LIST_extractLast(List *list)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(LIST_isEmpty(list)){
#ifdef VERBOSE_
    printf("Error: [%s] The list is empty\n", __FUNCTION__);
#endif
    return NULL;
  }
  MemoryNode *node_to_extract = list->last_;
  //MemoryNode *aux = list->first_;
  list->last_ = list->first_;
  //We want to check if the next of our next is NULL to get the element before
  //the previous last, as this will be the new last
  while(NULL != list->last_->ops_->next(list->last_->ops_->next(list->last_))){
    list->last_ = list->last_->ops_->next(list->last_);
  }
  //list->last_ = aux;
  list->last_->ops_->setNext(list->last_, NULL);
  void* data = node_to_extract->ops_->data(node_to_extract);
  node_to_extract->ops_->soft_free(&node_to_extract);
  --list->length_;
  //In case there was just one element
  if(0 == list->length_){
    list->last_ = NULL;
    list->first_ = NULL;
  }
  return data;
}

void* LIST_extractAt(List *list, u16 position)
{
  if(NULL == list){
#ifdef VERBOSE_
    printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
    return NULL;
  }
  if(LIST_isEmpty(list)){
    return NULL;
  }
  if(position >= list->length_){
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return NULL;    
  }
  void* data = NULL;
  if(0 == position){ //Extraction at the start
    data = LIST_extractFirst(list);
    return data;
  }else if(position == list->length_ - 1){ //Extraction at the end
    data = LIST_extractLast(list);
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

s16 LIST_concat(List *list, List *src)
{
  if(NULL == list){
#ifdef VERBOSE_ 
      printf("Error: [%s] The list is null\n", __FUNCTION__);
#endif
      return kErrorCode_Null_List;
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

u16 LIST_traverse(List *list, void(*callback) (MemoryNode *))
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

void LIST_print(List *list)
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
  LIST_traverse(list, list->first_->ops_->print);
}