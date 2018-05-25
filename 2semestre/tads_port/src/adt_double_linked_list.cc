// adt_list.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_double_linked_list.h
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "adt_double_linked_list.h"
#include "common_def.h"


DLList::DLList(const u16 capacity)
{
  init(capacity);
}

DLList::~DLList()
{
  reset();
}

s16 DLList::init(const u16 capacity)
{
  first_ = nullptr;
  last_ = nullptr;
  capacity_ = capacity;
  length_ = 0;
  return kErrorCode_Ok;
}

s16 DLList::reset()
{
  //first_ shouldn't be NULL if list isn't empty but to be safe we check
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

s16 DLList::resize(const u16 new_size)
{
  if (new_size < length_) {
    return kErrorCode_Resize_Loss_Of_Data;
  }
  capacity_ = new_size;
  return kErrorCode_Ok;
}

u16 DLList::capacity() const
{
  return capacity_;
}

u16 DLList::length() const
{
  return length_;
}

bool DLList::length_debug() const
{
  MemoryNode *aux = first_;
  u16 elements_in_list = 0;
  while (aux->next() != nullptr) {
    aux = aux->next();
    elements_in_list++;
  }
  aux = last_;
  u16 inverse_elements_in_list = 0;
  while (aux->prev() != nullptr) {
    aux = aux->prev();
    inverse_elements_in_list++;
  }
  return elements_in_list == length_ &&
    inverse_elements_in_list == length_;
}

bool DLList::isEmpty() const
{
  return 0 == length_;
}

bool DLList::isFull() const
{
  if (0 == capacity_) return false;
  return length_ == capacity_;
}

void* DLList::head()
{
  if (isEmpty()) {
    return nullptr;
  }
  return first_->data();
}

void* DLList::last()
{
  if (isEmpty()) {
    return nullptr;
  }
  return last_->data();
}

MemoryNode* DLList::getNodeAtPosition(const u16 position) const
{
  u16 index;
  MemoryNode *aux = nullptr;
  // we divide by two our position to know if the index
  // is closest to the last or the first node
  if (position > length_ >> 1)
  {
    index = length_ - 1;
    aux = last_;
    while (index != position) {
      aux = aux->prev();
      --index;
    }
  }
  else
  {
    index = 0;
    aux = first_;
    while (index != position) {
      aux = aux->next();
      ++index;
    }
  }
  assert(aux != nullptr && "getNodeAtPosition: the node wasn't found DANGER!");
  return aux;
}


void* DLList::at(const u16 position)
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
  //if (position == length_ - 1) {
  //  return last_->data();
  //}
  //u16 index;
  //MemoryNode *aux;
  //// we divide by two our position to know if the index
  //// is closest to the last or the first node
  //if(position > ceil(position>>1)) 
  //{
  //  index = length_-1;
  //  aux = last_;
  //  while (index != position) {
  //    aux = aux->prev();
  //    --index;
  //  }
  //}else
  //{
  //  index = 0;
  //  aux = first_;
  //  while (index != position) {
  //    aux = aux->next();
  //    ++index;
  //  }
  //}
  //return aux->data();
  return getNodeAtPosition(position)->data();
}

s16 DLList::insertFirst(void* data, const u16 data_size)
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
    return kErrorCode_DLList_Is_Full;
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
  if (nullptr != first_) {
    first_->setPrev(new_node);
  }
  first_ = new_node;
  ++length_;
  const s16 status = first_->memCopy(data, data_size);
  return status;
}

s16 DLList::insertLast(void* data, const u16 data_size)
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
    return kErrorCode_DLList_Is_Full;
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
  new_node->setPrev(last_);
  last_ = new_node;
  ++length_;
  const s16 status = last_->memCopy(data, data_size);
  return status;
}

s16 DLList::insertAt(void* data, const u16 position, const u16 data_size)
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
    return kErrorCode_DLList_Is_Full;
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
  //MemoryNode *aux = first_;
  //u16 index = 0;
  ////We wish to found the node previous to the position we want to insert
  //while (index != position - 1) {
  //  aux = aux->next(aux);
  //  ++index;
  //}
  //We wish to found the node previous to the position we want to insert
  MemoryNode *aux = getNodeAtPosition(position - 1);
  new_node->setNext(aux->next());
  new_node->setPrev(aux);
  //First of all we update the previous of the node after the one we are
  //inserting
  aux->next()->setPrev(new_node);
  //aux->setPrev(aux->next(aux), new_node);
  aux->setNext(new_node);
  ++length_;
  status = new_node->memCopy(data, data_size);
  return status;
}

void* DLList::extractFirst()
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
  if (nullptr == first_) {
    last_ = nullptr;
  }
  else {
    first_->setPrev(nullptr);
  }
  //We free the node without affecting it's data
  node_to_extract->free_mn(true);
  --length_;
  return data;
}

void* DLList::extractLast()
{
  if (isEmpty()) {
#ifdef VERBOSE_
    printf("Error: [%s] The list is empty\n", __FUNCTION__);
#endif
    return nullptr;
  }
  MemoryNode *node_to_extract = last_;
  last_ = node_to_extract->prev();

  if (nullptr == last_) {//In case case tere was just an element
    first_ = nullptr;
  }
  else {
    last_->setNext(nullptr);
  }
  void* data = node_to_extract->data();
  node_to_extract->free_mn(true);
  --length_;
  return data;
}

void* DLList::extractAt(const u16 position)
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
  if (0 == position) { //Extraction at the start
    data = extractFirst();
    return data;
  }
  else if (position == length_ - 1) { //Extraction at the end
    data = extractLast();
    return data;
  }
  //MemoryNode *node_to_extract = nullptr;
  //MemoryNode *aux = first_;
  //u16 index = 0;
  ////We wish to found the node previous to the position we want to insert
  //while (index != position - 1) {
  //  aux = aux->next(aux);
  //  ++index;
  //}

  //We wish to found the node previous to the position we want to insert
  MemoryNode *node_to_extract = nullptr;
  MemoryNode *aux = getNodeAtPosition(position - 1);
  node_to_extract = aux->next();
  data = node_to_extract->data();
  aux->setNext(node_to_extract->next());
  node_to_extract->next()->setPrev(aux);
  //aux->setPrev(node_to_extract->next(node_to_extract), aux);
  node_to_extract->free_mn(true);
  --length_;
  return data;
}

s16 DLList::concat(DLList* src)
{  
  if (nullptr == src) {
#ifdef VERBOSE_ 
    printf("Error: [%s] The source list is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Reference_Received;
  }
  last_->setNext(src->first_);
  src->first_->setPrev(last_);
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

uint16_t DLList::traverse(s16(MemoryNode::*callback)()) const
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

void DLList::print() const
{
  if (nullptr == first_) {
    printf("EMPTY");
    return;
  }
  traverse(&MemoryNode::print);
}