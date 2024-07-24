#include "endian.h"

unsigned int isLittleEndian()
{
    // This only checks if the system is little endian, it does not determine if system is big or mixed endian
    int testVar = 1;
    return(* (char *) &testVar == 1);
}
