// memory_node.h
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//
#ifndef __MEMORY_NODE_H__
#define __MEMORY_NODE_H__

#include "platform_types.h"

typedef struct memory_node_s
{
	void *data_;
	u16 size_;
	struct memory_node_ops_s *ops_;
} MemoryNode;

struct memory_node_ops_s
{
	/** @brief Initializes the memory node
  *
  * Initializes the memory node, this method must only be called from Create
  * as it will assume the pointer passed to it is a valid one created by
  * the Create functionality.
  *
  * @return s16 ErrorCode of the execution
  * @param *node pointer to the node we wish to initialize
  */
	s16(*init) (MemoryNode *node);
	/** @brief Resets the memory node
  *
  * Sets the data and size of the memory node to it's default values. In case
  * a null pointer wass passed it will return a kErrorCode_Null_Memory_Node
  *
  * @return s16 ErrorCode of the execution
  * @param *node pointer to the node we wish to reset
  */
	s16(*reset) (MemoryNode *node);
	/** @brief Frees the memory node
  *
  * Resets the content of the memory node and frees it. Note that this function
  * calls the reset method. In case the direction to the pointer is null it 
  * will return a kErrorCode_Null_Pointer_Reference_Received. If the execution
  * went well this function assures that the pointer to node ends as NULL
  *
  * @return s16 ErrorCode of the execution
  */
	s16(*free) (MemoryNode **node);		// free memory, both data and node
	void*(*data) (MemoryNode *node);	// returns a reference to data
	u16(*size) (MemoryNode *node);		// returns data size
	s16 (*setData) (MemoryNode *node, void *src, u16 bytes);
	s16(*memSet) (MemoryNode *node, u8 value);
	s16(*memCopy) (MemoryNode *node, void *src, u16 bytes);
	s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);
	s16(*memMask) (MemoryNode *node, u8 mask);
	void(*print) (MemoryNode *node);
};
/** @brief Create a Memory Node
*
* Initializes a new memory node allocating memory from it. If the allocation 
* of memory fails returns a NULL and if everything went well returns the 
* pointer to the memory node.
*
* @return MemoryNode* pointer to the memory node
*/
MemoryNode* MEMNODE_create();
/** @brief Create a Memory Node from a reference
*
* Initializes a new memory node in the memory node passed by reference, if it
* already had something returns a warning. If the allocation of memory fails
* returns an allocation error and if everything went well returns an ok.
*
* @return s16 ErrorCode of the execution
* @param **node direction to the pointer of the memory node we want to
* initialize
*/
s16 MEMNODE_createFromRef(MemoryNode **node);

#endif // __MEMORY_NODE_H__