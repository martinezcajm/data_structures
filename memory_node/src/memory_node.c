// memory_node.c : 
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_node.h"
#include "common_def.h"

static s16 MEMNODE_init(MemoryNode *node);
static s16 MEMNODE_reset(MemoryNode *node);
static s16 MEMNODE_free (MemoryNode *node);
static void* MEMNODE_data(MemoryNode *node); // returns a reference to data
static u16 MEMNODE_size(MemoryNode *node); // returns data size
static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memSet(MemoryNode *node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memConcat (MemoryNode *node, void *src, u16 bytes);


struct memory_node_ops_s memory_node_ops =
{
	.init = MEMNODE_init,
	.reset = MEMNODE_reset,
	.free = MEMNODE_free,
	.data = MEMNODE_data,
	.size = MEMNODE_size,
	.setData = MEMNODE_setData,
	.memSet = MEMNODE_memSet,
	.memCopy = MEMNODE_memCopy,
	.memConcat = MEMNODE_memConcat
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

s16 MEMNODE_free (MemoryNode *node){
	//We don't need to check if node is null as reset will do it
	s16 status = MEMNODE_reset(node);
	if(kErrorCode_Null_Pointer_Received == status){
		//The node is already null, so it's already free.	
		return kErrorCode_Ok;
	}
	free(node);
	node = NULL;
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
	if(kErrorCode_Null_Pointer_Received == status){
#ifdef VERBOSE_
			printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
			return status;
	}
	node->size_ = bytes; 
	node->data_ = src;
	return kErrorCode_Ok;
}

s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes){
	
	if(NULL == src){
#ifdef VERBOSE_
	printf("Error: [%s] the src passed is null\n", __FUNCTION__);
#endif
	return kErrorCode_Null_Pointer_Received;
	}

	//We don't need to check if node is null as reset will do it
	s16 status = MEMNODE_reset(node);
	if(kErrorCode_Null_Pointer_Received == status){
#ifdef VERBOSE_
		printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Pointer_Received;
	}
	node->data_	= malloc(bytes);
	if(NULL == node->data_){
#ifdef VERBOSE_
		printf("Error: [%s] malloc failed\n", __FUNCTION__);
#endif
		return kErrorCode_Error_Trying_To_Allocate_Memory;
	}
	memcpy(node->data_, src, bytes);
	//node->data_ = src;
	 node->size_ = bytes;
	return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value){
	if(NULL == node){
#ifdef VERBOSE_
		printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Pointer_Received;
	}
	if(NULL == node->data_){
#ifdef VERBOSE_
		printf("Error: [%s] Trying to do a memset to null data\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Data;
	}
	memset(node->data_, (s16)value, node->size_);
	return kErrorCode_Ok;
}

s16 MEMNODE_memConcat (MemoryNode *node, void *src, u16 bytes){
	if(NULL == node){
#ifdef VERBOSE_
		printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Pointer_Received;
	}
	if(NULL == node->data_ || NULL == src){
#ifdef VERBOSE_
		printf("Warning: [%s] trying to concat with null\n", __FUNCTION__);
#endif
		return kWarningCode_Ilogic_Expression;
	}
	s16 *aux;
	aux = (s16*)malloc(node->size_ + bytes);
	if(NULL == aux){
#ifdef VERBOSE_
		printf("Error: [%s] malloc failed\n", __FUNCTION__);
#endif
		return kErrorCode_Error_Trying_To_Allocate_Memory;
	}
	memcpy(aux, node->data_, node->size_);
	memcpy(aux+node->size_, src, bytes);
	//We have already checked that data is not null.
	free(node->data_);
	node->data_ = aux;
	node->size_ = node->size_ + bytes;
	return kErrorCode_Ok;
}

int main(){
	MemoryNode *node = NULL;
	node = MEMNODE_Create();

	return 0;
}