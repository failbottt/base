#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FAILBOT_BASE
#define _FAILBOT_BASE

#define c_linkage extern

#define link_function c_linkage


typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef float    f32;
typedef double   f64;
typedef s8 b8;

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)
#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) ((U64)(x) << 40llu)

#if !defined(MEM_DEFAULT_RESERVE_SIZE)
# define MEM_DEFAULT_RESERVE_SIZE MB(1)
#endif

#if !defined(MEM_MAX_ALIGN)
# define MEM_MAX_ALIGN 64 
#endif

#define MEM_INITIAL_COMMIT KB(4)
#define MEM_INTERNAL_MIN_SIZE AlignUpPow2(sizeof(Arena), MEM_MAX_ALIGN)

#define AlignUpPow2(x,p) (((x) + (p) - 1)&~((p) - 1))
#define AlignDownPow2(x,p) ((x)&~((p) - 1))
#define IsPow2OrZero(x) (((x)&((x)-1)) == 0)

#define memory_zero(p,z) memset((p), 0, (z))

// Strings
// ------------
typedef struct {
    int length;
    u8* str;
} String;

#define new_string(s) (String){strlen(s), (u8*)s}

// Arenas
// ------------
typedef struct Arena {
    u64  size;
    u64  alignment;
    u64  pos;
    void *current;
    void *previous;
    void *data;
} Arena;

Arena arena_alloc(void);
Arena arena_alloc_reserve(u64 size);
void  arena_resize(Arena *arena);
void  arena_free(Arena *arena);
void  arena_destroy(Arena *arena);
void  arena_push(Arena *arena, void* data, u64 size);

#endif
