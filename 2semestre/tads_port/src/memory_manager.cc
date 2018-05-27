// memory_node.c : 
// Toni Barella
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at memory_node.h
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include "memory_manager.h"
#include "common_def.h"


MemoryManager::MemoryManager()
{
  init();
}

MemoryManager::~MemoryManager()
{
  clear_memory();
  delete(sixteenb_nodes_);
  delete(sixtyfourb_nodes_);
  delete(thirtytwob_nodes_);
}

MemoryManager& MemoryManager::instance()
{
  static MemoryManager pinstance;
  return pinstance;
}

s16 MemoryManager::init()
{
  //used_nodes_ = new List(0);
  sixteenb_nodes_ = new List(initial_capacity_sixteen_);
  thirtytwob_nodes_ = new List(initial_capacity_thirtytwo_);
  sixtyfourb_nodes_ = new List(initial_capacity_sixtyfour_);
  char data[64];
  memset(data, 0, sizeof(data));
  s16 status = kErrorCode_Ok;
  for(u16 i = 0; i<initial_capacity_sixteen_; i++)
  {
    status = sixteenb_nodes_->insertFirst(data, 16);
    //TODO maybe it can be outside of the fors and checked only one time
    //best option?
    if(status != kErrorCode_Ok)
    {
      clear_memory();
      return kErrorCode_Error_Trying_To_Allocate_Memory;
    }
  }
  for (u16 i = 0; i<initial_capacity_thirtytwo_; i++)
  {
    status = thirtytwob_nodes_->insertFirst(data, 32);
    if (status != kErrorCode_Ok)
    {
      clear_memory();
      return kErrorCode_Error_Trying_To_Allocate_Memory;
    }
  }
  for (u16 i = 0; i<initial_capacity_sixtyfour_; i++)
  {
    status = sixtyfourb_nodes_->insertFirst(data, 64);
    if (status != kErrorCode_Ok)
    {
      clear_memory();
      return kErrorCode_Error_Trying_To_Allocate_Memory;
    }
  }
  return kErrorCode_Ok;
}

void* MemoryManager::malloc(u16 size) const
{
  //TODO the memory manager should allocate more memory
  //once it has no more available of that size, right now it will
  //return nullptr
  if(size <= 16)
  {
    return sixteenb_nodes_->extractFirst();
  }else if(size <= 32)
  {
    return thirtytwob_nodes_->extractFirst();
  }else if(size <= 64)
  {
    return sixtyfourb_nodes_->extractFirst();
  }
  return nullptr;
}

s16 MemoryManager::free(void* p, u16 size)
{
  s16 status = kErrorCode_Ok;
  if (size <= 16)
  {
    status = sixteenb_nodes_->insertFirst(p, 16);
  }
  else if (size <= 32)
  {
    status = thirtytwob_nodes_->insertFirst(p, 16);
  }
  else if (size <= 64)
  {
    status = sixtyfourb_nodes_->insertFirst(p, 16);
  }else
  {
    assert(false, "the memory manager didn't allocate that size");
  }
  return status;
}


s16 MemoryManager::clear_memory()
{
  sixteenb_nodes_->reset();
  thirtytwob_nodes_->reset();
  sixtyfourb_nodes_->reset();
  return kErrorCode_Ok;
}
