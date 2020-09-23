// adt_list.h
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Header for our abstract data type list
//
#ifndef __ADT_DOUBLE_LINKED_LIST_H__
#define __ADT_DOUBLE_LINKED_LIST_H__

#include "platform_types.h"
#include "memory_node.h"

typedef struct adt_double_linked_list_s
{
  u16 capacity_;
  u16 length_;
  MemoryNode *first_;
  MemoryNode *last_;
  struct adt_double_linked_list_ops_s *ops_;
} DLList;

struct adt_double_linked_list_ops_s
{
  // Internal storage management
  /** @brief Initializes the list
  *
  * Initializes the list, this method must only be called from Create
  * as it will assume the pointer passed to it is a valid one created by
  * the Create functionality.
  *
  * @return s16 ErrorCode of the execution
  * @param *list pointer to the list we wish to initialize
  * @param capacity number of elements that the list can store note that a 
  * value of 0 will imply that it has an infinite capacity
  */
  s16 (*init) (DLList *list, u16 capacity);
  /** @brief Destroys the list and it's data
  *
  * Destroys the list and its data. Note that this function calls the reset
  * method. In case the direction to the pointer is null it will return a
  * kErrorCode_Null_Pointer_Reference_Received. If the execution went well this
  * function assures that the pointer to list ends as NULL
  *
  * @return s16 ErrorCode of the execution
  * @param **list direction to the pointer of the list we want to destroy
  */
  s16(*destroy) (DLList **list);
  /** @brief Resets the list
  *
  * Frees the elements of the list, using the reset method of memory node,
  * and sets the values of the list to it's default. In case a null pointer
  * was passed it will return a kErrorCode_Null_DLList
  *
  * @return s16 ErrorCode of the execution
  * @param *list pointer to the list we wish to reset
  */
  s16 (*reset) (DLList *list);
  /** @brief Changes the capacity of the list
  *
  * Adjusts the capacity of the list so it can store more elements. If the new
  * size causes a loss of data the function will return an error. Note that a 
  * capacity of 0 is an infinite capacity
  *
  * @return s16 ErrorCode of the execution
  * @param *list pointer to the list we wish to resuze
  * @param new_size new size for the list
  */
  s16 (*resize)(DLList *list, u16 new_size);
  // State queries
  /** @brief getter of capacity
  *
  * Returns the maximum number of elemets that can be stored at the list.
  *
  * @return u16 capacity of the list
  * @param *list pointer to the list we wish to get the capacity
  */
  u16 (*capacity)(DLList *list);
  /** @brief getter of the length
  *
  * Returns the current number of elements (<= capacity)
  *
  * @return u16 length of the list
  * @param *list pointer to the list we wish to get the length
  */
  u16 (*length)(DLList *list);
  /** @brief checks that the length of the list is consistent
  *
  * Traverses the number of elements and checks its result with its own lenght
  *
  * @return bool 
  * @param *list pointer to the list we wish to get the length
  */
  bool (*length_debug)(DLList *list);
  /** @brief Indicates if the list is empty
  *
  * Indicates if the list is empty
  *
  * @return bool true if the list is empty false otherwise
  * @param *list pointer to the list
  */
  bool (*isEmpty) (DLList *list);
  /** @brief Indicates if the list is full
  *
  * Indicates if the list is full
  *
  * @return bool true if the list is full false otherwise
  * @param *list pointer to the list
  */
  bool (*isFull) (DLList *list);
  // Data queries
  /** @brief Returns the first element of the list
  *
  * Returns a reference to the first node. If the list passed is NULL or the
  * list is empty returns null.
  *
  * @return void* first element of the list
  * @param *list pointer to the list
  */
  void* (*head)(DLList *list);
  /** @brief Returns the last element of the list
  *
  * Returns a reference to the last node. If the list passed is NULL or the
  * list is empty returns null.
  *
  * @return void* last element of the list
  * @param *list pointer to the list
  */
  void* (*last)(DLList *list);
  /** @brief Returns the element at the specified position
  *
  * Returns a reference to the element at the indicated position, starting by * 0. If the list passed is NULL or the list is empty returns null. It also
  * returns NULL if position it's greater or equal to the length.
  *
  * @return void* element of the list at the indicated position
  * @param *list pointer to the list
  * @param position position in which the element is located
  */
  void* (*at)(DLList *list, u16 position);
  // Insertion
  /** @brief Inserts the data at the first position of the list
  *
  * Inserts the data at the first position of the list and returns the status
  * depending of the result. In case the list is full a
  * kErrorCode_DLList_Is_Full is returned, if the list is null 
  * kErrorCode_Null_DLList and in case the the data is null
  * kErrorCode_Null_Data. The list makes a copy of the data so the value
  * you store will not be touched unless you modify it through the list.
  *
  * @return s16 status of the operation once finished
  * @param *list pointer to the list
  * @param *data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16 (*insertFirst) (DLList *list, void *data, u16 data_size);
  /** @brief Inserts the data at the last position of the list
  *
  * Inserts the data at the last position of the list and returns the status
  * depending of the result. In case the list is full a
  * kErrorCode_DLList_Is_Full is returned, if the list is null 
  * kErrorCode_Null_DLList and in case the the data is null
  * kErrorCode_Null_Data. The list makes a copy of the data so the value
  * you store will not be touched unless you modify it through the list.
  *
  * @return s16 status of the operation once finished
  * @param *list pointer to the list
  * @param *data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16(*insertLast) (DLList *list, void *data, u16 data_size);
  /** @brief Inserts the data at the position of the list indicated
  *
  * Inserts the data at the position of the list indicated, starting by 0,   
  * and returns the status depending of the result. In case the list is full a
  * kErrorCode_DLList_Is_Full is returned, if the list is null 
  * kErrorCode_Null_DLList and in case the the data is null
  * kErrorCode_Null_Data. In case the range is greater than the number of
  * elements stored a kErrorCode_Out_Of_Range_Index will be returned.
  *
  * @return s16 status of the operation once finished
  * @param *list pointer to the list
  * @param *data data we wish to store at the position
  * @param data_size size of the data we wish to store
  * @param position position in which the data will be stored
  */
  s16(*insertAt) (DLList *list, void *data, u16 position, u16 data_size);
  // Extraction
  /** @brief Extracts the first element of the list and returns it
  *
  * Extracts the first element of the list and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the list.
  *
  * @return void* data at the first position of the list
  * @param *list pointer to the list
  */
  void* (*extractFirst) (DLList *list);
  /** @brief Extracts the last element of the list and returns it
  *
  * Extracts the last element of the list and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the list.
  *
  * @return void* data at the last position of the list
  * @param *list pointer to the list
  */
  void* (*extractLast) (DLList *list);
  /** @brief Extracts the element of the list at the position indicated
  *   and returns it
  *
  * Extracts the element of the list at the position indicated, starting by 0, 
  * and removes it from the list. Notice that the data must be freed once 
  * you finish using it as it's no longer responsability of the list.
  *
  * @return void* data at the indicated position of the list
  * @param *list pointer to the list
  * @param position position of the element we want to extract
  */
  void* (*extractAt) (DLList *list, u16 position); // extracts the element stored in a specific position
  // Miscellaneous
  /** @brief Concatenates two list storing the result at origin
  *
  * Concatenates the source to the list, in case one of the list has infinite
  * capacity the result list will have infinite capacity, otherwise it will be
  * the result of both capacities added. Notice that the src list will 
  * dissapear after the execution. In case the list is null 
  * kErrorCode_Null_DLList will be returned and in case the the src is null
  * kErrorCode_Null_Pointer_Parameter_Received. If there's a problem during
  * the allocation of the new list kErrorCode_Error_Trying_To_Allocate_Memory
  * will be returned.
  *
  * @return s16 status of the operation once finished
  * @param *list pointer to the list that will store the result of the
  * concatenation
  * @param *src list we want to concatenate to our origin             
  */
  s16(*concat) (DLList *list, DLList *src);
  /** @brief Applies the callback method to the list
  *
  * Applies a memory node function to the set of elements of the list.
  *
  * @return u16 number of elements traveled
  * @param *list pointer to the list
  * @param *callback function of memory node that will be applied to the set
  */
  u16 (*traverse)(DLList *list, void(*callback) (MemoryNode *));
  /** @brief Prints the content of the elements of the list
  *
  * Prints the content of the elements of the list
  *
  * @param *list pointer to the list
  */
  void(*print)(DLList *list);
};
/** @brief Create a DLList
*
* Initializes a new DLList allocating memory for it and it's storage.
* If the allocation of memory fails returns a NULL and if everything went well
* returns the pointer to the memory node. Note that a capacity of 0 is an
* infinite capacity
*
* @return DLList* pointer to the list
*/
DLList* DLLIST_Create(u16 capacity);
#endif //__ADT_LIST_H__











