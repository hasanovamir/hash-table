#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

int CountHashFunction (char* str, int str_len)
{
    DEBUG_ASSERT (str != nullptr);

    int cur_hash = 0;

    for (int i = 0; i < str_len; i++) {
        cur_hash = (cur_hash << 5) + cur_hash + str[i];
    }

    int hash = cur_hash % kHashMapCap;

    return (cur_hash < 0) ? hash + kHashMapCap : hash;
}

//————————————————————————————————————————————————————————————————————————————————