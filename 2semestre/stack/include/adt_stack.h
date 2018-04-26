// adt_queue.h
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Header for our abstract data type stack
//
#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__

#include "adt_vector.h"

typedef struct adt_stack_s
{
  Vector *vector_;
  struct adt_stack_ops_s *ops_;
} Stack;

struct adt_stack_ops_s
{
  // Internal storage management
  /** @brief Initializes the stack
  *
  * Initializes the stack, this method must only be called from Create
  * as it will assume the pointer passed to it is a valid one created by
  * the Create functionality.
  *
  * @return s16 ErrorCode of the execution
  * @param *stack pointer to the stack we wish to initialize
  * @param capacity number of elements that the stack can store note that a 
  * value of 0 will imply that it has an infinite capacity
  */
  //s16 (*init) (Stack *stack, u16 capacity);
  /** @brief Destroys the stack and it's data
  *
  * Destroys the stack and its data. Note that this function calls the reset
  * method. In case the direction to the pointer is null it will return a
  * kErrorCode_Null_Pointer_Reference_Received. If the execution went well this
  * function assures that the pointer to stack ends as NULL
  *
  * @return s16 ErrorCode of the execution
  * @param **stack direction to the pointer of the stack we want to destroy
  */
  s16(*destroy) (Stack **stack);
  /** @brief Resets the stack
  *
  * Frees the elements of the stack, using the reset method of memory node,
  * and sets the values of the stack to it's default. In case a null pointer
  * was passed it will return a kErrorCode_Null_Queue
  *
  * @return s16 ErrorCode of the execution
  * @param *stack pointer to the stack we wish to reset
  */
  s16 (*reset) (Stack *stack);
  /** @brief Changes the capacity of the stack
  *
  * Adjusts the capacity of the stack so it can store more elements. If the new
  * size causes a loss of data the function will return an error. Note that a 
  * capacity of 0 is an infinite capacity
  *
  * @return s16 ErrorCode of the execution
  * @param *stack pointer to the stack we wish to resuze
  * @param new_size new size for the stack
  */
  s16 (*resize)(Stack *stack, u16 new_size);
  // State queries
  /** @brief getter of capacity
  *
  * Returns the maximum number of elemets that can be stored at the stack.
  *
  * @return u16 capacity of the stack
  * @param *stack pointer to the stack we wish to get the capacity
  */
  u16 (*capacity)(Stack *stack);
  /** @brief getter of the length
  *
  * Returns the current number of elements (<= capacity)
  *
  * @return u16 length of the stack
  * @param *stack pointer to the stack we wish to get the length
  */
  u16 (*length)(Stack *stack);
  /** @brief Indicates if the stack is empty
  *
  * Indicates if the stack is empty
  *
  * @return bool true if the stack is empty false otherwise
  * @param *stack pointer to the stack
  */
  bool (*isEmpty) (Stack *stack);
  /** @brief Indicates if the stack is full
  *
  * Indicates if the stack is full
  *
  * @return bool true if the stack is full false otherwise
  * @param *stack pointer to the stack
  */
  bool (*isFull) (Stack *stack);
  // Data queries
  /** TODO change description @brief Returns the first element of the stack
  *
  * Returns a reference to the first node. If the stack passed is NULL or the
  * stack is empty returns null.
  *
  * @return void* first element of the stack
  * @param *stack pointer to the stack
  */
  void* (*first)(Stack *stack);
  // Insertion
  /** TODO change description
  @brief Inserts the data at the first position of the stack
  *
  * Inserts the data at the first position of the stack and returns the status
  * depending of the result. In case the stack is full a
  * kErrorCode_Queue_Is_Full is returned, if the stack is null 
  * kErrorCode_Null_Queue and in case the the data is null
  * kErrorCode_Null_Data. The stack makes a copy of the data so the value
  * you store will not be touched unless you modify it through the stack.
  *
  * @return s16 status of the operation once finished
  * @param *stack pointer to the stack
  * @param *data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16 (*push) (Stack *stack, void *data, u16 data_size);
  // Extraction
  /** TODO change description
  @brief Extracts the first element of the stack and returns it
  *
  * Extracts the first element of the stack and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the stack.
  *
  * @return void* data at the first position of the stack
  * @param *stack pointer to the stack
  */
  void* (*pop) (Stack *stack);
  // Miscellaneous
  /** @brief Concatenates two stack storing the result at origin
  *
  * Concatenates the source to the stack, in case one of the stack has infinite
  * capacity the result stack will have infinite capacity, otherwise it will be
  * the result of both capacities added. Notice that the src
  * stack won't be modified during the execution. In case the stack is null 
  * kErrorCode_Null_Queue will be returned and in case the the src is null
  * kErrorCode_Null_Pointer_Parameter_Received. If there's a problem during
  * the allocation of the new stack kErrorCode_Error_Trying_To_Allocate_Memory
  * will be returned.
  *
  * @return s16 status of the operation once finished
  * @param *stack pointer to the stack that will store the result of the
  * concatenation
  * @param *src stack we want to concatenate to our origin             
  */
  s16(*concat) (Stack *stack, Stack *src);
  /** @brief Applies the callback method to the stack
  *
  * Applies a memory node function to the set of elements of the stack.
  *
  * @return u16 number of elements traveled
  * @param *stack pointer to the stack
  * @param *callback function of memory node that will be applied to the set
  */
  u16 (*traverse)(Stack *stack, void(*callback) (MemoryNode *));
  /** @brief Prints the content of the elements of the stack
  *
  * Prints the content of the elements of the stack
  *
  * @param *stack pointer to the stack
  */
  void(*print)(Stack *stack);
};
/** @brief Create a Stack
*
* Initializes a new Stack allocating memory for it and it's storage.
* If the allocation of memory fails returns a NULL and if everything went well
* returns the pointer to the memory node. Note that a capacity of 0 is an
* infinite capacity
*
* @return Stack* pointer to the stack
*/
Stack* STACK_Create(u16 capacity);
#endif //__ADT_STACK_H__