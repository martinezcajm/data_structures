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
  MemoryNode *storage_;
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
  * @param *node pointer to the node we wish to reset
  */
  s16 (*reset) (Vector *vector);
  u16 (*resize)(Vector *vector, u16 new_size);
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
  * NULL if position it's greater or equal to capacity
  *
  * @return void* element of the vector at the indicated position
  * @param *vector pointer to the vector
  * @param position position in which the element is located
  */
  void* (*at)(Vector *vector, u16 position);
  // Insertion
  s16 (*insertFirst) (Vector *vector, void *data, u16 data_size); // inserts an element in the first position
  s16(*insertLast) (Vector *vector, void *data, u16 data_size);
  s16(*insertAt) (Vector *vector, void *data, u16 data_size, u16 position);  // inserts an element in a specific position
  // Extraction
  s16(*extractFirst) (Vector *vector, void *data);  // extracts the element stored in the first position
  s16(*extractLast) (Vector *vector, void *data);   // extracts the element stored in the last position
  s16(*extractAt) (Vector *vector, void *data, u16 position); // extracts the element stored in a specific position
  // Miscellaneous
  s16(*concat) (Vector *vector, Vector *src);   // concatenates two vectors, and are stored in origin
  u16 (*traverse)(Vector *vector, void(*callback) (MemoryNode *)); // traverses a vector and applies a callback to each node
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











