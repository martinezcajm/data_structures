// adt_vector.h
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//
#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "platform_types.h"
#include "memory_node.h"

class Vector
{
 public:
   /** @brief Vector constructor
   *
   * Base constructor of vector
   *
   * @return *Vector
   */
   Vector(u16 capacity);
   /** @brief Frees the vector
   *
   * Resets the content of the vector and frees it. Note that this function
   * calls the reset method.
   *
   * @return void
   */
   ~Vector();
   /** @brief vector copy constructor
   *
   * Vector copy constructor.
   *
   * @return *Vector
   * @param o vector to be copied
   */
   Vector(const Vector& o);
   /** @brief Vector = operation
   *
   * returns a reference to memory node equal to mn
   *
   * @return &Vector
   * @param v vector to be copied
   */
   Vector& operator = (const Vector &v);
   /** @brief Vector new operation override
   *
   * returns a reference to memory node equal to mn
   *
   * @return void*
   * @param size size of the memory to allocate
   */
   void* operator new(size_t size);
   /** @brief Vector delete operation override
   *
   * returns a reference to memory node equal to mn
   *
   * @return void
   * @param pointer_to_delete vector to be copied
   */
   void operator delete(void* pointer_to_delete);
   /** @brief Initializes the memory node
   *
   * Initializes the memory node. Note that the constructor
   * already initializes the node.
   *
   * @return s16 ErrorCode of the execution
   */
  /** @brief Initializes the vector
  *
  * Initializes the vector, this method must only be called from Create
  * as it will assume the pointer passed to it is a valid one created by
  * the Create functionality.
  *
  * @return s16 ErrorCode of the execution
  * @param capacity number of elements that the vector can store
  */
  s16 init (const u16 capacity);
  /** @brief Resets the vector
  *
  * Frees the storage of the vector, using the reset method of memory node,
  * and sets the values of the vector to it's default. In case a null pointer
  * was passed it will return a kErrorCode_Null_Vector
  *
  * @return s16 ErrorCode of the execution
  */
  s16 reset();
  /** @brief Changes the capacity of the vector
  *
  * Allocates new memory to store a new quantity of elements in the vector. If
  * the new size is lower than the original vector the elements that exceed the
  * new size will be freed. In case a null vector is passed it will return
  * a kErrorCode_Null_Vector.
  *
  * @return s16 ErrorCode of the execution
  * @param new_size new size for the vector
  */
  s16  resize(const u16 new_size);
  // State queries
  /** @brief getter of capacity
  *
  * Returns the maximum number of elemets to store.
  *
  * @return u16 capacity of the vector
  */
  u16 capacity() const;
  /** @brief getter of the length
  *
  * Returns the current number of elements (<= capacity)
  *
  * @return u16 capacity of the vector
  */
  u16 length() const;
  /** @brief Indicates if the vector is empty
  *
  * Indicates if the vector is empty
  *
  * @return bool true if the vector is empty false otherwise
  */
  boolean isEmpty () const;
  /** @brief Indicates if the vector is full
  *
  * Indicates if the vector is full
  *
  * @return bool true if the vector is full false otherwise
  */
  boolean isFull () const;
  // Data queries
  /** @brief Returns the first element of the vector
  *
  * Returns a reference to the first node. If the vector passed is NULL or the
  * vector is empty returns null.
  *
  * @return void* first element of the vector
  */
  void* head();
  /** @brief Returns the last element of the vector
  *
  * Returns a reference to the last node. If the vector passed is NULL or the
  * vector is empty returns null.
  *
  * @return void* last element of the vector
  */
  void* last();
  /** @brief Returns the element at the specified position
  *
  * Returns a reference to the element at the indicated position. If the 
  * vector passed is NULL or the vector is empty returns null. It also returns
  * NULL if position it's greater or equal to the length.
  *
  * @return void* element of the vector at the indicated position
  * @param position position in which the element is located
  */
  void* at(const u16 position);
  // Insertion
  /** @brief Inserts the data at the first position of the vector
  *
  * Inserts the data at the first position of the vector and returns the status
  * depending of the result. In case the vector is full a
  * kErrorCode_Vector_Is_Full is returned, if the vector is null 
  * kErrorCode_Null_Vector and in case the the data is null
  * kErrorCode_Null_Data.
  *
  * @return s16 status of the operation once finished
  * @param data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16 insertFirst (void *data, const u16 data_size);
  /** @brief Inserts the data at the last position of the vector
  *
  * Inserts the data at the last position of the vector and returns the status
  * depending of the result. In case the vector is full a
  * kErrorCode_Vector_Is_Full is returned, if the vector is null 
  * kErrorCode_Null_Vector and in case the the data is null
  * kErrorCode_Null_Data.
  *
  * @return s16 status of the operation once finished
  * @param data data we wish to store at the position
  * @param data_size size of the data we wish to store
  */
  s16 insertLast (void *data, const u16 data_size);
  /** @brief Inserts the data at the position of the vector indicated
  *
  * Inserts the data at the position of the vector indicated and returns the 
  * status depending of the result. In case the vector is full a
  * kErrorCode_Vector_Is_Full is returned, if the vector is null 
  * kErrorCode_Null_Vector and in case the the data is null
  * kErrorCode_Null_Data. In case the range is greater than the number of
  * elements stored a kErrorCode_Out_Of_Range_Index will be returned.
  *
  * @return s16 status of the operation once finished
  * @param data data we wish to store at the position
  * @param data_size size of the data we wish to store
  * @param position position in which the data will be stored
  */
  s16 insertAt (void *data, const u16 data_size, const u16 position);
  // Extraction
  /** @brief Extracts the first element of the vector and returns it
  *
  * Extracts the first element of the vector and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the vector.
  *
  * @return void* data at the first position of the vector
  */
  void* extractFirst ();
  /** @brief Extracts the last element of the vector and returns it
  *
  * Extracts the last element of the vector and removes it. 
  * Notice that the data must be freed once you are finished using it as it's
  * no longer responsability of the vector.
  *
  * @return void* data at the last position of the vector
  */
  void* extractLast ();
  /** @brief Extracts the element of the vector at the position indicated
  *   and returns it
  *
  * Extracts the element of the vector at the position indicated 
  * and removes it from the vector. Notice that the data must be freed once 
  * you finished using it as it's no longer responsability of the vector.
  *
  * @return void* data at the indicated position of the vector
  * @param position position of the element we want to extract
  */
  void* extractAt (const u16 position);
  // Miscellaneous
  /** @brief Concatenates two vector storing the result at origin
  *
  * Concatenates the source to the vector, the result of it will have a 
  * capacity of vector's capacity plus src capacity's. Notice that the src
  * vector won't be modified during the execution. In case the vector is null 
  * kErrorCode_Null_Vector will be returned and in case the the src is null
  * kErrorCode_Null_Pointer_Parameter_Received. If there's a problem during
  * the allocation of the new vector kErrorCode_Error_Trying_To_Allocate_Memory
  * will be returned.
  *
  * @return s16 status of the operation once finished
  * @param src vector we want to concatenate to our origin                                                       
  */
  s16 concat (const Vector &src);
  /** @brief Applies the callback method to the vector
  *
  * Applies a memory node function to the set of elements of the vector.
  *
  * @return u16 number of elements traveled
  * @param callback function of memory node that will be applied to the set
  */
  u16 traverse(s16(MemoryNode::*callback)()) const;
  /** @brief Prints the content of the elements of the vector
  *
  * Prints the content of the elements of the vector
  *
  */
  void print () const;



  //u16 traverse(s16 callback);

 private:
  u16 head_;
  u16 tail_;
  u16 capacity_;
  MemoryNode *storage_;
  //function pointer to memory node for our callbacks
  //s16 (MemoryNode::*mem_node_fp_)() = nullptr;
};
#endif //__ADT_VECTOR_H__











