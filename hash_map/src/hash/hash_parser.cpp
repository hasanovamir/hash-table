#include "hash_map.h"

static hash_err_t InitBuffer (char** src,int size);
static hash_err_t ReadSrc    (const char* file_name, int file_size, char* src_buffer);
static int CountNumbers (int val);
static void ParseHashData (hash_ctx_t* hash_ctx, char* buffer, int file_name);

//————————————————————————————————————————————————————————————————————————————————

hash_err_t TakeHashData (hash_ctx_t* hash_ctx, char* file_name)
{
    DEBUG_ASSERT (file_name != nullptr);

    int file_size = GetFileSize (file_name);

    char* buffer = nullptr;

    if (InitBuffer (&buffer  , file_size        ) != hash_err_t::success)
        return hash_err_t::allocate_err ;
    if (ReadSrc    (file_name, file_size, buffer) != hash_err_t::success)
        return hash_err_t::open_file_err;

    ParseHashData (hash_ctx, buffer, file_size);

    free (buffer);

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

hash_err_t InitBuffer (char** src,int size)
{
    *src = (char*) calloc (size , sizeof (char));

    if (src == nullptr) {
        PRINTERR (hash_err_t::allocate_err)
        return hash_err_t::allocate_err;
    }

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

hash_err_t ReadSrc (const char* file_name, int file_size, char* src_buffer)
{
    FILE* file = fopen (file_name, "r");
    if (file == nullptr) {
        PRINTERR (hash_err_t::open_file_err)
        return hash_err_t::open_file_err;
    }

    if (fread (src_buffer, sizeof (char), file_size, file) != file_size) {
        PRINTERR (hash_err_t::invalid_file_size)
        return hash_err_t::invalid_file_size;
    }

    fclose (file);

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————

void ParseHashData (hash_ctx_t* hash_ctx, char* buffer, int file_name)
{
    DEBUG_ASSERT (buffer != nullptr);

    int pos = 0;

    while (pos < file_name) {
        int str_len = atoi (buffer + pos);
        int num_len = CountNumbers (str_len);
        pos += num_len;
        HashInsert (hash_ctx, buffer + pos, str_len);
        pos += str_len;
    }
}

//————————————————————————————————————————————————————————————————————————————————

int CountNumbers (int val)
{
    int n = 0;

    while (val) {
        n++;
        val /= 10;
    }

    return (n == 0) ? 1 : n;
}

//————————————————————————————————————————————————————————————————————————————————

hash_err_t GetFileName (int argc, char** argv, char** file_name)
{
    if (argc < 2) {
        PRINTERR (hash_err_t::no_data_file)
        return hash_err_t::no_data_file;
    }

    *file_name = argv[1];

    return hash_err_t::success;
}

//————————————————————————————————————————————————————————————————————————————————