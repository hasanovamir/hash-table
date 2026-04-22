#include "general_io.h"

//--------------------------------------------------------------------------------

long long int GetFileSize (const char* file_name)
{
    DEBUG_ASSERT (file_name != nullptr);

    struct stat statistic = {};
    stat (file_name, &statistic);

    long long int file_size = statistic.st_size;
    
    if (file_size == 0)
    {
        fprintf(stderr, "ERR_get_file_size in %s:%d func:%s\n",
            __FILE__, __LINE__, __PRETTY_FUNCTION__);
        return -1;
    }

    return file_size;
}

//--------------------------------------------------------------------------------