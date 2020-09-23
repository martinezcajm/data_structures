// adt_list.h
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Header for our abstract data type list
//
#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "platform_types.h"
#include "memory_node.h"

//typedef struct adt_list_s
//{
//  u16 capacity_;
//  u16 length_;
//  MemoryNode *first_;
//  MemoryNode *last_;
//  struct adt_list_ops_s *ops_;
//} List;

class List
{
 public:
   /** @brief List constructor
   *
   * Base constructor of list
   *
   * @return *List
   */
   List(u16 capacity);
   /** @brief Frees the List
   *
   * Resets the content of the List and frees it. Note that this function
   * calls the reset method.
   *
   * @return void
   */
   ~List();
   /*TODO 
   List(const List& o);*/
   /* TODO
   List& operator = (const List &l);*/
  // Internal storage management
  /** @brief Initializes the list
  *
  * Initializes the list, this method must only be called from Create
  * as it will assume the pointer passed to it is a valid one created by
  * the Create functionality.
  *
  * @return s16 ErrorCode of the execution
  * @param capacity number of elements that the list can store note that a 
  * value of 0 will imply that it has an infinite capacity
  */
  s16 init(const u16 capacity);
  /** @brief Destroys the list and it's data
  *
  * Destroys the list and its data. Note that this function calls the reset
  * method. In case the direction to the pointer is null it will return a
  * kErrorCode_Null_Pointer_Reference_Received. If the execution went well this
  * function assures that the pointer to list ends as NULL
  *
  * @return s16 ErrorCode of the execution
  */
  //s16 destroy();
  /** @brief Resets the list
  *
  * Frees the elements of the list, using the reset method of memory node,
  * and sets the values of the list to it's default. In case a null pointer
  * was passed it will return a kErrorCode_Null_List
  *
  * @return s16 ErrorCode of the execution
  */
  s16 reset();
  /** @brief Changes the capacity of the list
  *
  * Adjusts the capacity of the list so it can store more elements. If the new
  * size causes a loss of data the function will return an error. Note that a 
  * capacity of 0 is an infinite capacity
  *
  * @return s16 ErrorCode of the execution
  * @param new_size new size for the list
  */
  s16 resize(const u16 new_size);
  // State queries
  /** @brief getter of capacity
  *
  * Returns the maximum number of elemets that can be stored at the list.
  *
  * @return u16 capacity of the list
  */
  u16 capacity() const;
  /** @brief getter of the length
  *
  * Returns the current number of elements (<= capacity)
  *
  * @return u16 length of the list
  */
  u16 length() const;
  /** @brief checks that the length of the list is consistent
  *
  * Traverses the number of elements and checks its result with its own lenght
  *
  * @return bool 
  */
  bool length_debug() const;
  /** @brief Indicates if the list is empty
  *
  * Indicates if the list is empty
  *
  * @return bool true if the list is empty false otherwise
  */
  bool isEmpty() const;
  /** @brief Indicates if the list is full
  *
  * Indicates if the list is full
  *
  * @return bool true if the list is full false otherwise
  */
  bool isFull() const;
  // Data queries
  /** @brief Returns the first element of the list
  *
  * Returns a reference to the first node. If the list passed is NULL or the
  * list is empty returns null.
  *
  * @return void* first element of the list
  */
  void* head();
  /** @brief Returns the last element of the list
  *
  * Returns a reference to the last node. If the list passed is NULL or the
  * list is empty returns null.
  *
  * @return void* last element of the list
  */
  void* last();
  /** @brief Returns the element at the specified position
  *
  * Returns a reference to the element at the indicated position, starting by * 0. If the list passed is NULL or the list is empty returns null. It also
  * returns NULL if position it's greater or equal to the length.
  *
  * @return void* element of the list at the indicated position
  * @param position position in which the element is located
  */
  void* at(const u16 position);
  // Insertion
  /** @brief Inserts the data at the first position of the list
  *
  * Inserts the data at the first position of the list and returns the status
  * depending of the result. In case the list is full a
  * kErrorCode_List_Is_Full is returned, if the list is null 
  * kErrorCode_Null_List and in case the the data is null
  * kErrorCode_Null_Data. The list makes a copy of the data so the value
  * you store will not be touched unless you modify it through the list.
  *
  * @return s16 status of the operation once finished
  * @param data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16 insertFirst(void *data,const u16 data_size);
  /** @brief Inserts the data at the last position of the list
  *
  * Inserts the data at the last position of the list and returns the status
  * depending of the result. In case the list is full a
  * kErrorCode_List_Is_Full is returned, if the list is null 
  * kErrorCode_Null_List and in case the the data is null
  * kErrorCode_Null_Data. The list makes a copy of the data so the value
  * you store will not be touched unless you modify it through the list.
  *
  * @return s16 status of the operation once finished
  * @param data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16 insertLast(void *data, const u16 data_size);
  /** @brief Inserts the data at the position of the list indicated
  *
  * Inserts the data at the position of the list indicated, starting by 0,   
  * and returns the status depending of the result. In case the list is full a
  * kErrorCode_List_Is_Full is returned, if the list is null 
  * kErrorCode_Null_List and in case the the data is null
  * kErrorCode_Null_Data. In case the range is greater than the number of
  * elements stored a kErrorCode_Out_Of_Range_Index will be returned.
  *
  * @return s16 status of the operation once finished
  * @param data data we wish to store at the position
  * @param data_size size of the data we wish to store
  * @param position position in which the data will be stored
  */
  s16 insertAt(void *data, const u16 position, const u16 data_size);
  // Extraction
  /** @brief Extracts the first element of the list and returns it
  *
  * Extracts the first element of the list and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the list.
  *
  * @return void* data at the first position of the list
  */
  void* extractFirst();
  /** @brief Extracts the last element of the list and returns it
  *
  * Extracts the last element of the list and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the list.
  *
  * @return void* data at the last position of the list
  */
  void* extractLast();
  /** @brief Extracts the element of the list at the position indicated
  *   and returns it
  *
  * Extracts the element of the list at the position indicated, starting by 0, 
  * and removes it from the list. Notice that the data must be freed once 
  * you finish using it as it's no longer responsability of the list.
  *
  * @return void* data at the indicated position of the list
  * @param position position of the element we want to extract
  */
  void* extractAt(u16 position); // extracts the element stored in a specific position
  // Miscellaneous
  /** @brief Concatenates two list storing the result at origin
  *
  * Concatenates the source to the list, in case one of the list has infinite
  * capacity the result list will have infinite capacity, otherwise it will be
  * the result of both capacities added. Notice that the src
  * list won't be modified during the execution. In case the list is null 
  * kErrorCode_Null_List will be returned and in case the the src is null
  * kErrorCode_Null_Pointer_Parameter_Received. If there's a problem during
  * the allocation of the new list kErrorCode_Error_Trying_To_Allocate_Memory
  * will be returned.
  *
  * @return s16 status of the operation once finished
  * concatenation
  * @param src list we want to concatenate to our origin             
  */
  s16 concat(List *src);
  /** @brief Applies the callback method to the list
  *
  * Applies a memory node function to the set of elements of the list.
  *
  * @return u16 number of elements traveled
  * @param callback function of memory node that will be applied to the set
  */
  u16 traverse(s16(MemoryNode::*callback)()) const;
  /** @brief Prints the content of the elements of the list
  *
  * Prints the content of the elements of the list
  *
  */
  void print() const;

 private:
    u16 capacity_;
    u16 length_;
    MemoryNode *first_;
    MemoryNode *last_;
};

#endif //__ADT_LIST_H__











