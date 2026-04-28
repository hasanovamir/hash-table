#pragma once

//--------------------------------------------------------------------------------

#include "list.h"
#include "general_io_file_func.h"

//--------------------------------------------------------------------------------

const int kHashMapCap = 10000;

//--------------------------------------------------------------------------------

struct hash_ctx_t
{
    list_t** src;
} ;

//--------------------------------------------------------------------------------

enum class hash_err_t
{
    success               = 0,
    invalid_index         = 1,
    invalid_capacity_size = 2,
    allocate_err          = 3,
    up_size_err           = 4,
    get_next_free_err     = 5,
    change_next_err       = 6,
    change_prev_err       = 7,
    open_file_err         = 8,
    sys_func_err          = 9,
    invalid_free_val      = 10,
    invalid_head          = 11,
    invalid_tail          = 12,
    invalid_size          = 13,
    incorrect_numbering   = 14,
    invalid_file_size     = 15,
    no_data_file          = 16,
};

//--------------------------------------------------------------------------------

hash_err_t HashDump (hash_ctx_t* hash_ctx, const char* file_name);
hash_err_t InitHashMap (hash_ctx_t** hash_ctx);
int CountHashFunction (char* str, int str_len);
hash_err_t HashInsert (hash_ctx_t* hash_ctx, char* str, int str_len);
hash_err_t TakeHashData (hash_ctx_t* hash_ctx, char* file_name);
hash_err_t GetFileName  (int argc, char** argv, char** file_name);
bool HashFindElement (hash_ctx_t* hash_ctx, char* str, int str_len);
hash_err_t HashInitNewStr (int str_len, char** buf);
void HashDestroy (hash_ctx_t* hash_ctx);
hash_err_t HashDumpForData (hash_ctx_t* hash_ctx, const char* file_name);

//--------------------------------------------------------------------------------