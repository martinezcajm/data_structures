// common_def.h
// Toni Barella
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
//Implementation of common utilities of our API like the error codes

#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#define VERBOSE_
/** Error code enum. 
*  Enum with the different error codes.
*/
typedef enum
{
	kErrorCode_Ok = 0,
	kErrorCode_Null_Memory_Node = -1,
	kErrorCode_Null_Pointer_Parameter_Received = -2,
  kErrorCode_Null_Pointer_Reference_Received = -3,
  kErrorCode_Error_Trying_To_Allocate_Memory = -4,
  kErrorCode_Null_Data = -5,
  kWarningCode_Strange_Operation = -6
} ErrorCode;

#endif // __COMMON_DEF_H__