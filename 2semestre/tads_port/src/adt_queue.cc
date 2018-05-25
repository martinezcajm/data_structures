// adt_queue.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_queue.h
#include <cstdio>
#include <cstdlib>

#include "adt_queue.h"
#include "common_def.h"


Queue::Queue(const u16 capacity)
{
  const s16 status = init(capacity);
  if(kErrorCode_Ok != status)
  {
    delete(this);
  }
}

Queue::~Queue()
{
  delete(list_);
  list_ = nullptr;
}

s16 Queue::init(u16 capacity)
{
  list_ = new List(capacity);
  if (nullptr == list_) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  return kErrorCode_Ok;
}

int_least16_t Queue::reset()
{  
  return list_->reset();
}

int_least16_t Queue::resize(u16 new_size)
{
  const s16 status = list_->resize(new_size);
  return status;
}

uint16_t Queue::capacity() const
{
  return list_->capacity();
}

uint16_t Queue::length() const
{
  return list_->length();
}

bool Queue::length_debug() const
{
  return list_->length_debug();
}

bool Queue::isEmpty() const
{
  return list_->isEmpty();
}

bool Queue::isFull() const
{
  return list_->isFull();
}

void* Queue::first()
{
  return list_->head();
}

void* Queue::last()
{
  return list_->last();
}

int_least16_t Queue::enqueue(void* data, u16 data_size)
{
  //insertLast already checks data and if it's full
  return list_->insertLast(data, data_size);
}

void* Queue::dequeue()
{
  return list_->extractFirst();
}

int_least16_t Queue::concat(Queue* src)
{
  return list_->concat(src->list_);
}

uint16_t Queue::traverse(s16 ( MemoryNode::* callback)()) const
{
  return list_->traverse(callback);
}

void Queue::print() const
{
  list_->print();
}