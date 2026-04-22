#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

hash_err_t InitHashMap (hash_ctx_t** hash_ctx)
{
    *hash_ctx = (hash_ctx_t*) calloc (1, sizeof (hash_ctx_t));
    if (*hash_ctx == nullptr) {
        PRINTERR (hash_err_t::allocate_err);
        return hash_err_t::allocate_err;
    }

    list_t** src = (list_t**) calloc (kHashMapCap, sizeof (list_t*));
    if (src == nullptr) {
        PRINTERR (hash_err_t::allocate_err);
        return hash_err_t::allocate_err;
    }

    (*hash_ctx)->src = src;
    hash_ctx_t* hash = *hash_ctx;

    for (int i = 0; i < kHashMapCap; i++) {
        list_t* cur_list = nullptr;

        if (ListInit (&cur_list) != list_err_t::success) {
            return hash_err_t::allocate_err;
        }
        
        hash->src[i] = cur_list;
    }

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————