#ifndef ROM_PATCHER_H
#define ROM_PATCHER_H

#include <stdio.h>

// === Constants =======================================================================================================
/**
 * @def PROGRAM_VERSION
 * The current version of the program represented as a C-string.
 */
#define PROGRAM_VERSION "0.0.1"

/** Enumeration identifying current program state. */
enum ProgramMode {
    /** Initial program state (does nothing). */
    MODE_NOP,
    /** Apply a patch to a file. */
    MODE_APPLY_PATCH,
    /** Generate patch from two input files. */
    MODE_GENERATE_PATCH,
};

/** Enumeration describing the patching format currently in use. */
enum PatchType {
    /** Internal Patching System */
    PATCH_IPS,
    /** Universal Patching System */
    PATCH_UPS,
};


// === Data Structures =================================================================================================
/**
 * @struct ProgramState romPatcher.h "inc/romPatcher.h"
 * @brief Maintains the internal state of the program.
 */
struct ProgramState {
    // Files
    /** 
     * In both patch and generate mode, this is the base ROM file from which either a patch or
     * a patched file will result.
     */
    char * romFile,
         /**
          * In patch mode, this parameter stores the patch file to be applied to the ROM.
          * In generate mode, this is the resulting patch from the comparison operation.
          */
         * patchFile,
         /**
          * In patch mode, this is the resulting patched rom.
          * In generate mode, this is the ROM that has had modifications applied to it.
          */
         * outputFile;

    // Program flags
    /**
     * unsigned int helpFlag
     * Triggers the help menu to be displayed to the user.
     * Functionally acts as a boolean.
     * @see printHelp
     */
    unsigned int helpFlag;

    /**
     * unsigned int mode
     * The current operation mode of the program.
     * @see ProgramMode
     */
    enum ProgramMode mode;

    /** 
     * unsigned int patchType
     * The format of the patch file being handled.
     * @see PatchType
     */
    enum PatchType patchType;
};


// === Function Prototypes =============================================================================================
/**
 * Displays help documentation to the user.
 * 
 * Typically called by passing the argument "-h" to the program, but may also be invoked if there is an issue with
 * program initialization.
 */
void printHelp();


/**
 * Initializes the program by creating an internal state from the arguments passed in from the command line.
 * 
 * @param[in] argc The number of arguments passed into the program. Is typically the `argc` from `main`.
 * @param[in] argv The vector of arguments used to initialize the program state. Is typically the `argv` from `main`.
 * 
 * @returns A program state initialized using the arguments passed in via the command line.
 * @retval NULL An issue has occurred when attempting to initialize the program state.
 * 
 * @post If initialization is successful, memory will be allocated for the program state and the pointer returned.
 */ 
struct ProgramState * programInit(int, char **);


/**
 * Initializes a ProgramState structure by setting its parameters to some default value.
 * 
 * Default values for newly-defined structs may be undefined, depending on the compiler. This ensures the provided
 * ProgramState is in a reliable state after the call in an effort to prevent errors.
 * 
 * @param[in, out] pState The ProgramState class to be initialized by the function call.
 * 
 */
void initProgramState(struct ProgramState *);


/**
 * @todo
 */
void runPatcher(struct ProgramState *);


/**
 * @todo
 */
void applyPatch(FILE *, FILE *, FILE *, enum PatchType);

/**
 * @todo
 */
void generatePatch(FILE *, FILE *, FILE *, enum PatchType);


#endif
