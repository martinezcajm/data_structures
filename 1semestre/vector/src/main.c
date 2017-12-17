#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_vector.h"

int main()
{
  Vector *vector = NULL;
  vector = VECTOR_Create(5);
  if(NULL == vector){
    printf("\n create returned a null vector");
    return 1;
  }
  printf("\ncapacity: %d", vector->ops_->capacity(vector));
  printf("\nlength: %d", vector->ops_->length(vector));
  printf("\n isEmpty: %d", vector->ops_->isEmpty(vector));
  printf("\n isFull: %d", vector->ops_->isFull(vector));

  vector->ops_->insertFirst(vector, "Let's store strings", 19);
  vector->ops_->insertLast(vector, "go", 2);
  vector->ops_->insertFirst(vector, "You are too slow", 16);
  vector->ops_->insertFirst(vector, "good boy", 8);
  vector->ops_->insertLast(vector, " my boy", 7);
  vector->ops_->insertLast(vector, " my boy", 7);

  printf("\ncapacity: %d", vector->ops_->capacity(vector));
  printf("\nlength: %d", vector->ops_->length(vector));
  printf("\n isEmpty: %d", vector->ops_->isEmpty(vector));
  printf("\n isFull: %d \n", vector->ops_->isFull(vector));

  vector->ops_->print(vector);
  vector->ops_->resize(vector, 7);
  vector->ops_->insertFirst(vector, "Now I'm bigger", 14);
  printf("\nSecond print:");
  vector->ops_->print(vector); 
  vector->ops_->insertAt(vector, " inserting at 3", 3, 15);
  printf("\nThird print:");
  vector->ops_->print(vector); 
  printf("\ncapacity: %d", vector->ops_->capacity(vector));
  printf("\nlength: %d", vector->ops_->length(vector));
  printf("\n isEmpty: %d", vector->ops_->isEmpty(vector));
  printf("\n isFull: %d \n", vector->ops_->isFull(vector));

  Vector *vector2 = NULL;
  vector2 = VECTOR_Create(2);

  Vector *vector3 = NULL;
  vector3 = VECTOR_Create(3);

  vector2->ops_->insertFirst(vector2, "Let's concatenate", 17);
  vector2->ops_->insertLast(vector2, "now", 3);

  vector3->ops_->insertFirst(vector3, "Concatenate with me", 19);
  vector3->ops_->insertLast(vector3, "come on!", 8);

  vector2->ops_->concat(vector2, vector3);
  printf("\n Fourth print:");
  vector2->ops_->print(vector2); 
  printf("\ncapacity: %d", vector2->ops_->capacity(vector2));
  printf("\nlength: %d", vector2->ops_->length(vector2));
  printf("\n isEmpty: %d", vector2->ops_->isEmpty(vector2));
  printf("\n isFull: %d", vector2->ops_->isFull(vector2));
}