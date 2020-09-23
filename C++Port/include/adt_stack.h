// adt_Stack.h
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Header for our abstract data type Stack
//
#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__

#include "adt_vector.h"

//typedef struct adt_Stack_s
//{
//  Vector *vector_;
//  struct adt_stack_ops_s *ops_;
//} Stack;

class Stack
{
 public:
   /** @brief Stack constructor
   *
   * Base constructor of Stack
   *
   * @parameter capacity capacity of the stack we are creating
   * @return *Stack
   */
   Stack(const u16 capacity);
   /** @brief Stack constructor
   *
   * Creates an stack using a vector as reference
   *
   ** @parameter v vector we use as reference to create an stack
   * @return *Stack
   */
   Stack(const Vector& v);
   /** @brief Frees the Stack
   *
   * Resets the content of the Stack and frees it. Note that this function
   * calls the reset method.
   *
   * @return void
   */
   ~Stack();
  /** @brief stack copy constructor
   *
   * stack copy constructor.
   *
   * @return *stack
   * @param o stack to be copied
   */
   Stack(const Stack& o);
   /** @brief stack = operation
   *
   * returns a reference to stack equal to s
   *
   * @return &Stack
   * @param s vector to be copied
   */
   Stack& operator = (const Stack &s);
   // Internal storage management
   /** @brief Resets the stack
   *
   * Frees the elements of the stack, using the reset method of memory node,
   * and sets the values of the stack to it's default.
   *
   * @return s16 ErrorCode of the execution
   */
   s16 reset();
   /** @brief Changes the capacity of the Stack
   *
   * Adjusts the capacity of the Stack so it can store more elements. If the new
   * size causes a loss of data the function will return an error. Note that a
   * capacity of 0 is an infinite capacity
   *
   * @return s16 ErrorCode of the execution
   * @param new_size new size for the Stack
   */
   s16 resize(u16 new_size);
   // State queries
   /** @brief getter of capacity
   *
   * Returns the maximum number of elemets that can be stored at the Stack.
   *
   * @return u16 capacity of the Stack   
   */
   u16 capacity() const;
   /** @brief getter of the length
   *
   * Returns the current number of elements (<= capacity)
   *
   * @return u16 length of the Stack
   */
   u16 length() const;
   /** @brief Indicates if the Stack is empty
   *
   * Indicates if the Stack is empty
   *
   * @return bool true if the Stack is empty false otherwise
   */
   bool isEmpty() const;
   /** @brief Indicates if the Stack is full
   *
   * Indicates if the Stack is full
   *
   * @return bool true if the Stack is full false otherwise
   */
   bool isFull() const;
   // Data queries
   /** TODO change description @brief Returns the first element of the Stack
   *
   * Returns a reference to the first element. If the Stack passed is NULL or the
   * Stack is empty returns null.
   *
   * @return void* first element of the Stack
   */
   void* first();
   // Insertion
   /** TODO change description
   @brief Inserts the data at the first position of the Stack
   *
   * Inserts the data at the first position of the Stack and returns the status
   * depending of the result. In case the Stack is full a
   * kErrorCode_Stack_Is_Full is returned, if the Stack is null
   * kErrorCode_Null_Stack and in case the the data is null
   * kErrorCode_Null_Data. The Stack makes a copy of the data so the value
   * you store will not be touched unless you modify it through the Stack.
   *
   * @return s16 status of the operation once finished
   * @param data data we wish to store at the position
   * @param data_size size of the data we wish to store
   */
   s16 push(void *data, u16 data_size);
   // Extraction
   /** TODO change description
   @brief Extracts the first element of the Stack and returns it
   *
   * Extracts the first element of the Stack and removes it.
   * Notice that the data must be freed once you are finished using it as it's
   * no longer responsability of the Stack.
   *
   * @return void* data at the first position of the Stack
   */
   void* pop();
   // Miscellaneous
   /** @brief Concatenates two Stack storing the result at origin
   *
   * Concatenates the source to the Stack, in case one of the Stack has infinite
   * capacity the result Stack will have infinite capacity, otherwise it will be
   * the result of both capacities added. Notice that the src
   * Stack won't be modified during the execution. In case the Stack is null
   * kErrorCode_Null_Stack will be returned and in case the the src is null
   * kErrorCode_Null_Pointer_Parameter_Received. If there's a problem during
   * the allocation of the new Stack kErrorCode_Error_Trying_To_Allocate_Memory
   * will be returned.
   *
   * @return s16 status of the operation once finished
   * concatenation
   * @param src Stack we want to concatenate to our origin
   */
   s16 concat(const Stack& src);
   /** @brief Applies the callback method to the Stack
   *
   * Applies a memory node function to the set of elements of the Stack.
   *
   * @return u16 number of elements traveled
   * @param callback function of memory node that will be applied to the set
   */
   u16 traverse(s16(MemoryNode::*callback)()) const;
   /** @brief Prints the content of the elements of the Stack
   *
   * Prints the content of the elements of the Stack
   *
   */
   void print() const;

 private:
   Vector *vector_;

   /** @brief Initializes the Stack
   *
   * Initializes the Stack, this method must only be called from Create
   * as it will assume the pointer passed to it is a valid one created by
   * the Create functionality.
   *
   * @return s16 ErrorCode of the execution
   * @param *Stack pointer to the Stack we wish to initialize
   * @param capacity number of elements that the Stack can store note that a
   * value of 0 will imply that it has an infinite capacity
   */
   s16 init(u16 capacity);

};

#endif //__ADT_Stack_H__