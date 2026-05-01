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

        int list_size = cur_list->size;
        list_size = (list_size == 0) ? 0 : list_size + 1; 

        fprintf (csv_file, "Hash = %d |", j);

        for (int i = 1; i < list_size; i++) {
            if (cur_list->data[i].str == nullptr) break;
            fprintf (csv_file, " idx = %d; val = %s |", i, cur_list->data[i].str);
        }

        fprintf (csv_file, "\n");
    }

    fclose (csv_file);

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

hash_err_t HashDumpForData (hash_ctx_t* hash_ctx, const char* file_name)
{
    DEBUG_ASSERT (hash_ctx != nullptr);

    FILE* csv_file = fopen (file_name, "w");
    if (csv_file == nullptr) {
        PRINTERR (hash_err_t::open_file_err);
        return hash_err_t::open_file_err;
    }

    for (int j = 0; j < kHashMapCap; j++) {

        list_t* cur_list = hash_ctx->src[j];

        int list_size = cur_list->size;
        list_size = (list_size == 0) ? 0 : list_size + 1; 

        fprintf (csv_file, "%d %d\n", j, list_size);
    }

    fclose (csv_file);

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————