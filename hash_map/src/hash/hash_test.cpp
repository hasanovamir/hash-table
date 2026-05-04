#include "hash_map.h"

//————————————————————————————————————————————————————————————————————————————————

static void HashTestProcess (hash_ctx_t* hash_ctx, char* buffer, int file_size);

//————————————————————————————————————————————————————————————————————————————————

hash_err_t HashTest (hash_ctx_t* hash_ctx, char* file_name)
{
    DEBUG_ASSERT (file_name != nullptr);

    int file_size = GetFileSize (file_name);

    char* buffer = nullptr;

    if (InitBuffer (&buffer  , file_size        ) != hash_err_t::success)
        return hash_err_t::allocate_err ;
    if (ReadSrc    (file_name, file_size, buffer) != hash_err_t::success)
        return hash_err_t::open_file_err;

    HashTestProcess (hash_ctx, buffer, file_size);

    free (buffer);

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

void HashTestProcess (hash_ctx_t* hash_ctx, char* buffer, int file_size)
{
    DEBUG_ASSERT (hash_ctx != nullptr);
    DEBUG_ASSERT (buffer   != nullptr);

    int src_pos = 0;

    char      str[kCommonStringSize] = "";
    u_int64_t str_len                = 0;
    bool      load_factor            = false;
    u_int64_t hash                   = 0;

    while (src_pos < file_size) {
        str_len      = CopyCurStr      (buffer + src_pos, str, &src_pos, file_size);
        //str[str_len] = '0';
        // SPEED_TEST (hash = CountHashFunction (str, str_len), "speed_test.txt")
        hash         = CountHashFunction (str, str_len);
        load_factor  = HashFindElement (hash_ctx, str, str_len, hash);
    }
}

//————————————————————————————————————————————————————————————————————————————————

int CopyCurStr (char* src, char* dst, int* pos, int file_size)
{
    DEBUG_ASSERT (src != nullptr);
    DEBUG_ASSERT (dst != nullptr);
    DEBUG_ASSERT (pos != nullptr);

    int str_len = 0;

    while (*pos < file_size && isalpha (*src)) {
        *(dst++) = *(src++);
        (*pos)++;
        str_len++;
    }

    *dst = '\0';

    while (*pos < file_size && !isalpha (*(src++))) {
        (*pos)++;
    }

    return str_len;
}

//————————————————————————————————————————————————————————————————————————————————

