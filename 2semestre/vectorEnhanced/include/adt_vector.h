// adt_vector.h
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//
#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "platform_types.h"
#include "memory_node.h"

typedef struct adt_vector_s
{
  u16 head_;
  u16 tail_;
  u16 capacity_;
  u16 length_;
  MemoryNode *storage_;
  struct adt_vector_ops_s *ops_;
} Vector;

struct adt_vector_ops_s
{
  // Internal storage management
  /** @brief Initializes the vector
  *
  * Initializes the vector, this method must only be called from Create
  * as it will assume the pointer passed to it is a valid one created by
  * the Create functionality.
  *
  * @return s16 ErrorCode of the execution
  * @param *vector pointer to the vector we wish to initialize
  * @param capacity number of elements that the vector can store
  */
  s16 (*init) (Vector *vector, u16 capacity);
  /** @brief Destroys the vector and it's data
  *
  * Destroys the vector, and its data. Note that this function calls the reset
  * method. In case the direction to the pointer is null it will return a
  * kErrorCode_Null_Pointer_Reference_Received. If the execution went well this
  * function assures that the pointer to vector ends as NULL
  *
  * @return s16 ErrorCode of the execution
  * @param **vector direction to the pointer of the vector we want to destroy
  */
  s16(*destroy) (Vector **vector);
  /** @brief Resets the vector
  *
  * Frees the storage of the vector, using the reset method of memory node,
  * and sets the values of the vector to it's default. In case a null pointer
  * was passed it will return a kErrorCode_Null_Vector
  *
  * @return s16 ErrorCode of the execution
  * @param *vector pointer to the vector we wish to reset
  */
  s16 (*reset) (Vector *vector);
  /** @brief Changes the capacity of the vector
  *
  * Allocates new memory to store a new quantity of elements in the vector. If
  * the new size is lower than the length of the original vector an error will
  * happen, avoiding accidentally loss of data and will return a 
  * kErrorCode_Resize_Loss_Of_Data. In case a null vector is passed it will
  * return a kErrorCode_Null_Vector.
  *
  * @return s16 ErrorCode of the execution
  * @param *vector pointer to the vector we wish to reset
  * @param new_size new size for the vector
  */
  s16 (*resize)(Vector *vector, u16 new_size);
  // State queries
  /** @brief getter of capacity
  *
  * Returns the maximum number of elemets to store.
  *
  * @return u16 capacity of the vector
  * @param *vector pointer to the vector we wish to get the capacity
  */
  u16 (*capacity)(Vector *vector);
  /** @brief getter of the length
  *
  * Returns the current number of elements (<= capacity)
  *
  * @return u16 capacity of the vector
  * @param *vector pointer to the vector we wish to get the length
  */
  u16 (*length)(Vector *vector);
  /** @brief Indicates if the vector is empty
  *
  * Indicates if the vector is empty
  *
  * @return bool true if the vector is empty false otherwise
  * @param *vector pointer to the vector
  */
  bool (*isEmpty) (Vector *vector);
  /** @brief Indicates if the vector is full
  *
  * Indicates if the vector is full
  *
  * @return bool true if the vector is full false otherwise
  * @param *vector pointer to the vector
  */
  bool (*isFull) (Vector *vector);
  // Data queries
  /** @brief Returns the first element of the vector
  *
  * Returns a reference to the first node. If the vector passed is NULL or the
  * vector is empty returns null.
  *
  * @return void* first element of the vector
  * @param *vector pointer to the vector
  */
  void* (*head)(Vector *vector);
  /** @brief Returns the last element of the vector
  *
  * Returns a reference to the last node. If the vector passed is NULL or the
  * vector is empty returns null.
  *
  * @return void* last element of the vector
  * @param *vector pointer to the vector
  */
  void* (*last)(Vector *vector);
  /** @brief Returns the element at the specified position
  *
  * Returns a reference to the element at the indicated position. If the 
  * vector passed is NULL or the vector is empty returns null. It also returns
  * NULL if position it's greater or equal to the length.
  *
  * @return void* element of the vector at the indicated position
  * @param *vector pointer to the vector
  * @param position position in which the element is located
  */
  void* (*at)(Vector *vector, u16 position);
  // Insertion
  /** @brief Inserts the data at the first position of the vector
  *
  * Inserts the data at the first position of the vector and returns the status
  * depending of the result. In case the vector is full a
  * kErrorCode_Vector_Is_Full is returned, if the vector is null 
  * kErrorCode_Null_Vector and in case the the data is null
  * kErrorCode_Null_Data.
  *
  * @return s16 status of the operation once finished
  * @param *vector pointer to the vector
  * @param *data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16 (*insertFirst) (Vector *vector, void *data, u16 data_size);
  /** @brief Inserts the data at the last position of the vector
  *
  * Inserts the data at the last position of the vector and returns the status
  * depending of the result. In case the vector is full a
  * kErrorCode_Vector_Is_Full is returned, if the vector is null 
  * kErrorCode_Null_Vector and in case the the data is null
  * kErrorCode_Null_Data.
  *
  * @return s16 status of the operation once finished
  * @param *vector pointer to the vector
  * @param *data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16(*insertLast) (Vector *vector, void *data, u16 data_size);
  /** @brief Inserts the data at the position of the vector indicated
  *
  * Inserts the data at the position of the vector indicated and returns the 
  * status depending of the result. In case the vector is full a
  * kErrorCode_Vector_Is_Full is returned, if the vector is null 
  * kErrorCode_Null_Vector and in case the the data is null
  * kErrorCode_Null_Data. In case the range is greater than the number of
  * elements stored a kErrorCode_Out_Of_Range_Index will be returned.
  *
  * @return s16 status of the operation once finished
  * @param *vector pointer to the vector
  * @param *data data we wish to store at the position
  * @param data_size size of the data we wish to store
  * @param position position in which the data will be stored
  */
  s16(*insertAt) (Vector *vector, void *data, u16 data_size, u16 position);
  // Extraction
  /** @brief Extracts the first element of the vector and returns it
  *
  * Extracts the first element of the vector and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the vector.
  *
  * @return void* data at the first position of the vector
  * @param *vector pointer to the vector
  */
  void* (*extractFirst) (Vector *vector);
  /** @brief Extracts the last element of the vector and returns it
  *
  * Extracts the last element of the vector and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the vector.
  *
  * @return void* data at the last position of the vector
  * @param *vector pointer to the vector
  */
  void* (*extractLast) (Vector *vector);
  /** @brief Extracts the element of the vector at the position indicated
  *   and returns it
  *
  * Extracts the element of the vector at the position indicated 
  * and removes it from the vector. Notice that the data must be freed once 
  * you finished using it as it's no longer responsability of the vector.
  *
  * @return void* data at the indicated position of the vector
  * @param *vector pointer to the vector
  * @param position position of the element we want to extract
  */
  void* (*extractAt) (Vector *vector, u16 position); // extracts the element stored in a specific position
  // Miscellaneous
  /** @brief Concatenates two vector storing the result at origin
  *
  * Concatenates the source to the vector, the result of it will have a 
  * capacity of vector's capacity plus src capacity's. Notice that the src
  * vector won't be modified during the execution. In case the vector is null 
  * kErrorCode_Null_Vector will be returned and in case the the src is null
  * kErrorCode_Null_Pointer_Parameter_Received. If there's a problem during
  * the allocation of the new vector kErrorCode_Error_Trying_To_Allocate_Memory
  * will be returned.
  *
  * @return s16 status of the operation once finished
  * @param *vector pointer to the vector that will store the result of the
  * concatenation
  * @param *src vector we want to concatenate to our origin                                                       
  */
  s16(*concat) (Vector *vector, Vector *src);
  /** @brief Applies the callback method to the vector
  *
  * Applies a memory node function to the set of elements of the vector.
  *
  * @return u16 number of elements traveled
  * @param *vector pointer to the vector
  * @param *callback function of memory node that will be applied to the set
  */
  u16 (*traverse)(Vector *vector, void(*callback) (MemoryNode *));
  /** @brief Prints the content of the elements of the vector
  *
  * Prints the content of the elements of the vector
  *
  * @param *vector pointer to the vector
  */
  void(*print)(Vector *vector);
};
/** @brief Create a Vector
*
* Initializes a new Vector allocating memory for it and it's storage.
* If the allocation of memory fails returns a NULL and if everything went well
* returns the pointer to the memory node.
*
* @return Vector* pointer to the vector
*/
Vector* VECTOR_Create(u16 capacity);
#endif //__ADT_VECTOR_H__











