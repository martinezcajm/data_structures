// memory_node.h
// Toni Barella
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Implementation of memory node and it's functionalities.
#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__

#include "platform_types.h"
//#include "memory_node.h"
#include "adt_list.h"

class MemoryManager
{
 public:
   /** @brief Gets the instance of our MemoryManager
   *
   * In charge of creating our MemoryManager singleton in case it doesn't exist
   * or return it's instance if it exists.
   *
   * @return GameManager& instance
   */
   static MemoryManager& instance();      
   /** @brief Applies a mask to the data
   *
   * Applies an and (&) mask to the data of the memory node byte to byte. In
   * case a null memory node was passed it will return
   * kErrorCode_Null_Memory_Node.
   * @return s16 ErrorCode of the execution
   * @param mask mask we want to apply to the data
   */
   void* malloc(u16 size) const;
   /** @brief prints the content of data
   *
   * Prints the data byte to byte in hexadecimal. In case a null memory node
   * was passed it will print The node is null. If data is null it will print
   * The data is null
   * @return s16 status of the function
   */
   s16 free(void *p, u16 size);   

 private:
   List *sixteenb_nodes_;
   List *thirtytwob_nodes_;
   List *sixtyfourb_nodes_;
   static const u16 initial_capacity_sixteen_ = 100;
   static const u16 initial_capacity_thirtytwo_ = 50;
   static const u16 initial_capacity_sixtyfour_ = 25;
   //List *used_nodes_;
   /** @brief Memory Node constructor
   *
   * Base constructor of memory node
   *
   * @return *MemoryNode
   */
   MemoryManager();
   /** @brief MemoryNode copy constructor
   *
   * Memory node copy constructor.
   *
   * @return *MemoryNode
   * @param o memory node to be copied
   */
   MemoryManager(const MemoryManager& o) {};
   /** @brief MemoryNode = operation
   *
   * returns a reference to memory node equal to mn
   *
   * @return &MemoryNode
   * @param mn memory node to be copied
   */
   MemoryManager& operator = (const MemoryManager &mn) {};
   /** @brief memory node destructor
   *
   * Destructor of memory node. Note that you need to call free_mn to destroy
   * a memory node.
   *
   * @return void
   */
   ~MemoryManager();
   /** @brief Initializes the memory manager
   *
   * Initializes the memory manager.
   *
   * @return s16 ErrorCode of the execution
   */
   s16 init();
   /** @brief clears the memory alloced by the memory manager
   *
   *  Clears the memory alloced by the memory manager. This method will be called on destruction.
   *
   * @return s16 ErrorCode of the execution
   */
   s16 clear_memory();

};

#endif // __MEMORY_NODE_H__