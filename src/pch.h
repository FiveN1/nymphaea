#ifndef PCH_H
#define PCH_H
// standard library
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#include<string.h>
#include<time.h>

#include<math.h>

// Platform specific
#include<Windows.h>

// type defines
// https://en.wikipedia.org/wiki/C_data_types
#ifdef CUSTOM_TYPES
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef unsigned long long  u64;

typedef char                i8;
typedef short               i16;
typedef long                i32;
typedef long long           i64;
#endif

// debug functions
#include"nymphaea_lib/core/debug/print/print.h"
#include"nymphaea_lib/core/debug/assert/assert.h"
#include"nymphaea_lib/core/debug/memory_debug/mem_debug.h"
#include"nymphaea_lib/core/debug/time/time.h"

// useful functions
#include"nymphaea_lib/core/functions/string_format/string_format.h"

#endif PCH_H