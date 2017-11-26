// adt_vector.c : 
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//comments included at adt_vector.h
#include "adt_vector.h"

static s16 VECTOR_init(Vector *vector);
static s16 VECTOR_destroy(Vector *vector);
static s16 VECTOR_reset(Vector *vector);
static u16 VECTOR_resize(Vector *vector, u16 new_size);
static u16 VECTOR_capacity(Vector *vector);
static u16 VECTOR_length(Vector *vector);
static bool VECTOR_isEmpty(Vector *vector);
static bool VECTOR_isFull(Vector *vector);
static void* VECTOR_head(Vector *vector);
static void* VECTOR_last(Vector *vector);
static void* VECTOR_at(Vector *vector, u16 position);
static s16 VECTOR_insertFirst(Vector *vector, void *data);
static s16 VECTOR_insertLast(Vector *vector, void *data);
static s16 VECTOR_insertAt(Vector *vector, void *data, u16 position);
static s16 VECTOR_extractFirst(Vector *vector, void *data);
static s16 VECTOR_extractLast(Vector *vector, void *data);
static s16 VECTOR_extractAt(Vector *vector, void *data, u16 position);
static s16 VECTOR_concat(Vector *vector, Vector *src);
static u16 VECTOR_taverse(Vector *vector, void(*callback) (MemoryNode *));
static void VECTOR_print(Vector *vector);

struct adt_vector_ops_s adt_vector_ops =
{
  .destroy = VECTOR_destroy,
  .reset = VECTOR_reset,
  .resize = VECTOR_resize
};

Vector* VECTOR_Create(u16 capacity)
{

}

s16 VECTOR_init(Vector *vector)
{

}

s16 VECTOR_destroy(Vector *vector)
{

}
s16 VECTOR_reset(Vector *vector)
{

}
u16 VECTOR_resize(Vector *vector, u16 new_size)
{
  
}
u16 VECTOR_capacity(Vector *vector)
{
  
}
u16 VECTOR_length(Vector *vector)
{
  
}
bool VECTOR_isEmpty(Vector *vector)
{
  
}
bool VECTOR_isFull(Vector *vector)
{
  
}
void* VECTOR_head(Vector *vector)
{
  
}
void* VECTOR_last(Vector *vector)
{
  
}
void* VECTOR_at(Vector *vector, u16 position)
{
  
}
s16 VECTOR_insertFirst(Vector *vector, void *data)
{
  
}
s16 VECTOR_insertLast(Vector *vector, void *data)
{
  
}
s16 VECTOR_insertAt(Vector *vector, void *data, u16 position)
{
  
}
s16 VECTOR_extractFirst(Vector *vector, void *data)
{
  
}
s16 VECTOR_extractLast(Vector *vector, void *data)
{
  
}
s16 VECTOR_extractAt(Vector *vector, void *data, u16 position)
{
  
}
s16 VECTOR_concat(Vector *vector, Vector *src)
{
  
}
u16 VECTOR_taverse(Vector *vector, void(*callback) (MemoryNode *))
{
  
}
void VECTOR_print(Vector *vector)
{
  
}