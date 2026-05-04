#pragma once

//--------------------------------------------------------------------------------

#include <ctype.h>
#include <immintrin.h>
#include "list.h"
#include "general_io_file_func.h"

//--------------------------------------------------------------------------------

const int kHashMapCap = 10007;

//--------------------------------------------------------------------------------

struct hash_ctx_t
{
    list_t** src;
    int calls;
};

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

extern "C" {
bool HashFindElementAsm (hash_ctx_t* hash_ctx, char* str, u_int64_t str_len, u_int64_t hash);
}

hash_err_t InitHashMap       (hash_ctx_t** hash_ctx                                 );
hash_err_t InitBuffer        (char** src , int    size                              );
hash_err_t HashInitNewStr    (u_int64_t str_len, str_ctx_t* str_ctx                       );
hash_err_t TakeHashData      (hash_ctx_t* hash_ctx, char* file_name                 );
hash_err_t HashTest          (hash_ctx_t* hash_ctx, char* file_name                 );
hash_err_t GetFileName       (int argc, char** argv, char** file_name               );
hash_err_t HashDumpForData   (hash_ctx_t* hash_ctx, const char* file_name           );
hash_err_t HashDump          (hash_ctx_t* hash_ctx, const char* file_name           );
hash_err_t HashInsert        (hash_ctx_t* hash_ctx, char* str, u_int64_t str_len          );
hash_err_t ReadSrc           (const char* file_name, int file_size, char* src_buffer);
u_int64_t  CountHashFunction (char* str, u_int64_t str_len                          );
bool       HashFindElement   (hash_ctx_t* hash_ctx, char* str, u_int64_t str_len, u_int64_t hash);
void       ParseHashData     (hash_ctx_t* hash_ctx , char* buffer, int file_name    );
void       HashDestroy       (hash_ctx_t* hash_ctx                                  );
int        CountNumbers      (int val                                               );
int        CopyCurStr        (char* src, char* dst, int* pos, int file_size         );

//--------------------------------------------------------------------------------

#define SPEED_TEST(function, file)     \
FILE* file_ds = fopen (file, "a")     ;\
_mm_lfence();\
u_int64_t _start = __rdtsc ()         ;\
_mm_lfence();\
function                              ;\
    _mm_lfence();\
u_int64_t _time  = __rdtsc () - _start;\
_mm_lfence();\
fprintf (file_ds, "%lld\n", _time)    ;\
fclose (file_ds)                      ;

//--------------------------------------------------------------------------------