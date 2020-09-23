// adt_queue.h
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Header for our abstract data type queue
//
#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "adt_queue.h"

class Printer
{
 public:
   /** @brief Printer constructor
   *
   * Base constructor of Printer
   *
   * @return *Printer
   */
   Printer();
   /** @brief Frees the Printer
   *
   * Resets the content of the Printer and frees it.
   *
   * @return void
   */
   ~Printer();
   // Internal storage management
   /** @brief Clears the messages in the printer
   *
   * Clears the messages that the printer actually has.
   *
   * @return s16 ErrorCode of the execution  
   */
   s16 clear();
   /** @brief Changes the capacity of the queue
   *
   * Adjusts the capacity of the queue so it can store more elements. If the new
   * size causes a loss of data the function will return an error. Note that a
   * capacity of 0 is an infinite capacity
   *
   * @return s16 status of the execution
   * @param message new size for the queue
   */
   s16 write(const char* message);
   /** @brief Prints the messages stored
   *
   * Shows the stored messages, notice that the messages will be cleared once
   * extracted
   *
   */
   void flush() const;

 private:
   Queue *queue_;

   /** @brief Initializes the queue
   *
   * Initializes the queue with an infinite capacity. In case the allocation
   * of the que is not possible kErrorCode_Error_Trying_To_Allocate_Memory will
   * be returned.
   *
   * @return s16 ErrorCode of the execution
   */
   s16 init();

};

#endif //__PRINTER_H__