#include <stdio.h>
#include <stdlib.h>

#include "romPatcher.h"
#include "endian.h"

void programInit()
{
    if(!isLittleEndian())
    {
        // For now just prints error and exits; should ask if should continue regardless
        fprintf(stderr, "System is not little endian. Program execution cannot continue safely.");
        exit(EXIT_FAILURE);
    }
}
