#include <stdio.h>
#include <stdlib.h>

#include "romPatcher.h"


int main(int argc, char ** argv)
{
    struct ProgramState * programState;
    if(!(programState = programInit(argc, argv)))
    {
        printHelp();
        return 1;
    }

    // Clean up
    free(programState);
    programState = NULL;
    return 0;
}
