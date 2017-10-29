// memory_node.c : 
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//

#include <stdio.h>
#include <stdlib.h>

#include "memory_node.h"
#include "common_def.h"

static s16 MEMNODE_init(MemoryNode *node);
static s16 MEMNODE_reset(MemoryNode *node);
static void* MEMNODE_data(MemoryNode *node); // returns a reference to data
static u16 MEMNODE_size(MemoryNode *node); // returns data size

static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes);

struct memory_node_ops_s memory_node_ops =
{
	.init = MEMNODE_init,
	.data = MEMNODE_data,
	.size = MEMNODE_size,
};


MemoryNode* MEMNODE_Create()
{
	MemoryNode *node = malloc(sizeof(MemoryNode));
	if (NULL == node)
	{
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	MEMNODE_init(node);
	return node;
}

s16 MEMNODE_init(MemoryNode *node)
{
	if (NULL == node)
	{
#ifdef VERBOSE_
		printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Pointer_Received;
	}
	node->data_ = NULL;
	node->size_ = 0;
	node->ops_ = &memory_node_ops;
	return kErrorCode_Ok;
}

static s16 MEMNODE_reset(MemoryNode *node){
	if (NULL == node)
	{
#ifdef VERBOSE_
		printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Pointer_Received;
	}
	node->size_ = 0;
	if(NULL == node->data_){
		return kErrorCode_Ok;
	}
	free(node->data_);
	node->data_ = NULL;
	return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node) // returns a reference to data
{
	if(NULL == node){
		#ifdef VERBOSE_
			printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
		#endif
			return NULL;
	}
	return node->data_;
}

u16	MEMNODE_size(MemoryNode *node) // returns data size
{
	if(NULL == node){
		#ifdef VERBOSE_
			printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
		#endif
			return 0;
	}
	return node->size_;
}

s16	MEMNODE_setData(MemoryNode *node, void *src, u16 bytes) 
{
	s16 status = MEMNODE_reset(node);
	if(status == kErrorCode_Null_Pointer_Received){
		#ifdef VERBOSE_
			printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
		#endif
			return status;
	}
	node->size_ = bytes; 
	node->data_ = src;
	return kErrorCode_Ok;

	//return node->size_;
}

int main(){
	MemoryNode *node = NULL;
	node = MEMNODE_Create();

	return 0;
}