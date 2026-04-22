#pragma once

//--------------------------------------------------------------------------------

#include "list.h"

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
};

//--------------------------------------------------------------------------------

hash_err_t HashDump (hash_ctx_t* hash_ctx, const char* file_name);
hash_err_t InitHashMap (hash_ctx_t** hash_ctx);

//--------------------------------------------------------------------------------