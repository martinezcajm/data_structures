// adt_Stack.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_Stack.h
#include <cstdio>
#include <cstdlib>

#include "adt_Stack.h"
#include "common_def.h"


Stack::Stack(const u16 capacity)
{
  const s16 status = init(capacity);
  if(kErrorCode_Ok != status)
  {
    delete(this);
  }
}

Stack::Stack(const Vector& v)
{
  const s16 status = init(v.capacity());
  if (kErrorCode_Ok != status)
  {
    delete(this);
  }
  //if status kErrorCode_Ok the vector was created
  //successfully
  vector_->concat(v);
}


Stack::~Stack()
{
  delete(vector_);
  vector_ = nullptr;
}

Stack::Stack(const Stack& o)
{
  const s16 status = init(o.capacity());
  if (kErrorCode_Ok != status)
  {
    delete(this);
  }
  //if status kErrorCode_Ok the vector was created
  //successfully
  vector_->concat(*(o.vector_));
}

Stack& Stack::operator=(const Stack& s)
{
  const s16 status = init(s.capacity());
  if (kErrorCode_Ok != status)
  {
    delete(this);
  }
  //if status kErrorCode_Ok the vector was created
  //successfully
  vector_->concat(*(s.vector_));
  return *this;
}

s16 Stack::init(u16 capacity)
{
  vector_ = new Vector(capacity);
  if (nullptr == vector_) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  return kErrorCode_Ok;
}

s16 Stack::reset()
{  
  return vector_->reset();
}

s16 Stack::resize(u16 new_size)
{
  const s16 status = vector_->resize(new_size);
  return status;
}

u16 Stack::capacity() const
{
  return vector_->capacity();
}

u16 Stack::length() const
{
  return vector_->length();
}

bool Stack::isEmpty() const
{
  return vector_->isEmpty();
}

bool Stack::isFull() const
{
  return vector_->isFull();
}

void* Stack::first()
{
  return vector_->last();
}

s16 Stack::push(void* data, u16 data_size)
{
  //insertLast already checks data and if it's full
  return vector_->insertLast(data, data_size);
}

void* Stack::pop()
{
  return vector_->extractLast();
}

s16 Stack::concat(const Stack& src)
{
  return vector_->concat(*(src.vector_));
}

u16 Stack::traverse(s16 ( MemoryNode::* callback)()) const
{
  return vector_->traverse(callback);
}

void Stack::print() const
{
  vector_->print();
}