// adt_list.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_list.h
#include <cstdio>
#include <cstdlib>

#include "adt_list.h"
#include "common_def.h"

List::List(u16 capacity)
{
  init(capacity);
}

List::~List()
{
  //list->first_ shouldn't be NULL if list isn't empty but to be safe we check
  //it
  reset();
}


s16 List::init(const u16 capacity)
{
  first_ = nullptr;
  last_ = nullptr;
  capacity_ = capacity;
  length_ = 0;
  return kErrorCode_Ok;
}

s16 List::reset()
{
  //list->first_ shouldn't be NULL if list isn't empty but to be safe we check
  //it
  if (!isEmpty()) {
    while (nullptr != first_) {
      last_ = first_;
      first_ = first_->next();
      last_->free_mn();
    }
  }
  length_ = 0;
  first_ = nullptr;
  last_ = nullptr;
  return kErrorCode_Ok;
}

s16 List::resize(const u16 new_size)
{
  if (new_size < length_) {
    return kErrorCode_Resize_Loss_Of_Data;
  }
  capacity_ = new_size;
  return kErrorCode_Ok;
}

u16 List::capacity() const
{
  return capacity_;
}

u16 List::length() const
{
  return length_;
}

bool List::length_debug() const
{
  MemoryNode *aux = first_;
  u16 elements_in_list = 0;
  while (aux->next() != nullptr) {
    aux = aux->next();
    elements_in_list++;
  }
  return elements_in_list == length_;
}

bool List::isEmpty() const
{
  return 0 == length_;
}

bool List::isFull() const
{
  if (0 == capacity_) return false;
  return length_ == capacity_;
}

void* List::head()
{
  if (isEmpty()) {
    return nullptr;
  }
  return first_->data();
}

void* List::last()
{
  if (isEmpty()) {
    return nullptr;
  }
  return last_->data();
}

void* List::at(const u16 position)
{
  if (isEmpty()) {
    return nullptr;
  }
  if (position >= length_) {
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return nullptr;
  }
  //In case the position is the last one we return directly the data pointed
  //by last
  if (position == length_ - 1) {
    return last_->data();
  }
  u16 index = 0;
  MemoryNode *aux = first_;
  while (index != position) {
    aux = aux->next();
    ++index;
  }
  return aux->data();
}

s16 List::insertFirst(void* data, const u16 data_size)
{
  if (nullptr == data) {
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if (isFull()) {
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_List_Is_Full;
  }
  MemoryNode *new_node = new MemoryNode();
  if (nullptr == new_node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  if (nullptr == last_) {
    last_ = new_node;
  }
  new_node->setNext(first_);
  first_ = new_node;
  ++length_;
  const s16 status = first_->memCopy(data, data_size);
  return status;
}

s16 List::insertLast(void* data, const u16 data_size)
{
  if (nullptr == data) {
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if (isFull()) {
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_List_Is_Full;
  }
  MemoryNode *new_node = new MemoryNode();
  if (nullptr == new_node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  if (nullptr == first_) {
    first_ = new_node;
  }
  if (nullptr != last_) {
    last_->setNext(new_node);
  }
  last_ = new_node;
  ++length_;
  const s16 status = last_->memCopy(data, data_size);
  return status;
}

s16 List::insertAt(void* data, const u16 position, const u16 data_size)
{
  if (nullptr == data) {
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if (isFull()) {
#ifdef VERBOSE_
    printf("Error: [%s] The list is full\n", __FUNCTION__);
#endif
    return kErrorCode_List_Is_Full;
  }
  if (position >= length_) {
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return kErrorCode_Out_Of_Range_Index;
  }
  s16 status = 0;
  if (0 == position) { //Insertion at the start
    status = insertFirst(data, data_size);
    return status;
  }
  else if (position == length_ - 1) { //Insertion at the end
    status = insertLast(data, data_size);
    return status;
  }
  MemoryNode *new_node = new MemoryNode();
  if (nullptr == new_node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  MemoryNode *aux = first_;
  u16 index = 0;
  //We wish to found the node previous to the position we want to insert
  while (index != position - 1) {
    aux = aux->next();
    ++index;
  }
  new_node->setNext(aux->next());
  aux->setNext(new_node);
  ++length_;
  status = new_node->memCopy(data, data_size);
  return status;
}

void* List::extractFirst()
{
  if (isEmpty()) {
#ifdef VERBOSE_
    printf("Error: [%s] The list is empty\n", __FUNCTION__);
#endif
    return nullptr;
  }
  MemoryNode *node_to_extract = first_;
  void* data = first_->data();
  first_ = first_->next();
  //If the list only had one element we set last to NULL
  if (nullptr == first_) last_ = nullptr;
  //We free the node without affecting it's data
  node_to_extract->free_mn(true);
  --length_;
  return data;
}

void* List::extractLast()
{
  if (isEmpty()) {
#ifdef VERBOSE_
    printf("Error: [%s] The list is empty\n", __FUNCTION__);
#endif
    return nullptr;
  }
  MemoryNode *node_to_extract = last_;
  if(first_->next() != nullptr) //first and last are not the same
  {
    last_ = first_;
    //We want to check if the next of our next is NULL to get the element before
    //the previous last, as this will be the new last
    while (nullptr != last_->next()->next()) {
      last_ = last_->next();
    }
  }
  //list->last_ = aux;
  last_->setNext(nullptr);
  void* data = node_to_extract->data();
  node_to_extract->free_mn(true);
  --length_;
  //In case there was just one element
  if (0 == length_) {
    last_ = nullptr;
    first_ = nullptr;
  }
  return data;
}

void* List::extractAt(u16 position)
{
  if (isEmpty()) {
    return nullptr;
  }
  if (position >= length_) {
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return nullptr;
  }
  void* data = nullptr;
  if (0 == position) { //extraction at the start
    data = extractFirst();
    return data;
  }
  else if (position == length_ - 1) { //extraction at the end
    data = extractLast();
    return data;
  }
  MemoryNode *node_to_extract = nullptr;
  MemoryNode *aux = first_;
  u16 index = 0;
  //We wish to found the node previous to the position we want to insert
  while (index != position - 1) {
    aux = aux->next();
    ++index;
  }
  node_to_extract = aux->next();
  data = node_to_extract->data();
  aux->setNext(node_to_extract->next());
  node_to_extract->free_mn(true);
  --length_;
  return data;
}

s16 List::concat(List* src)
{
  if (nullptr == src) {
#ifdef VERBOSE_ 
    printf("Error: [%s] The source list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  last_->setNext(src->first_);
  last_ = src->last_;
  if (0 == capacity_ || 0 == src->capacity_) {
    capacity_ = 0;
  }
  else {
    capacity_ = capacity_ + src->capacity_;
  }
  length_ = length_ + src->length_;
  src->first_ = nullptr;
  src->last_ = nullptr;
  src->length_ = 0;
  return kErrorCode_Ok;
}

u16 List::traverse(s16 ( MemoryNode::* callback)()) const
{
  u16 index = 0;
  MemoryNode *aux = first_;
  while (nullptr != aux) {
    (*aux.*callback)();
    //It shouldn't happen, reset is not allowed for traverse, but we assure
    //that aux is not null before the callback method
    if (nullptr != aux) aux = aux->next();
    index++;
  }
  return index;
}

void List::print() const
{
  if (nullptr == first_) {
    printf("EMPTY");
    return;
  }
  traverse(&MemoryNode::print);
}