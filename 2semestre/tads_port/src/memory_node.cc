// memory_node.c : 
// Toni Barella
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at memory_node.h
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "memory_node.h"
#include "common_def.h"

MemoryNode::MemoryNode()
{
  init();
}

MemoryNode::~MemoryNode()
{
  //reset();
}

MemoryNode::MemoryNode(const MemoryNode& o)
{
  size_ = o.size();
  setData(o.data(), o.size());
}

MemoryNode& MemoryNode::operator=(const MemoryNode& mn)
{
  size_ = mn.size();
  setData(mn.data(), mn.size());
  return *this;
}


s16 MemoryNode::init()
{
  data_ = nullptr;
  size_ = 0;    
  next_ = nullptr;
  prev_ = nullptr;
  return kErrorCode_Ok;
}

s16 MemoryNode::free_mn(boolean soft)
{
  if (!soft) reset();
  delete(this);
  return kErrorCode_Ok;
}


s16 MemoryNode::reset()
{
  size_ = 0;
  if(nullptr == data_){
    return kErrorCode_Ok;
  }
  free(data_);
  data_ = nullptr;
  next_ = nullptr;
  prev_ = nullptr;
  return kErrorCode_Ok;
}

void* MemoryNode::data() const
{
  return data_;
}

u16 MemoryNode::size() const
{
  return size_;
}

MemoryNode* MemoryNode::next() const
{
  return next_;
}

s16 MemoryNode::setNext(MemoryNode* next_node)
{
  next_ = next_node;
  return kErrorCode_Ok;
}

MemoryNode* MemoryNode::prev() const
{
  return prev_;
}

s16 MemoryNode::setPrev(MemoryNode* prev_node)
{
  prev_ = prev_node;
  return kErrorCode_Ok;
}

s16 MemoryNode::setData(void* src, u16 bytes)
{
  if (nullptr == src) {
#ifdef VERBOSE_
    printf("Warning: [%s] The data passed is null\n", __FUNCTION__);
#endif
    return kWarningCode_Strange_Operation;
  }
  const s16 status = reset();
  if (kErrorCode_Ok != status) {
#ifdef VERBOSE_
    printf("Error: [%s] Error reseting the data\n", __FUNCTION__);
#endif
    return status;
  }
  size_ = bytes;
  data_ = src;
  return kErrorCode_Ok;
}

s16 MemoryNode::memSet(u8 value)
{
  if (nullptr == data_) {
#ifdef VERBOSE_
    printf("Error: [%s] Trying to do a memset to null data\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  memset(data_, static_cast<s16>(value), size_);
  return kErrorCode_Ok;
}

s16 MemoryNode::memCopy(void* src, u16 bytes)
{
  //We want to make sure the size of the new data to copy is greater than 0
  //before anything else
  if (0 == bytes) {
#ifdef VERBOSE_
    printf("Warning: [%s] Asking to do a memcopy of 0 bytes\n", __FUNCTION__);
#endif
    return kWarningCode_Strange_Operation;
  }

  if (nullptr == src) {
#ifdef VERBOSE_
    printf("Error: [%s] the src passed is null\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Parameter_Received;
  }

  const s16 status = reset();
  if (kErrorCode_Null_Memory_Node == status) {
#ifdef VERBOSE_
    printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
    return status;
  }
  data_ = malloc(bytes);
  if (nullptr == data_) {
#ifdef VERBOSE_
    printf("Error: [%s] malloc failed\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  memcpy(data_, src, bytes);
  size_ = bytes;
  return kErrorCode_Ok;
}

s16 MemoryNode::memConcat(void* src, u16 bytes)
{
  if (nullptr == data_) {
#ifdef VERBOSE_
    printf("Error: [%s] Trying to concat with null data\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Data;
  }
  if (nullptr == src) {
#ifdef VERBOSE_
    printf("Warning: [%s] Trying to concat with null source\n", __FUNCTION__);
#endif
    return kWarningCode_Strange_Operation;
  }
  u8 *aux = static_cast<u8*>(malloc(size_ + bytes));
  if (nullptr == aux) {
#ifdef VERBOSE_
    printf("Error: [%s] malloc failed\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  memcpy(aux, data_, size_);
  memcpy(aux + (size_), src, bytes);
  //We have already checked that data is not null.
  free(data_);
  data_ = aux;
  size_ = size_ + bytes;
  return kErrorCode_Ok;
}

s16 MemoryNode::memMask(u8 mask) const
{
  u8 *aux = static_cast<u8*>(data_);
  for (u16 i = 0; i < size_; ++i) {
    aux[i] &= mask;
  }
  return kErrorCode_Ok;
}

s16 MemoryNode::print()
{
  if (nullptr == data_) {
    printf("Nothing\n");
    return kErrorCode_Ok;
  }
  u8 *aux = static_cast<u8*>(data_);
  for (u16 i = 0; i < size_; ++i) {
    printf("%c", aux[i]);
  }
  printf("\n");
  return kErrorCode_Ok;
}