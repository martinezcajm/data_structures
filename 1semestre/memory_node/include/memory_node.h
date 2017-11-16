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
	s16(*init) (MemoryNode *node);		// init memory node
	s16(*reset) (MemoryNode *node);		// reset content of memory node
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
// Create function:
//   1.- Allocates memory, size is passed as parameter, returns the allocated chunk of memory
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