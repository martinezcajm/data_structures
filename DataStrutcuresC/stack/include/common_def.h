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
  kWarningCode_Strange_Operation = -6,
  kErrorCode_Null_Vector = -7,
  kErrorCode_Out_Of_Range_Index = -8,
  kErrorCode_Vector_Is_Full = -9,
  kErrorCode_Resize_Loss_Of_Data = -10,
  kErrorCode_Null_List = -11,
  kErrorCode_List_Is_Full = -12,
  kErrorCode_Null_Queue = -13,
  kErrorCode_Queue_Is_Full = -14,
  kErrorCode_Null_Stack = -15,
  kErrorCode_Stack_Is_Full = -16
} ErrorCode;

#endif // __COMMON_DEF_H__