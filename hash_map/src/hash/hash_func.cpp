#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

static int HashFunc5 (char* str, int str_len);
static int HashFunc4 (char* str, int str_len);
static int HashFunc3 (char* str, int str_len);
static int HashFunc2 (char* str, int str_len);
static int HashFunc1 (char* str, int str_len);

//————————————————————————————————————————————————————————————————————————————————

int CountHashFunction (char* str, int str_len) {
    int hash = 0;
#if defined(HASH_5)
    hash = HashFunc5(str, str_len);
#elif defined(HASH_4)
    hash = HashFunc4(str, str_len);
#elif defined(HASH_3)
    hash = HashFunc3(str, str_len);
#elif defined(HASH_2)
    hash = HashFunc2(str, str_len);
#elif defined(HASH_1)
    hash = HashFunc1(str, str_len);
#else
    hash = HashFunc5 (str, str_len);
#endif
    return hash;
}

//————————————————————————————————————————————————————————————————————————————————

static int HashFunc1 (char* str, int str_len)
{
    return 0;
}

//————————————————————————————————————————————————————————————————————————————————

static int HashFunc2 (char* str, int str_len)
{
    DEBUG_ASSERT (str != nullptr);

    return str[0];
}

//————————————————————————————————————————————————————————————————————————————————

static int HashFunc3 (char* str, int str_len)
{
    return str_len;
}

//————————————————————————————————————————————————————————————————————————————————

static int HashFunc4 (char* str, int str_len)
{
    int hash = 0;

    for (int i = 0; i < str_len; i++) {
        hash += str[i];
    }

    return hash;
}

//————————————————————————————————————————————————————————————————————————————————

static int HashFunc5 (char* str, int str_len) 
{
    DEBUG_ASSERT (str != nullptr);

    unsigned int result = 0;

    __asm__ volatile (
    "movl  $5381, %%eax\n"
    "movq  %1   , %%r8 \n"
    "movl  %2   , %%ecx\n"
    ".hash_count_loop: \n"

    "shll   $2    , %%eax   \n"
    "leal   (%%eax, %%eax, 8), %%eax   \n"
    "movzbl (%%r8), %%edx   \n"
    "addl   %%edx , %%eax   \n"
    "incq   %%r8            \n"
    "loop   .hash_count_loop\n"

    "movl   $10000, %%ecx\n"
    "xorl   %%edx , %%edx\n"
    "divl   %%ecx        \n"
    "movl   %%edx , %0   \n"

    : "=r" (result)
    : "r" (str), "r" (str_len)
    : "eax", "ecx", "edx", "r8", "memory", "cc"
    );

    // unsigned int cur_hash = 0;

    // for (int i = 0; i < str_len; i++) {
    //     cur_hash = (cur_hash << 5) + cur_hash + str[i];
    // }

    // unsigned hash = cur_hash % kHashMapCap;

    // return (int) hash;
    
    return (int)result;
}

//————————————————————————————————————————————————————————————————————————————————