#include "base.c"

typedef struct Test {
    u64 x,y;
} Test;

int main(void)
{
    Arena arena = arena_alloc();

    String s1 = new_string("99990--");

    arena_push(&arena, s1.str, s1.length);

    arena_push(&arena, new_string("77").str, 2);

    printf("%.*s\n", 12, (u8*)arena.data);

    /* u8* hw = (u8*)"Hello, world!"; */
    /* String s1 = (String){strlen((const char*)hw), hw}; */


    /* Test t = {0,0}; */
    /* arena_push(&arena, &t, 4); */













    /* printf("%s\n", Stringify(GB(1))); */
    /* printf("GB: %d\n", GB(1)); */




    /* arena_free(&arena); */
    /* arena_destroy(&arena); */
    return 0;
}
