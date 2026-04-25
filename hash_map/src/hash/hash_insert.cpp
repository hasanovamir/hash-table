#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

hash_err_t HashInsert (hash_ctx_t* hash_ctx, char* str, int str_len)
{
    DEBUG_ASSERT (str != nullptr);

    char* buf = (char*) calloc (str_len + 1, sizeof (char));
    if (buf == nullptr) {
        PRINTERR (hash_err_t::allocate_err);
        return hash_err_t::allocate_err;
    }

    memcpy (buf, str, str_len);

    int hash = CountHashFunction (buf, str_len);

    list_err_t list_err = ListAdd (hash_ctx->src[hash], buf);
    if (list_err != list_err_t::success) {
        return (hash_err_t) list_err;
    }

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————