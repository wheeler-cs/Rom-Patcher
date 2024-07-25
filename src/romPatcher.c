#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "romPatcher.h"
#include "endian.h"



void printHelp()
{
    printf("\nROM Patcher v%s", PROGRAM_VERSION);
    printf("\nA CLI program for both applying patches to ROMs and generating patches from two input files.");

    printf("\n\nUsage: patcher [options] -i infile -p patch {-o outfile}");

    printf("\n");
}


struct ProgramState * programInit(int argc, char ** argv)
{
    // Validate endianness of host machine
    // NOTE: I am not sure if this is needed or not. I do not know how much C abstracts away from the host machine's
    //       architecture, and this is just a precaution.
    if(!isLittleEndian())
    {
        // For now just prints error and exits; should ask if should continue regardless
        // TODO: Ask if should continue, regardless of architecture
        fprintf(stderr, "System is not little endian. Program execution cannot continue safely.");
        return NULL;
    }

    // Allocate memory needed to keep track of the program's state
    struct ProgramState * pState = (struct ProgramState *) malloc(sizeof(struct ProgramState));
    initProgramState(pState);

    // Handle arguments passed to program
    unsigned int i;
    for(i = 1; i < argc; i++)
    {
        // Handle options that use only a flag
        if(!strcmp(argv[i], "-h"))
        {
            // Help flag immediately assumes all other arguments are meaningless
            pState->helpFlag = 1;
            break;
        }
        // Handle options that require following entries
        if(argc > (i + 1))
        {
            if(!strcmp(argv[i], "-i"))
            {
                pState->romFile = argv[i + 1];
                i++;
            }
            else if(!strcmp(argv[i], "-p"))
            {
                pState->patchFile = argv[i + 1];
                i++;
            }
            else if(!strcmp(argv[i], "-o"))
            {
                pState->outputFile = argv[i + 1];
                i++;
            }
        }
    }

    return pState;
}


void initProgramState(struct ProgramState * pState)
{
    pState->romFile = "";
    pState->patchFile = "";
    pState->outputFile = "out.rom";
    pState->mode = MODE_NOP;
    pState->helpFlag = 0;
}
