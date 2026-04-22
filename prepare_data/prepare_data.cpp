#include "general_io.h"

//————————————————————————————————————————————————————————————————————————————————

int  CountNumbers   (int          val);
int  mystrlen       (char*        src);
void BuffersDestroy (char*        src ,     char*  dst       );
int  InitBuffers    (char**       src ,     char** dst        , int   size       );
int  ProcessSrc     (char* dst_buffer ,     char*  src_buffer , int   file_size  );
int  ReadSrc        (const char* file_name, int    file_size  , char* src_buffer );
int  OutputDstFile  (const char* file_name, const char* buffer, int   buffer_size);
int  GetFilesNames  (int argc, const char** argv, const char** src_file_name, const char** dst_file_name);

//————————————————————————————————————————————————————————————————————————————————

int main (int argc, char** argv)
{
    const char* src_file_name = nullptr;
    const char* dst_file_name = nullptr;
          char* src_buffer    = nullptr;
          char* dst_buffer    = nullptr;

    if (GetFilesNames (argc, (const char**) argv, &src_file_name, &dst_file_name)) return 1;

    int file_size = GetFileSize (src_file_name);

    if (InitBuffers (&src_buffer, &dst_buffer, file_size )) return 1;
    if (ReadSrc     (src_file_name  , file_size  , src_buffer)) return 1;

    int dst_len = ProcessSrc (dst_buffer, src_buffer, file_size);

    if (OutputDstFile (dst_file_name, dst_buffer, dst_len)) return 1;

    BuffersDestroy (src_buffer, dst_buffer);

    return 0;
    
}

//————————————————————————————————————————————————————————————————————————————————

int GetFilesNames (int argc, const char** argv, const char** src_file_name, const char** dst_file_name)
{
    if (argc < 3) {
        fprintf (stderr, "NO files to prepare fuckin shit\n");
        return 1;
    }

    *src_file_name = argv[1];
    *dst_file_name = argv[2];

    return 0;
}

//————————————————————————————————————————————————————————————————————————————————

int InitBuffers (char** src, char** dst, int size)
{
    *src = (char*) calloc (size    , sizeof (char));
    *dst = (char*) calloc (size * 2, sizeof (char));

    if (src == nullptr || dst == nullptr) {
        fprintf (stderr, "Alloc err\n");
        return 1;
    }

    return 0;
}

//————————————————————————————————————————————————————————————————————————————————

int ReadSrc (const char* file_name, int file_size, char* src_buffer)
{
    FILE* file = fopen (file_name, "r");
    if (file == nullptr) {
        fprintf (stderr, "Open file err");
        return 1;
    }

    if (fread (src_buffer, sizeof (char), file_size, file) != file_size) {
        fprintf (stderr, "Invalid file size\n");
        return 1;
    }

    fclose (file);

    return 0;
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

int ProcessSrc (char* dst_buffer, char* src_buffer, int file_size)
{
    int pos_1 = 0;
    int pos_2 = 0;

    while (pos_1 < file_size) {
        if (isalpha (src_buffer[pos_1])) {
            int len = mystrlen (src_buffer + pos_1);
            sprintf (dst_buffer + pos_2, "%d", len); 
            pos_2 += CountNumbers (len);

            strncpy (dst_buffer + pos_2, src_buffer + pos_1, len);
            pos_1 += len;
            pos_2 += len;
        }
        else {
            pos_1++;
        }
    }

    return pos_2;
}

//————————————————————————————————————————————————————————————————————————————————

int OutputDstFile (const char* file_name, const char* buffer, int buffer_size)
{
    FILE* file = fopen (file_name, "w");
    if (file == nullptr) {
        fprintf (stderr, "Open file err");
        return 1;
    }

    fwrite (buffer, sizeof (char), buffer_size, file);

    fclose (file);

    return 0;
}

//————————————————————————————————————————————————————————————————————————————————

void BuffersDestroy (char* src, char* dst)
{
    free (src);
    free (dst);
}

//————————————————————————————————————————————————————————————————————————————————

int mystrlen (char* src)
{
    if (src == nullptr) return 0;

    int n = 0;

    while (isalpha (src[n])) n++;

    return n;
}

//————————————————————————————————————————————————————————————————————————————————