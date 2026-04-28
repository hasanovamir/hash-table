#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

hash_err_t HashInsert (hash_ctx_t* hash_ctx, char* str, int str_len)
{
    DEBUG_ASSERT (str != nullptr);

    bool load_factor = HashFindElement (hash_ctx, str, str_len);
    if (load_factor == true) return hash_err_t::success;

    char* buf = nullptr;
    if (HashInitNewStr (str_len, &buf) != hash_err_t::success) return hash_err_t::allocate_err;

    memcpy (buf, str, str_len);

    int hash = CountHashFunction (buf, str_len);

    list_err_t list_err = ListAdd (hash_ctx->src[hash], buf);
    if (list_err != list_err_t::success) {
        return (hash_err_t) list_err;
    }

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

bool HashFindElement (hash_ctx_t* hash_ctx, char* str, int str_len)
{
    DEBUG_ASSERT (hash_ctx != nullptr);

    int hash = CountHashFunction (str, str_len);

    list_t* target_list = hash_ctx->src[hash];
    if (target_list == nullptr) {
        PRINTERR (target_list == nullptr);
        return false;
    }

    for (int i = 1; i < target_list->size + 1; i++) {
        if (strncmp (str, target_list->data[i], str_len) == 0) return true;
    }

    return false;
}

//————————————————————————————————————————————————————————————————————————————————