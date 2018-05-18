// adt_vector.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_vector.h
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "adt_vector.h"
#include "common_def.h"

Vector::Vector(u16 capacity)
{
  //Vector *vector = malloc(sizeof(Vector));
  storage_ = static_cast<MemoryNode*>(malloc(sizeof(MemoryNode) * capacity));
  if (nullptr == storage_) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    delete(this);
    return;
  }
  init(capacity);
}

Vector::~Vector()
{
  //We don't need to check if the pointer to vecotr is null as reset will do it
  const s16 status = reset();
  //We check if all went well and free the vector in case it was
  if (kErrorCode_Ok == status) {
    free(storage_);
  }
}

Vector::Vector(const Vector& o)
{
  concat(o);
  //head_ = o.head_;
  //tail_ = o.tail_;
  //capacity_ = o.capacity();  
}

Vector& Vector::operator=(const Vector& v)
{
  concat(v);
  //head_ = v.head_;
  //tail_ = v.tail_;
  //capacity_ = v.capacity();  
  return *this;
}


s16 Vector::init(const u16 capacity)
{
  //This function will only by called from Create so we don't need to check
  //the pointer.
  head_ = 0;
  tail_ = 0;
  capacity_ = capacity;
  //We initialize the nodes of our storage
  traverse(&MemoryNode::init);
  return kErrorCode_Ok;
}

s16 Vector::reset()
{
  traverse(&MemoryNode::reset);
  head_ = 0;
  tail_ = 0;
  return kErrorCode_Ok;
}

s16 Vector::resize(const u16 new_size)
{
  const u16 old_capacity = capacity_;
  //In case the new size is the same as the actual capacity we have finished
  if (new_size == old_capacity) {
    return kErrorCode_Ok;
  }
  MemoryNode *new_storage = static_cast<MemoryNode*>(malloc(sizeof(MemoryNode) * new_size));
  if (nullptr == new_storage) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }

  MemoryNode *old_storage = storage_;

  storage_ = new_storage;
  capacity_ = new_size;

  //We initialize the memnodes of the new vector
  traverse(&MemoryNode::init);
  if (new_size > old_capacity) {
    memcpy(new_storage, old_storage, sizeof(MemoryNode)*old_capacity);
  }
  else if (new_size < old_capacity) {
    if (length()>= new_size) {
      memcpy(new_storage, old_storage + head_,
        sizeof(MemoryNode)*new_size);
      if (length()>new_size) { //we need to free the remaining data
        for (u16 i = head_ + new_size; i < old_capacity; ++i) {
          (old_storage+i)->reset();
        }
      }
      head_ = 0;
      tail_ = new_size;
    }
    else {
      memcpy(new_storage, old_storage + head_,
        sizeof(MemoryNode)*length());
        tail_ = length();
      head_ = 0;
    }
  }
  free(old_storage);
  return kErrorCode_Ok;
}

u16 Vector::capacity() const
{
  return capacity_;
}

u16 Vector::length() const
{
  return tail_ - head_;
}

boolean Vector::isEmpty() const
{
  return 0 == length();
}

boolean Vector::isFull() const
{
  return length() == capacity_;
}

void* Vector::head()
{
  MemoryNode *aux = storage_ + head_;
  return aux->data();
}

void* Vector::last()
{
  MemoryNode *aux = storage_ + (tail_ - 1);
  return aux->data();
}

void* Vector::at(const u16 position)
{
  if (isEmpty()) {
    return nullptr;
  }
  if (position >= length()) {
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return nullptr;
  }
  MemoryNode *aux = storage_ + (head_ + position);
  return aux->data();
}

s16 Vector::insertFirst(void* data, const u16 data_size)
{
  if (nullptr == data) {
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if (isFull()) {
#ifdef VERBOSE_
    printf("Error: [%s] The vector is full\n", __FUNCTION__);
#endif
    return kErrorCode_Vector_Is_Full;
  }
  if (isEmpty()) {//is empty so we just need to update the tail
    ++tail_;
  }
  else if (head_ > 0) { //we don't need to move the content
    --head_;
  }
  else { //the head is at the first position so we need to move the elements
    memmove(storage_ + 1, storage_,
      sizeof(MemoryNode)*length());
    //As the elements were moved one position to the right the tail needs to 
    //be updated
    ++tail_;
  }
  MemoryNode *aux = storage_ + head_;
  s16 status = aux->init();
  //status = aux->ops_->setData(aux, data, data_size);
  status = aux->memCopy(data, data_size);
  return status;
}

s16 Vector::insertLast(void* data, const u16 data_size)
{
  if (nullptr == data) {
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if (isFull()) {
#ifdef VERBOSE_
    printf("Error: [%s] The vector is full\n", __FUNCTION__);
#endif
    return kErrorCode_Vector_Is_Full;
  }

  //As we know the vector is not full if the tail is equal to capacity
  //we have free space at the front
  if (tail_ == capacity_) {
    memmove(storage_ + head_ - 1,
      storage_ + head_,
      sizeof(MemoryNode)*length());
    --head_;
  }
  else {//Tail is pointing to the next free node we increase the tail
    ++tail_;
  }
  MemoryNode *aux = storage_ + (tail_ - 1);
  s16 status = aux->init();
  status = aux->memCopy(data, data_size);
  return status;
}

s16 Vector::insertAt(void* data, const u16 data_size, const u16 position)
{
  if (nullptr == data) {
#ifdef VERBOSE_
    printf("Error: [%s] the data passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if (isFull()) {
#ifdef VERBOSE_
    printf("Error: [%s] The vector is full\n", __FUNCTION__);
#endif
    return kErrorCode_Vector_Is_Full;
  }
  if (position > length()) {
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return kErrorCode_Out_Of_Range_Index;
  }

  s16 status;

  if (0 == position) { //Insertion at the start
    status = insertFirst(data, data_size);
    return status;
  }
  else if (position == length()) { //Insertion at the end
    status = insertLast(data, data_size);
    return status;
    //we don't have space at the end
  }
  else if (tail_ == capacity_) {
    memmove(storage_ + (head_ - 1),
      storage_ + head_,
      sizeof(MemoryNode)* position);
    --head_;
  }
  else { //We can move to the right as we have space at the end
    memmove(storage_ + (head_ + position + 1),
      storage_ + (head_ + position),
      sizeof(MemoryNode)* (length() - position));
    ++tail_;
  }
  MemoryNode *aux = storage_ + position;
  //we initialize the memory node before doing the memcopy
  status = aux->init();
  status = aux->memCopy(data, data_size);
  return status;
}

void* Vector::extractFirst()
{
  if (isEmpty()) {
    return nullptr;
  }
  MemoryNode *aux = storage_ + head_;
  void *data = aux->data();
  const s16 status = aux->init();
  if (kErrorCode_Null_Pointer_Reference_Received == status) {
#ifdef VERBOSE_
    printf("Error: [%s] Strange behaviour, please inform us\n", __FUNCTION__);
#endif
    return nullptr;
  }
  if (1 != length()) {
    //If there's more than one element, we want to increase the head after the
    //extraction, the length can't be 0 as we checked the vector is not empty 
    //At the start
    ++head_;
  }
  else {
    //If there's just one element we want to decrease the tail after the
    //extraction
    --tail_;
  }
  return data;
}

void* Vector::extractLast()
{
  if (isEmpty()) {
    return nullptr;
  }
  MemoryNode *aux = storage_ + (tail_ - 1);
  void *data = aux->data();
  s16 status = aux->init();
  if (kErrorCode_Null_Pointer_Reference_Received == status) {
#ifdef VERBOSE_
    printf("Error: [%s] Strange behaviour, please inform us\n", __FUNCTION__);
#endif
    return NULL;
  }
  --tail_;
  return data;
}

void* Vector::extractAt(const u16 position)
{
  if (isEmpty()) {
#ifdef VERBOSE_
    printf("Error: [%s] The vector is empty\n", __FUNCTION__);
#endif
    return nullptr;
  }
  if (position >= length()) {
#ifdef VERBOSE_
    printf("Error: [%s] Index out of range\n", __FUNCTION__);
#endif
    return nullptr;
  }

  if (0 == position) { //extraction of the first element
    return extractFirst();
  }
  else if (position == length() - 1) { //Extraction at the end
    return extractLast();
  }
  else {
    MemoryNode *aux = storage_ + (head_ + position);
    void *data = aux->data();
    memmove(storage_ + (head_ + position),
      storage_ + (head_ + position + 1),
      sizeof(MemoryNode)* (length() - (position + 1)));
    //We have shifted the data to the left, so we need to initialize the last
    //element that will now be the new tail of the vector
    --tail_;
    aux = storage_ + tail_;
    const s16 status = aux->init();
    if (kErrorCode_Null_Pointer_Reference_Received == status) {
#ifdef VERBOSE_
      printf("Error:[%s] Strange behaviour, please inform us\n", __FUNCTION__);
#endif
      return nullptr;
    }
    return data;
  }
}

s16 Vector::concat(const Vector& src)
{
  const s16 status = resize(capacity_ + src.capacity_);

  if (kErrorCode_Ok != status) {
    return status;
  }

  for (u16 i = 0; i < src.length(); ++i) {
    insertLast((src.storage_ + i)->data(),
      (src.storage_ + i)->size());
  }

  return kErrorCode_Ok;
}

u16 Vector::traverse(s16(MemoryNode::*callback)()) const
{
	MemoryNode *aux = storage_;
	u16 i;
	for (i = 0; i< capacity_; i++) {
    (*aux.*callback)();
		++aux;
	}
	return i;
}

void Vector::print() const
{
  traverse(&MemoryNode::print);
}
