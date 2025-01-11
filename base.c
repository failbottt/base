#include "base.h"

Arena 
arena_alloc_reserve(u64 reserve_size) 
{
    Arena result = {0};

    u64 size = reserve_size;
    if (size <= 0) {
        size = MEM_DEFAULT_RESERVE_SIZE;
    }

    if (!IsPow2OrZero(size)) {
        size = AlignUpPow2(size, MEM_MAX_ALIGN);
    }

    result.data = (void*)malloc(sizeof(u8)*size);
    result.current = result.data;
    result.previous = 0;
    result.size = size;
    result.alignment = sizeof(void*);

    return result;
}

Arena
arena_alloc(void)
{
    Arena result = arena_alloc_reserve(MEM_DEFAULT_RESERVE_SIZE);
    return result;
}

void
arena_free(Arena *arena)
{
    arena->current = 0;
    arena->previous = 0;
}

void
arena_destroy(Arena *arena)
{
    if (arena->data != 0) {
        free(arena->data);
    }
    arena->current = 0;
    arena->previous = 0;
}

void
arena_resize(Arena *arena)
{
    u64 i = MEM_DEFAULT_RESERVE_SIZE;
    void *buf = malloc(sizeof(u8)*i);
    memcpy(buf, arena->current, arena->size);
    arena->current = buf;
    arena->pos = arena->pos + i;
    arena->size = arena->size + i;
}


void
arena_push(Arena *arena, void* data, u64 size)
{
    u64 buf_size = size;
    if (!IsPow2OrZero(size)) {
        buf_size = AlignUpPow2(size, 64);
    }

    if (arena->pos + buf_size >= arena->size) {
        arena_resize(arena);
    }

    arena->previous = arena->current;
    memcpy(arena->data+arena->pos, data, buf_size);
    arena->current = arena->data;
    arena->pos = arena->pos+buf_size;
}
