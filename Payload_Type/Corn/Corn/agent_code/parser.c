#include <windows.h>

typedef struct
{
    PBYTE original;
    PBYTE buffer;
    SIZE_T length;
    SIZE_T originalLength;
} Parser, *PParser;

getInt32() {

}

PBYTE getBytes(PParser parser, PSIZE_T size)
{
    SIZE_T length = 0;
    if (*size == 0) // get size
    {
        length = getInt32(parser);
        *size = length;
    }
    else 
    {
        
    }
}