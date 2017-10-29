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
	s16(*init) (MemoryNode *node);		// init memory node
	s16(*reset) (MemoryNode *node);		// reset content of memory node
	s16(*free) (MemoryNode *node);		// free memory, both data and node
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
//   2.- Allocates memory from a reference, size is passed as parameter, returns 0 if failed, 1 if success
s16 MEMNODE_createFromRef(MemoryNode **node);

#endif // __MEMORY_NODE_H__