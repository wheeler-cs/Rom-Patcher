#ifndef ROM_PATCHER_H
#define ROM_PATCHER_H

#include <stdio.h>

// === Constants =======================================================================================================
#define PROGRAM_VERSION "0.0.1"

/** Enumeration identifying current program state. */
enum ProgramMode {
    MODE_NOP,            /** Initial program state (does nothing). */
    MODE_APPLY_PATCH,    /** Apply a patch to a file. */
    MODE_GENERATE_PATCH, /** Generate patch from two input files. */
};

/** Enumeration describing the patching format currently in use. */
enum PatchType {
    PATCH_IPS,  /** Internal Patching System */
    PATCH_UPS,  /** Universal Patching System */
};


// === Data Structures =================================================================================================
/**
 * @struct ProgramState romPatcher.h "inc/romPatcher.h"
 * @brief Maintains the internal state of the program.
 */
struct ProgramState {
    // Files
    char * romFile,         /**
                             * char * romFile 
                             * In both patch and generate mode, this is the base ROM file from which either a patch or
                             * a patched file will result.
                             */
         * patchFile,       /**
                             * char * patchFile
                             * In patch mode, this parameter stores the patch file to be applied to the ROM.
                             * In generate mode, this is the resulting patch from the comparison operation.
                             */
         * outputFile;      /**
                             * char * outputFile
                             * In patch mode, this is the resulting patched rom.
                             * In generate mode, this is the ROM that has had modifications applied to it.
                             */
    // Program flags
    unsigned int helpFlag;      /**
                                 * unsigned int helpFlag
                                 * Triggers the help menu to be displayed to the user.
                                 * Functionally acts as a boolean.
                                 * @see printHelp
                                 */
    enum ProgramMode mode;      /**
                                 * unsigned int mode
                                 * The current operation mode of the program.
                                 * @see ProgramMode
                                 */
    enum PatchType patchType;   /** 
                                 * unsigned int patchType
                                 * The format of the patch file being handled.
                                 * @see PatchType
                                 */
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
 * 
 */
void runPatcher(struct ProgramState *);


/**
 * 
 */
void applyPatch(FILE *, FILE *, FILE *, enum PatchType);

/**
 * 
 */
void generatePatch(FILE *, FILE *, FILE *, enum PatchType);


#endif
