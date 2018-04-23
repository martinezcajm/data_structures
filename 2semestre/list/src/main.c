// main.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//Test battery for adt_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_list.h"

int main()
{
  List *list = NULL;
  list = LIST_Create(5);
  char data[1024];
  
  if(NULL == list){
    printf("\n create returned a null list");
    return 1;
  }
  printf("\ncapacity: %d", list->ops_->capacity(list));
  printf("\nlength: %d", list->ops_->length(list));
  printf("\n isEmpty: %d", list->ops_->isEmpty(list));
  printf("\n isFull: %d", list->ops_->isFull(list));

  list->ops_->insertFirst(list, "Let's store strings", 20);
  list->ops_->insertLast(list, "go", 3);
  list->ops_->insertAt(list, "You are too slow", 4,17); //out of range
  list->ops_->insertAt(list, "You are too slow", 0,17); 
  list->ops_->insertFirst(list, "good boy", 9);
  list->ops_->insertLast(list, " my boy", 8);
  list->ops_->insertLast(list, " my boy", 8);

  memset(data, 0, sizeof(data));
  memcpy(data, list->ops_->head(list), 9);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, list->ops_->last(list), 8);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, list->ops_->at(list, 3), 3);
  printf("\n %s", data);

  printf("\ncapacity: %d", list->ops_->capacity(list));
  printf("\nlength: %d", list->ops_->length(list));
  printf("\n isEmpty: %d", list->ops_->isEmpty(list));
  printf("\n isFull: %d \n", list->ops_->isFull(list));

  list->ops_->print(list);
  list->ops_->resize(list, 7);
  list->ops_->insertFirst(list, "Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  list->ops_->print(list); 
  list->ops_->insertAt(list, " inserting at 3", 3, 16);
  printf("\n \n||||Third print:||||\n");
  list->ops_->print(list); 
  printf("\ncapacity: %d", list->ops_->capacity(list));
  printf("\nlength: %d", list->ops_->length(list));
  printf("\n isEmpty: %d", list->ops_->isEmpty(list));
  printf("\n isFull: %d \n", list->ops_->isFull(list));

  List *list2 = NULL;
  list2 = LIST_Create(2);

  List *list3 = NULL;
  list3 = LIST_Create(3);

  list2->ops_->insertFirst(list2, "Let's concatenate", 18);
  list2->ops_->insertLast(list2, "now", 4);

  list3->ops_->insertFirst(list3, "Concatenate with me", 20);
  list3->ops_->insertLast(list3, "come on!", 9);


  list2->ops_->concat(list2, list3);
  list3->ops_->destroy(&list3);
  printf("\n \n|||| Fourth print: |||| \n");
  list2->ops_->print(list2); 
  printf("\ncapacity: %d", list2->ops_->capacity(list2));
  printf("\nlength: %d", list2->ops_->length(list2));
  printf("\n isEmpty: %d", list2->ops_->isEmpty(list2));
  printf("\n isFull: %d", list2->ops_->isFull(list2));

  memset(data, 0, sizeof(data));
  memcpy(data, list2->ops_->extractFirst(list2), 18);
  printf("\n %s", data);
  list2->ops_->extractLast(list2);
  printf("\n \n|||list2 after extract||| \n");
  list2->ops_->print(list2);
  list2->ops_->insertFirst(list2, "I see you lost something", 25);
  printf("\n \n|||list2||| \n");
  list2->ops_->print(list2);

  list2->ops_->insertLast(list2, "go", 3);
  list2->ops_->insertLast(list2, "again", 6);
  list2->ops_->extractFirst(list2);
  list2->ops_->extractFirst(list2);
  printf("\n \n|||list2 ready to resize||| \n");
  list2->ops_->print(list2);
  list2->ops_->resize(list2, 3);
  printf("\n \n|||list2 after resize||| \n");
  list2->ops_->print(list2);
  list2->ops_->resize(list2, 1);
  printf("\n \n|||list2 after second resize||| \n");
  list2->ops_->print(list2);


  memset(data, 0, sizeof(data));
  memcpy(data, list->ops_->extractAt(list, 4), 20);
  printf("\n %s \n", data);
  printf("\n \n|||list before extract||| \n");
  list->ops_->print(list);
  list->ops_->extractAt(list, 3);
  printf("\n \n|||list after extract||| \n");
  list->ops_->print(list);

  list->ops_->reset(list);
  printf("\n \n|||list after reset||| \n");
  list->ops_->print(list);
  list->ops_->insertFirst(list, "Let's store strings", 20);
  printf("\n \n|||list after insert||| \n");
  list->ops_->print(list);
  list->ops_->destroy(&list);
  list2->ops_->destroy(&list2);
  List *infinite_list = NULL;
  infinite_list = LIST_Create(0);
  infinite_list->ops_->insertLast(infinite_list, "I have infinite power", 22);
  infinite_list->ops_->insertLast(infinite_list, "and infinite space", 19);
  infinite_list->ops_->insertAt(infinite_list, "boy", 3, 4);
  infinite_list->ops_->insertAt(infinite_list, "boy", 2, 4);
  printf("\n \n|||infinite list||| \n");
  infinite_list->ops_->print(infinite_list);
  printf("\n isEmpty: %d", infinite_list->ops_->length_debug(infinite_list));
  infinite_list->ops_->resize(infinite_list, 2);
  infinite_list->ops_->resize(infinite_list, 3);
  infinite_list->ops_->insertLast(infinite_list, "noo", 4);
  printf("\n %s", data);
}