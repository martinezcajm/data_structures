// main.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//Test battery for memory_node
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_node.h"
#include "common_def.h"

int main()
{
  //node created to always have a reference to the operations
  MemoryNode *aux_for_ops = NULL;

  MemoryNode *node = NULL;
  MemoryNode *node2 = NULL;
  node = MEMNODE_create();
  if(NULL == node){
    printf("\n create returned a null node");
    return 1;
  }
  node2 = MEMNODE_create();
  if(NULL == node2){
    printf("\n create returned a null node");
    return 1;
  }
  aux_for_ops = MEMNODE_create();
  if(NULL == aux_for_ops){
    printf("\n create returned a null node");
    return 1;
  }
  s16 status;
  status = aux_for_ops->ops_->free(&node);
  if(kErrorCode_Ok != status){
    printf("reset failed with status %d", status);
  }

  aux_for_ops->ops_->print(node);

  node = MEMNODE_create();

  aux_for_ops->ops_->memCopy(node, "hellos", 6);
  aux_for_ops->ops_->print(node);
  aux_for_ops->ops_->memSet(node, 'c');
  aux_for_ops->ops_->print(node);
  char *name = (char*)malloc(sizeof(char)*5);
  if(NULL == name){
    return 1;
  }
  memcpy(name, "Pepe", 5);
  aux_for_ops->ops_->setData(node2, name, 5);
  aux_for_ops->ops_->print(node2);

  MemoryNode *node3 = NULL;
  MEMNODE_createFromRef(&node3);
  aux_for_ops->ops_->memCopy(node3, "hello ", 6);
  aux_for_ops->ops_->memConcat(node3, aux_for_ops->ops_->data(node2),
                               aux_for_ops->ops_->size(node2));
  aux_for_ops->ops_->print(node3);

  aux_for_ops->ops_->memMask(node2, 'e');
  aux_for_ops->ops_->print(node2);

  aux_for_ops->ops_->free(&node2);

  aux_for_ops->ops_->memMask(NULL, 'e');
  aux_for_ops->ops_->memConcat(NULL, "NULL",4);

  char *test = (char*)malloc(sizeof(char)*65535);
  if(NULL == test){
    return 1;
  }
  aux_for_ops->ops_->memConcat(node, test,-1);
  aux_for_ops->ops_->memCopy(node, "zero",0);

  char *big_data = (char*)malloc(sizeof(char)*65535);
  if(NULL == big_data){
    return 1;
  }
  aux_for_ops->ops_->memCopy(node, big_data,65535);
  aux_for_ops->ops_->print(node);
  aux_for_ops->ops_->reset(node);
  aux_for_ops->ops_->print(node);
  aux_for_ops->ops_->free(&node);
  aux_for_ops->ops_->free(&node3);
  aux_for_ops->ops_->free(&aux_for_ops);
  return 0;
}
