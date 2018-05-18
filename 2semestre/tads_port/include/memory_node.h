// memory_node.h
// Toni Barella
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Implementation of memory node and it's functionalities.
#ifndef __MEMORY_NODE_H__
#define __MEMORY_NODE_H__

#include "platform_types.h"

class MemoryNode
{
 public:
   /** @brief Memory Node constructor
   *
   * Base constructor of memory node
   *
   * @return *MemoryNode
   */
   MemoryNode();
   /** @brief MemoryNode copy constructor
   *
   * Memory node copy constructor.
   *
   * @return *MemoryNode
   * @param o memory node to be copied
   */
   MemoryNode(const MemoryNode& o);
   /** @brief MemoryNode = operation
   *
   * returns a reference to memory node equal to mn
   *
   * @return &MemoryNode
   * @param mn memory node to be copied
   */
   MemoryNode& operator = (const MemoryNode &mn);
   /** @brief Initializes the memory node
   *
   * Initializes the memory node. Note that the constructor
   * already initializes the node.
   *
   * @return s16 ErrorCode of the execution
   */
   s16 init();
   /** @brief Frees the memory node (Destructor)
   *
   * Destroys the memory node. In case you wish to mantain the data of the
   * memory node after it's destruction set soft as true otherwise just
   * ignore the parameter or pass false
   *
   * @return s16 ErrorCode of the execution
   * @param soft in case false is passed data will be released, otherwise the
   * data won't be released and it's your responsability to free it.
   * free
   */
   s16 free_mn (boolean soft = false);
   /** @brief Resets the memory node
   *
   * Sets the data and size of the memory node to it's default values.
   *
   * @return s16 ErrorCode of the execution
   */
   s16 reset ();
   /** @brief getter of data
   *
   * Returns a pointer to data. In case a null pointer wass passed it will
   * return null
   *
   * @return void* reference to the data of the memory node
   */
   void* data () const;
   /** @brief gets the data size
   *
   * Returns the size of the data. In case a null pointer wass passed it will
   * return a 0
   *
   * @return u16 size of the data
   */
   u16 size () const;
   /** @brief gettter of next
   *
   * Returns the next MemoryNode
   *
   * @return MemoryNode* reference to the next memory node
   */
   MemoryNode *next () const;
   /** @brief setter of next
   *
   * Sets the next MemoryNode of the MemoryNode. Take into account that this
   * function won't release the old next MemoryNode.
   *
   * @return s16 ErrorCode of the execution
   * @param next_node new pointer to the next memory_node
   */
   s16 setNext (MemoryNode *next_node);
   /** @brief gettter of previous
   *
   * Returns the previous MemoryNode
   *
   * @return MemoryNode* pointer to the previous memory node
   */
   MemoryNode *prev () const;
   /** @brief setter of previous
   *
   * Sets the previous MemoryNode of the MemoryNode. Take into account that this
   * function won't release the old previous MemoryNode.
   *
   * @return s16 ErrorCode of the execution
   * @param prev_node new pointer to the previous memory_node
   */
   s16 setPrev (MemoryNode *prev_node);
   /** @brief Sets new data to the memory node
   *
   * Resets the old data of the memory node and sets it to it's new value
   * updating it's size with the bytes parameter. In case src is null it will
   * return a  kWarningCode_Strange_Operation and WON'T reset the old data. In
   * case a null pointer was passed it will return kErrorCode_Null_Memory_Node
   *
   * @return s16 ErrorCode of the execution
   * @param src  source of the new data of the memory node
   * @param bytes size of the data the memory node will be referencing
   */
   s16 setData (void *src, u16 bytes);
   /** @brief Sets all the data to the value passed
   *
   * Applies a memset of the value passed to the data of the memory node. In
   * case a null pointer wass passed it will return kErrorCode_Null_Memory_Node.
   * In case the data of the memory node is null it will return a
   * kErrorCode_Null_Data
   *
   * @return s16 ErrorCode of the execution
   * @param value we want to memset to the data
   */
   s16 memSet (u8 value);
   /** @brief allocates the data passe by src and sets it to the memory node.
   *
   * Copies the data passed in src and sets the pointer of data to this new
   * data. If a size of 0 bytes is passed a kWarningCode_Strange_Operation will
   * be returned and NOTHING will be done to the node. If the source is null a
   * kErrorCode_Null_Pointer_Parameter_Received will be returned. In case a
   * null pointer was passed it will return kErrorCode_Null_Memory_Node. If the
   * allocation of the new data went wrong it will return a
   * kErrorCode_Error_Trying_To_Allocate_Memory.
   *
   * @return s16 ErrorCode of the execution
   * @param src  source of the data that will be copied
   * @param bytes size of the new data
   */
   s16 memCopy (void *src, u16 bytes);
   /** @brief Concats the data of the memory  with thedata passed at source
   *
   * Allocates memory for the data result from the concatenation of the memory
   * node data with the data at source. In case a null memory node was passed
   * it will return kErrorCode_Null_Memory_Node. If the data of the memory node
   * is null a kErrorCode_Null_Data will be returned. If the source is null a
   * kWarningCode_Strange_Operation will be returned. If there's an error
   * allocating the memory a kErrorCode_Error_Trying_To_Allocate_Memory will be
   * returned.
   * @return s16 ErrorCode of the execution
   * @param src  source we want to concat to the data
   * @param bytes size of the data to concat
   */
   s16 memConcat (void *src, u16 bytes);
   /** @brief Applies a mask to the data
   *
   * Applies an and (&) mask to the data of the memory node byte to byte. In
   * case a null memory node was passed it will return
   * kErrorCode_Null_Memory_Node.
   * @return s16 ErrorCode of the execution
   * @param mask mask we want to apply to the data
   */
   s16 memMask (u8 mask) const;
   /** @brief prints the content of data
   *
   * Prints the data byte to byte in hexadecimal. In case a null memory node
   * was passed it will print The node is null. If data is null it will print
   * The data is null
   * @return s16 status of the function
   */
   s16 print ();

 private:
   void *data_;
   u16 size_;
   MemoryNode *next_;
   MemoryNode *prev_;
   /** @brief memory node destructor
   *
   * Destructor of memory node. Note that you need to call free_mn to destroy
   * a memory node.
   *
   * @return void
   */
   ~MemoryNode();
};

#endif // __MEMORY_NODE_H__