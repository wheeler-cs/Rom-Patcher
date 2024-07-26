#include <stdlib.h>
#include <string.h>

#include "romPatcher.h"
#include "endian.h"
#include "patching.h"


void printHelp()
{
    printf("\nROM Patcher v%s", PROGRAM_VERSION);
    printf("\nA CLI program for both applying patches to ROMs and generating patches from two input files.");

    printf("\n\nUsage: patcher [options] -i infile -p patch {-o outfile}");

    printf("\n");
}


struct ProgramState * programInit(int argc, char ** argv)
{
    // Print header
    printf("ROM Patcher, %s", PROGRAM_VERSION);
    fflush(stdout); // fprintf will output to stderr before printf can print without this

    // Validate endianness of host machine
    // NOTE: I am not sure if this is needed or not. I do not know how much C abstracts away from the host machine's
    //       architecture, and this is just a precaution.
    if(!isLittleEndian())
    {
        // For now just prints error and exits; should ask if should continue regardless
        // TODO: Ask if should continue, regardless of architecture
        fprintf(stderr, "\nSystem is not little endian. Program execution cannot continue safely.");
        return NULL;
    }

    // Allocate memory needed to keep track of the program's state
    struct ProgramState * pState = (struct ProgramState *) malloc(sizeof(struct ProgramState));
    initProgramState(pState);

    // Handle arguments passed to program
    unsigned int i;
    for(i = 1; i < argc; i++)
    {
        // Handle arguments that use `-`
        if((strlen(argv[i]) == 2) && (argv[i][0] == '-'))
        {
            switch(argv[i][1]) {
                case 'h':       // Help Information
                    pState->helpFlag = 1;
                    break;
                case 'i':       // In File (needs parameter)
                    if(argc > (i + 1))
                    {
                        pState->romFile = argv[i + 1];
                        i++;
                    }
                    else
                    {
                        fprintf(stderr, "\nFlag '-i' is missing argument.");
                    }
                    break;
                case 'p':       // Patch File (needs parameter)
                    if(argc > (i + 1))
                    {
                        pState->patchFile = argv[i + 1];
                        i++;
                    }
                    else
                    {
                        fprintf(stderr, "\nFlag '-p' is missing argument.");
                    }
                    break;
                case 'o':       // Out File (needs parameter)
                    if(argc > (i + 1))
                    {
                        pState->outputFile = argv[i + 1];
                        i++;
                    }
                    else
                    {
                        fprintf(stderr, "\nFlag '-o' is missing argument.");
                    }
                    break;
                default:        // Unknown/unhandled argument
                    fprintf(stderr, "\nUnknown argument -%c", argv[i][1]);
            }
        }
        else {
            fprintf(stderr, "Unknown argument %s", argv[i]);
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


void runPatcher(struct ProgramState * pState)
{
    // No mode specified, just quit
    if(pState->mode == MODE_NOP)
        return;
    
    // Setup file streams
    FILE * romFileStream,
         * patchFileStream,
         * outputFileStream;
    romFileStream = fopen(pState->romFile, "rb"); // ROM is always read-only
    // TODO: Add error-handling for files streams not opened properly
    if(pState->mode == MODE_APPLY_PATCH)
    {
        // Reading from patch to modifed ROM
        patchFileStream = fopen(pState->patchFile, "rb");
        outputFileStream = fopen(pState->outputFile, "wb");
        applyPatch(romFileStream, patchFileStream, outputFileStream, pState->patchType);
    }
    else // Implied if(pState->mode == MODE_GENERATE_PATCH)
    {
        // Reading from modified ROM to patch
        patchFileStream = fopen(pState->patchFile, "wb");
        outputFileStream = fopen(pState->outputFile, "rb");
        generatePatch(romFileStream, outputFileStream, patchFileStream, pState->patchType);
    }

    // Close file streams to prevent memory leak
    fclose(romFileStream);
    fclose(patchFileStream);
    fclose(outputFileStream);
}


void applyPatch(FILE * referenceROM, FILE * patchData, FILE * outputROM, enum PatchType patchFormat)
{
    switch(patchFormat)
    {
        case PATCH_IPS:
            break;
        case PATCH_UPS:
            patchUPS(referenceROM, patchData, outputROM);
            break;
        default:
            break;
    }
}


void generatePatch(FILE * referenceROM, FILE * modifiedROM, FILE * outputPatch, enum PatchType patchFormat)
{

}
