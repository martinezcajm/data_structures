// platform_types.h
// Toni Barella
// Jose Maria Martinez
// Algoritmos & Inteligencia Artificial
// ESAT 2017/2018
// Redefinition of our basic types using the stdint library to avoid problems
// between different arquitectures.
#ifndef __PLATFORM_TYPES_H__
#define __PLATFORM_TYPES_H__

#include <cstdint>

typedef uint8_t 		u8;
typedef int_least8_t 	s8;
typedef uint16_t 		u16;
typedef int_least16_t 	s16;
typedef uint32_t 		u32;
typedef int_least32_t 	s32;
typedef uint64_t 		u64;
typedef int_least64_t	s64;

typedef uint8_t boolean;
#define TRUE 			1
#define FALSE 			0

typedef unsigned int BIT_FIELD;

#endif
