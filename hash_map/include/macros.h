#ifndef MACROS_H
#define MACROS_H

//————————————————————————————————————————————————————————————————————————————————

#include "colors.h"

//————————————————————————————————————————————————————————————————————————————————

const int kListStartCapacity = 11;
const int kMaxStringSize     = 256;
const int kMaxCommandSize    = 128;
const int kMaxFileNameSize   = 32;
const int kAllocCapacity     = 512;
const int kCommonStackSize   = 128;
const int kCommonStringSize  = 128;
const int kStartBigArrayCap  = 8;

//————————————————————————————————————————————————————————————————————————————————

#define RET_NULL_IF_NULL(src)         if (src   == nullptr) return nullptr
#define RET_NULL_IF_NEQ(src_1, src_2) if (src_1 != src_2  ) return nullptr

//————————————————————————————————————————————————————————————————————————————————

#ifndef N_DEBUG
#define DEBUG_ASSERT(cond)\
if (!(cond))\
{\
    fprintf(stderr, "%s in %s:%d func:%s\n", #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    exit(1);\
}
#else
#define DEBUG_ASSERT(cond) ;
#endif //N_DEBUG

//————————————————————————————————————————————————————————————————————————————————

#define PRINTERR(str)\
fprintf (stderr, COLOR_RED "%s" COLOR_RESET " in %s:%d in %s\n", #str, __FILE__, __LINE__, __PRETTY_FUNCTION__);

//————————————————————————————————————————————————————————————————————————————————

#endif //MACROS_H