// adt_queue.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_queue.h
#include <cstdio>
#include <cstdlib>

#include "common_def.h"
#include "printer.h"
#include <cstring>


Printer::Printer()
{
  const s16 status = init();
  if(kErrorCode_Ok != status)
  {
    delete(this);
  }
}

Printer::~Printer()
{
  delete(queue_);
  queue_ = nullptr;
}

s16 Printer::init()
{
  //We create an infinite queue
  queue_ = new Queue(0);
  if (nullptr == queue_) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Error_Trying_To_Allocate_Memory;
  }
  return kErrorCode_Ok;
}

int_least16_t Printer::clear()
{
  return queue_->reset();
}


s16 Printer::write(const char* message)
{
  if(nullptr == message)
  {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Null_Pointer_Parameter_Received;
  }
  queue_->enqueue((void*)message, static_cast<u16>(strlen(message)) + 1);
  return kErrorCode_Ok;
}

void Printer::flush() const
{
  while (!queue_->isEmpty()) {
    printf(static_cast<char const *>(queue_->dequeue()));
    printf("\n");
  }
}