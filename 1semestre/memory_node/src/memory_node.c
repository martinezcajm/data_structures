// memory_node.c : 
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//

//comments included at memory_node.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_node.h"
#include "common_def.h"

static s16 MEMNODE_init(MemoryNode *node);
static s16 MEMNODE_reset(MemoryNode *node);
static s16 MEMNODE_free (MemoryNode **node);
static void* MEMNODE_data(MemoryNode *node); // returns a reference to data
static u16 MEMNODE_size(MemoryNode *node); // returns data size
static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memSet(MemoryNode *node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memConcat (MemoryNode *node, void *src, u16 bytes);
static void MEMNODE_print (MemoryNode *node);


struct memory_node_ops_s memory_node_ops =
{
	.reset = MEMNODE_reset,
	.free = MEMNODE_free,
	.data = MEMNODE_data,
	.size = MEMNODE_size,
	.setData = MEMNODE_setData,
	.memSet = MEMNODE_memSet,
	.memCopy = MEMNODE_memCopy,
	.memConcat = MEMNODE_memConcat,
	.print = MEMNODE_print
};


MemoryNode* MEMNODE_create()
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

s16 MEMNODE_createFromRef(MemoryNode **node){
	if(NULL == node){
#ifdef VERBOSE_
		printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Pointer_Reference_Received;
	}
	//TODO Si la referencia tiene algo la devolvemos

	*node = MEMNODE_create();
	if(NULL == *node){
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return kErrorCode_Error_Trying_To_Allocate_Memory;
	}
	return kErrorCode_Ok;
}

s16 MEMNODE_init(MemoryNode *node)
{
	//This function will only by called from Create so we don't need to check
	//the pointer.
	node->data_ = NULL;
	node->size_ = 0;
	node->ops_ = &memory_node_ops;
	return kErrorCode_Ok;
}

static s16 MEMNODE_reset(MemoryNode *node){
	if (NULL == node)
	{
#ifdef VERBOSE_
		printf("Error: [%s] the memory node is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Memory_Node;
	}
	node->size_ = 0;
	if(NULL == node->data_){
		return kErrorCode_Ok;
	}
	free(node->data_);
	node->data_ = NULL;
	return kErrorCode_Ok;
}

s16 MEMNODE_free (MemoryNode **node){
	if(NULL == node){
#ifdef VERBOSE_
		printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Pointer_Reference_Received;
	}
	//We don't need to check if the pointer to node is null as reset will do it
	s16 status = MEMNODE_reset(*node);
	//We check if all went well and free the node in that case, if the node we
	//sent to reset was already null it's already free.
	if(kErrorCode_Ok == status){
		free(*node);
		*node = NULL;
	}
	return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node) // returns a reference to data
{
	if(NULL == node){
#ifdef VERBOSE_
			printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
			return NULL;
	}
	return node->data_;
}

u16	MEMNODE_size(MemoryNode *node) // returns data size
{
	if(NULL == node){
#ifdef VERBOSE_
			printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
			return 0;
	}
	return node->size_;
}

s16	MEMNODE_setData(MemoryNode *node, void *src, u16 bytes) 
{
	if(NULL == src){
#ifdef VERBOSE_
		printf("Warning: [%s] The data passed is null\n", __FUNCTION__);
#endif
		return kWarningCode_Strange_Operation;
	}
	s16 status = MEMNODE_reset(node);
	if(kErrorCode_Null_Memory_Node == status){
#ifdef VERBOSE_
		printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
		return status;
	}
	node->size_ = bytes; 
	node->data_ = src;
	return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value){
	if(NULL == node){
#ifdef VERBOSE_
		printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Memory_Node;
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

s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes){
	
	if(NULL == src){
#ifdef VERBOSE_
	printf("Error: [%s] the src passed is null\n", __FUNCTION__);
#endif
	return kErrorCode_Null_Pointer_Parameter_Received;
	}

	//We don't need to check if node is null as reset will do it
	s16 status = MEMNODE_reset(node);
	if(kErrorCode_Null_Memory_Node == status){
#ifdef VERBOSE_
		printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
		return status;
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

s16 MEMNODE_memConcat (MemoryNode *node, void *src, u16 bytes){
	if(NULL == node){
#ifdef VERBOSE_
		printf("Error: [%s] The pointer to memory node is null\n", __FUNCTION__);
#endif
		return kErrorCode_Null_Memory_Node;
	}
	if(NULL == node->data_ || NULL == src){
#ifdef VERBOSE_
		printf("Warning: [%s] trying to concat with null\n", __FUNCTION__);
#endif
		return kWarningCode_Strange_Operation;
	}
	s8 *aux;
	aux = (s8*)malloc(node->size_ + bytes);
	if(NULL == aux){
#ifdef VERBOSE_
		printf("Error: [%s] malloc failed\n", __FUNCTION__);
#endif
		return kErrorCode_Error_Trying_To_Allocate_Memory;
	}
	memcpy(aux, node->data_, node->size_-1);
	memcpy(aux + (node->size_-1), src, bytes);
	//We have already checked that data is not null.
	free(node->data_);
	node->data_ = aux;
	node->size_ = node->size_ + bytes;
	return kErrorCode_Ok;
}

void MEMNODE_print(MemoryNode *node){
	if(NULL == node){
#ifdef VERBOSE_
		printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
		printf("The node is null\n");
		return;
	}
	if(NULL == node->data_){
#ifdef VERBOSE_
		printf("Error: [%s] the pointer passed is null\n", __FUNCTION__);
#endif
		printf("The data is null\n");
		return;
	}
	printf("The data of the node is %s\n", (char *)node->data_);
}

int main(){
	MemoryNode *node = NULL;
	MemoryNode *node2 = NULL;
	MemoryNode *node3 = NULL;
	node = MEMNODE_create();
	node2 = MEMNODE_create();
	node3 = MEMNODE_create();
	MEMNODE_free(&node);
	MEMNODE_print(node);
	node = MEMNODE_create();
	MEMNODE_setData(node, "hellos", 6);
	MEMNODE_print(node);
	MEMNODE_memSet(node, 'c');
	MEMNODE_memCopy(node2, "hello", 6);
	MEMNODE_print(node);
	//MEMNODE_memCopy(node2, "hello world", 12);
	MEMNODE_print(node2);
	MEMNODE_memConcat(node2, " world", 7);
	MEMNODE_print(node2);
	return 0;
}