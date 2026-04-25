#include "hash_map.h"

int main (int argc, char** argv)
{
    hash_ctx_t* hash_ctx = nullptr;
    if (InitHashMap (&hash_ctx) != hash_err_t::success) return 1;

    char* file_name = nullptr;
    if (GetFileName  (argc, argv, &file_name) != hash_err_t::success) return 1;
    if (TakeHashData (hash_ctx  ,  file_name) != hash_err_t::success) return 1;

    HashDump (hash_ctx, "pisun.csv");

    return 0;
}