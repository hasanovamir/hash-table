#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

hash_err_t HashInsert (hash_ctx_t* hash_ctx, char* str, int str_len)
{
    DEBUG_ASSERT (str != nullptr);

    // SPEED_TEST (u_int64_t hash = CountHashFunction (str, str_len), "speed_test.txt")
    u_int64_t hash = CountHashFunction (str, str_len);

    bool load_factor = HashFindElement (hash_ctx, str, str_len, hash);
    if (load_factor == true) return hash_err_t::success;

    str_ctx_t str_ctx = {};
    if (HashInitNewStr (str_len, &str_ctx) != hash_err_t::success) return hash_err_t::allocate_err;

    memcpy (str_ctx.str, str, str_len);
    str_ctx.hash    = hash;
    str_ctx.str_len = str_len;

    list_err_t list_err = ListAdd (hash_ctx->src[hash % kHashMapCap], str_ctx);
    if (list_err != list_err_t::success) {
        return (hash_err_t) list_err;
    }
    
    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

bool HashFindElement (hash_ctx_t* hash_ctx, char* str, int str_len, u_int64_t hash)
{
    DEBUG_ASSERT (hash_ctx != nullptr);

    list_t* target_list = hash_ctx->src[hash % kHashMapCap];
    if (target_list == nullptr) {
        PRINTERR (target_list == nullptr);
        return false;
    }

    for (int i = 1; i < target_list->size + 1; i++) {
        str_ctx_t str_ctx = target_list->data[i];
        // if (str_ctx.str_len != str_len) continue;
        // if (str_ctx.hash    != hash   ) continue;
        if (strncmp (str, str_ctx.str, str_len) == 0) return true;
    }

    return false;
}

//————————————————————————————————————————————————————————————————————————————————