// main.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//Test battery for adt_vector
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_vector.h"

int main()
{
  Vector *vector = NULL;
  vector = VECTOR_Create(5);
  //char *data = NULL;
  char data[1024];
  
  if(NULL == vector){
    printf("\n create returned a null vector");
    return 1;
  }
  printf("\ncapacity: %d", vector->ops_->capacity(vector));
  printf("\nlength: %d", vector->ops_->length(vector));
  printf("\n isEmpty: %d", vector->ops_->isEmpty(vector));
  printf("\n isFull: %d", vector->ops_->isFull(vector));

  vector->ops_->insertFirst(vector, "Let's store strings", 20);
  vector->ops_->insertLast(vector, "go", 3);
  vector->ops_->insertAt(vector, "You are too slow", 4,17); //out of range
  vector->ops_->insertAt(vector, "You are too slow", 0,17); 
  vector->ops_->insertFirst(vector, "good boy", 9);
  vector->ops_->insertLast(vector, " my boy", 8);
  vector->ops_->insertLast(vector, " my boy", 8);

  memset(data, 0, sizeof(data));
  memcpy(data, vector->ops_->head(vector), 9);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, vector->ops_->last(vector), 8);
  printf("\n %s", data);
  memset(data, 0, sizeof(data));
  memcpy(data, vector->ops_->at(vector, 3), 3);
  printf("\n %s", data);

  printf("\ncapacity: %d", vector->ops_->capacity(vector));
  printf("\nlength: %d", vector->ops_->length(vector));
  printf("\n isEmpty: %d", vector->ops_->isEmpty(vector));
  printf("\n isFull: %d \n", vector->ops_->isFull(vector));

  vector->ops_->print(vector);
  vector->ops_->resize(vector, 7);
  vector->ops_->insertFirst(vector, "Now I'm bigger", 15);
  printf("\n \n||||Second print:||||\n");
  vector->ops_->print(vector); 
  vector->ops_->insertAt(vector, " inserting at 3", 3, 16);
  printf("\n \n||||Third print:||||\n");
  vector->ops_->print(vector); 
  printf("\ncapacity: %d", vector->ops_->capacity(vector));
  printf("\nlength: %d", vector->ops_->length(vector));
  printf("\n isEmpty: %d", vector->ops_->isEmpty(vector));
  printf("\n isFull: %d \n", vector->ops_->isFull(vector));

  Vector *vector2 = NULL;
  vector2 = VECTOR_Create(2);

  Vector *vector3 = NULL;
  vector3 = VECTOR_Create(3);

  vector2->ops_->insertFirst(vector2, "Let's concatenate", 18);
  vector2->ops_->insertLast(vector2, "now", 4);

  vector3->ops_->insertFirst(vector3, "Concatenate with me", 20);
  vector3->ops_->insertLast(vector3, "come on!", 9);


  vector2->ops_->concat(vector2, vector3);
  vector3->ops_->destroy(&vector3);
  printf("\n \n|||| Fourth print: |||| \n");
  vector2->ops_->print(vector2); 
  printf("\ncapacity: %d", vector2->ops_->capacity(vector2));
  printf("\nlength: %d", vector2->ops_->length(vector2));
  printf("\n isEmpty: %d", vector2->ops_->isEmpty(vector2));
  printf("\n isFull: %d", vector2->ops_->isFull(vector2));

  memset(data, 0, sizeof(data));
  memcpy(data, vector2->ops_->extractFirst(vector2), 18);
  printf("\n %s", data);
  vector2->ops_->extractLast(vector2);
  printf("\n \n|||vector2 after extract||| \n");
  vector2->ops_->print(vector2);
  vector2->ops_->insertFirst(vector2, "I see you lost something", 25);
  printf("\n \n|||vector2||| \n");
  vector2->ops_->print(vector2);

  vector2->ops_->insertLast(vector2, "go", 3);
  vector2->ops_->insertLast(vector2, "again", 6);
  vector2->ops_->extractFirst(vector2);
  vector2->ops_->extractFirst(vector2);
  printf("\n \n|||vector2 ready to resize||| \n");
  vector2->ops_->print(vector2);
  vector2->ops_->resize(vector2, 3);
  printf("\n \n|||vector2 after resize||| \n");
  vector2->ops_->print(vector2);
  vector2->ops_->resize(vector2, 1);
  printf("\n \n|||vector2 after second resize||| \n");
  vector2->ops_->print(vector2);


  memset(data, 0, sizeof(data));
  memcpy(data, vector->ops_->extractAt(vector, 4), 20);
  printf("\n %s \n", data);
  vector->ops_->extractAt(vector, 6);
  printf("\n \n|||vector after extract||| \n");
  vector->ops_->print(vector);

  vector->ops_->reset(vector);
  printf("\n \n|||vector after reset||| \n");
  vector->ops_->print(vector);
  vector->ops_->insertFirst(vector, "Let's store strings", 20);
  printf("\n \n|||vector after insert||| \n");
  vector->ops_->print(vector);
  vector->ops_->destroy(&vector);
  vector2->ops_->destroy(&vector2);
}