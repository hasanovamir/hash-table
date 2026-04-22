#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

hash_err_t HashDump (hash_ctx_t* hash_ctx, const char* file_name)
{
    DEBUG_ASSERT (hash_ctx != nullptr);

    FILE* csv_file = fopen (file_name, "w");
    if (csv_file == nullptr) {
        PRINTERR (hash_err_t::open_file_err);
        return hash_err_t::open_file_err;
    }

    for (int j = 0; j < kHashMapCap; j++) {

        list_t* cur_list = hash_ctx->src[j];
        int     list_cap = cur_list->capacity;

        fprintf (csv_file, "Hash = %d |", j);

        for (int i = 0; i < list_cap; i++) {
            fprintf (csv_file, " idx = %d; val = %s |", i, cur_list->data[i]);
        }
        fprintf (csv_file, "\n");
    }

    fclose (csv_file);

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————