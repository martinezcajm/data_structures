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
  */
	s16 (*init) (Vector *vector);
	s16(*destroy) (Vector **vector);					// destroys the vector, and its data
	s16 (*reset) (Vector *vector);					// resets vector's data
	u16 (*resize)(Vector *vector, u16 new_size);
	// State queries
	u16 (*capacity)(Vector *vector);				// returns the maximum number of elemets to store
	u16 (*length)(Vector *vector);					// current number of elements (<= capacity)
	bool (*isEmpty) (Vector *vector);
	bool (*isFull) (Vector *vector);
	// Data queries
	void* (*head)(Vector *vector);					// Head: returns a reference to the first node
	void* (*last)(Vector *vector);					// Last: returns a reference to the last node
	void* (*at)(Vector *vector, u16 position);		// At: returns a reference to a specific position
	// Insertion
	s16 (*insertFirst) (Vector *vector, void *data); // inserts an element in the first position
	s16(*insertLast) (Vector *vector, void *data);
	s16(*insertAt) (Vector *vector, void *data, u16 position);	// inserts an element in a specific position
	// Extraction
	s16(*extractFirst) (Vector *vector, void *data);	// extracts the element stored in the first position
	s16(*extractLast) (Vector *vector, void *data);		// extracts the element stored in the last position
	s16(*extractAt) (Vector *vector, void *data, u16 position);	// extracts the element stored in a specific position
	// Miscellaneous
	s16(*concat) (Vector *vector, Vector *src);		// concatenates two vectors, and are stored in origin
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











