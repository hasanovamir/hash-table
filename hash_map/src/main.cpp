#include "hash_map.h"

int main ()
{
    hash_ctx_t* hash_ctx = nullptr;
    InitHashMap (&hash_ctx);
    HashDump (hash_ctx, "pisun.csv");

    return 0;
}