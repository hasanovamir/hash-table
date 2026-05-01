#ifndef LIST_H
#define LIST_H

//————————————————————————————————————————————————————————————————————————————————

#define POISON (list_data_t) {nullptr, (u_int64_t) -1488, (u_int64_t) 0x67676767}

//————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"

//————————————————————————————————————————————————————————————————————————————————

struct str_ctx_t
{
    char*     str;
    u_int64_t str_len;
    u_int64_t hash;
};

typedef str_ctx_t list_data_t;

//————————————————————————————————————————————————————————————————————————————————

enum class list_err_t
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

//————————————————————————————————————————————————————————————————————————————————

struct list_t
{
    list_data_t* data;
    int* next;
    int* prev;
    int  head;
    int  tail;
    int  free;
    int  size;
    int  capacity;
    int  num_calls;
};

//————————————————————————————————————————————————————————————————————————————————

void       MemSetList        (list_t* list);
list_err_t ListDestroy       (list_t* list);
list_err_t ChangeFree        (list_t* list);
list_err_t IncreaseList      (list_t* list);
list_err_t ListCheck         (list_t* list);
list_err_t ListAdd           (list_t* list, list_data_t val);
list_err_t ListInit          (list_t** list);
list_err_t ListDeleteElement (list_t* list, int idx);
list_err_t ListInsertAfter   (list_t* list, int idx, list_data_t val);
list_err_t ListInsertBefore  (list_t* list, int idx, list_data_t val);

//————————————————————————————————————————————————————————————————————————————————

#ifndef N_DEBUG
#define LIST_VERIFY(list)\
do {\
    list_err_t status = ListCheck (list);\
    if (status != list_err_t::success) {\
        return   (status);\
    }\
} while (0);
#else
#define LIST_VERIFY(list) ;
#endif //LIST_VERIFY

//————————————————————————————————————————————————————————————————————————————————

#endif //LIST_H