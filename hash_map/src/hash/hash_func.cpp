#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

static u_int64_t HashFunc5 (char* str, int str_len);
static u_int64_t HashFunc4 (char* str, int str_len);
static u_int64_t HashFunc3 (char* str, int str_len);
static u_int64_t HashFunc2 (char* str, int str_len);
static u_int64_t HashFunc1 (char* str, int str_len);

//————————————————————————————————————————————————————————————————————————————————

u_int64_t CountHashFunction (char* str, int str_len)
{
    u_int64_t hash = 0;

#if defined (HASH_5)
    hash = HashFunc5 (str, str_len);
#elif defined (HASH_4)
    hash = HashFunc4 (str, str_len);
#elif defined (HASH_3)
    hash = HashFunc3 (str, str_len);
#elif defined (HASH_2)
    hash = HashFunc2 (str, str_len);
#elif defined (HASH_1)
    hash = HashFunc1 (str, str_len);
#else
    hash = HashFunc5 (str, str_len);
#endif
    return hash;
}

//————————————————————————————————————————————————————————————————————————————————

static u_int64_t HashFunc1 (char* str, int str_len)
{
    return 0;
}

//————————————————————————————————————————————————————————————————————————————————

static u_int64_t HashFunc2 (char* str, int str_len)
{
    DEBUG_ASSERT (str != nullptr);

    return str[0];
}

//————————————————————————————————————————————————————————————————————————————————

static u_int64_t HashFunc3 (char* str, int str_len)
{
    return str_len;
}

//————————————————————————————————————————————————————————————————————————————————

static u_int64_t HashFunc4 (char* str, int str_len)
{
    u_int64_t hash = 0;

    for (int i = 0; i < str_len; i++) {
        hash += str[i];
    }

    return hash;
}

//————————————————————————————————————————————————————————————————————————————————

static u_int64_t HashFunc5 (char* str, int str_len) 
{
    DEBUG_ASSERT (str != nullptr);

    u_int64_t result = 0;

    __asm__ volatile (
    "movq  $5381, %%rax\n"
    "movq  %1   , %%r8 \n"
    "movl  %2   , %%ecx\n"
    ".hash_count_loop: \n"

    "shlq   $2    , %%rax   \n"
    "leaq   (%%rax, %%rax, 8), %%rax   \n"
    "movq   (%%r8), %%rdx   \n"
    "addq   %%rdx , %%rax   \n"
    "incq   %%r8            \n"
    "loop   .hash_count_loop\n"

    : "=r" (result)
    : "r" (str), "r" (str_len)
    : "rax", "ecx", "rdx", "r8", "memory", "cc"
    );

    // unsigned int cur_hash = 0;

    // for (int i = 0; i < str_len; i++) {
    //     cur_hash = (cur_hash << 5) + cur_hash + str[i];
    // }

    // unsigned hash = cur_hash % kHashMapCap;

    // return (int) hash;
    
    return (u_int64_t) result;
}

//————————————————————————————————————————————————————————————————————————————————