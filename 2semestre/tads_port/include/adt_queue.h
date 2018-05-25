// adt_queue.h
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Header for our abstract data type queue
//
#ifndef __ADT_QUEUE_H__
#define __ADT_QUEUE_H__

#include "adt_list.h"

//typedef struct adt_queue_s
//{
//  List *list_;
//  struct adt_queue_ops_s *ops_;
//} Queue;

class Queue
{
 public:
   /** @brief Queue constructor
   *
   * Base constructor of Queue
   *
   * @return *List
   */
   Queue(const u16 capacity);
   // TODO Queue(List l);
   /** @brief Frees the Queue
   *
   * Resets the content of the Queue and frees it. Note that this function
   * calls the reset method.
   *
   * @return void
   */
   ~Queue();
   /*TODO
   Queue(const Queue& o);*/
   /*TODO
   Queue& operator = (const Queue &l);*/
   // Internal storage management
   /** @brief Resets the queue
   *
   * Frees the elements of the queue, using the reset method of memory node,
   * and sets the values of the queue to it's default. In case a null pointer
   * was passed it will return a kErrorCode_Null_Queue
   *
   * @return s16 ErrorCode of the execution  
   */
   s16 reset();
   /** @brief Changes the capacity of the queue
   *
   * Adjusts the capacity of the queue so it can store more elements. If the new
   * size causes a loss of data the function will return an error. Note that a
   * capacity of 0 is an infinite capacity
   *
   * @return s16 ErrorCode of the execution
   * @param *queue pointer to the queue we wish to resuze
   * @param new_size new size for the queue
   */
   s16 resize(u16 new_size);
   // State queries
   /** @brief getter of capacity
   *
   * Returns the maximum number of elemets that can be stored at the queue.
   *
   * @return u16 capacity of the queue   
   */
   u16 capacity() const;
   /** @brief getter of the length
   *
   * Returns the current number of elements (<= capacity)
   *
   * @return u16 length of the queue
   */
   u16 length() const;
   /** @brief checks that the length of the queue is consistent
   *
   * Traverses the number of elements and checks its result with its own lenght
   *
   * @return bool   
   */
   bool length_debug() const;
   /** @brief Indicates if the queue is empty
   *
   * Indicates if the queue is empty
   *
   * @return bool true if the queue is empty false otherwise
   */
   bool isEmpty() const;
   /** @brief Indicates if the queue is full
   *
   * Indicates if the queue is full
   *
   * @return bool true if the queue is full false otherwise
   */
   bool isFull() const;
   // Data queries
   /** TODO change description @brief Returns the first element of the queue
   *
   * Returns a reference to the first node. If the queue passed is NULL or the
   * queue is empty returns null.
   *
   * @return void* first element of the queue
   */
   void* first();
   /** @brief Returns the last element of the queue
   *
   * Returns a reference to the last node. If the queue passed is NULL or the
   * queue is empty returns null.
   *
   * @return void* last element of the queue
   */
   void* last();
   // Insertion
   /** TODO change description
   @brief Inserts the data at the first position of the queue
   *
   * Inserts the data at the first position of the queue and returns the status
   * depending of the result. In case the queue is full a
   * kErrorCode_Queue_Is_Full is returned, if the queue is null
   * kErrorCode_Null_Queue and in case the the data is null
   * kErrorCode_Null_Data. The queue makes a copy of the data so the value
   * you store will not be touched unless you modify it through the queue.
   *
   * @return s16 status of the operation once finished
   * @param data data we wish to store at the position
   * @param data_size size of the data we wish to store
   */
   s16 enqueue(void *data, u16 data_size);
   // Extraction
   /** TODO change description
   @brief Extracts the first element of the queue and returns it
   *
   * Extracts the first element of the queue and removes it.
   * Notice that the data must be freed once you are finished using it as it's
   * no longer responsability of the queue.
   *
   * @return void* data at the first position of the queue
   */
   void* dequeue();
   // Miscellaneous
   /** @brief Concatenates two queue storing the result at origin
   *
   * Concatenates the source to the queue, in case one of the queue has infinite
   * capacity the result queue will have infinite capacity, otherwise it will be
   * the result of both capacities added. Notice that the src
   * queue won't be modified during the execution. In case the queue is null
   * kErrorCode_Null_Queue will be returned and in case the the src is null
   * kErrorCode_Null_Pointer_Parameter_Received. If there's a problem during
   * the allocation of the new queue kErrorCode_Error_Trying_To_Allocate_Memory
   * will be returned.
   *
   * @return s16 status of the operation once finished
   * concatenation
   * @param src queue we want to concatenate to our origin
   */
   s16 concat(Queue *src);
   /** @brief Applies the callback method to the queue
   *
   * Applies a memory node function to the set of elements of the queue.
   *
   * @return u16 number of elements traveled
   * @param callback function of memory node that will be applied to the set
   */
   u16 traverse(s16(MemoryNode::*callback)()) const;
   /** @brief Prints the content of the elements of the queue
   *
   * Prints the content of the elements of the queue
   *
   */
   void print() const;

 private:
   List *list_;

   /** @brief Initializes the queue
   *
   * Initializes the queue, this method must only be called from Create
   * as it will assume the pointer passed to it is a valid one created by
   * the Create functionality.
   *
   * @return s16 ErrorCode of the execution
   * @param *queue pointer to the queue we wish to initialize
   * @param capacity number of elements that the queue can store note that a
   * value of 0 will imply that it has an infinite capacity
   */
   s16 init(u16 capacity);

};

#endif //__ADT_QUEUE_H__