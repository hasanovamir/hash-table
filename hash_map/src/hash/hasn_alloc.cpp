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
        if (ListInit (&hash->src[i]) != list_err_t::success) {
            return hash_err_t::allocate_err;
        }
    }

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

hash_err_t HashInitNewStr (int str_len, char** buf)
{
    *buf = (char*) calloc (str_len + 1, sizeof (char));
    if (*buf == nullptr) {
        PRINTERR (hash_err_t::allocate_err);
        return hash_err_t::allocate_err;
    }

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

void HashDestroy (hash_ctx_t* hash_ctx)
{
    for (int j = 0; j < kHashMapCap; j++) {
        list_t* cur_list = hash_ctx->src[j];

        for (int i = 0; i < cur_list->size + 1; i++) {
            free (cur_list->data[i]);
        }

        ListDestroy (cur_list);
    }

    free (hash_ctx->src);
    free (hash_ctx     );
}

//————————————————————————————————————————————————————————————————————————————————