#ifndef ROM_PATCHER_H
#define ROM_PATCHER_H

// === Constants =======================================================================================================
#define PROGRAM_VERSION "0.0.1"

/** Enumeration identifying current program state. */
enum ProgramMode {
    MODE_NOP,            /** Initial program state (does nothing). */
    MODE_APPLY_PATCH,    /** Apply a patch to a file. */
    MODE_GENERATE_PATCH, /** Generate patch from two input files. */
};


// === Data Structures =================================================================================================
/** Struct for maintaining program's internal state. */
struct ProgramState {
    // Files
    char * romFile,
         * patchFile,
         * outputFile;
    // Program flags
    unsigned int mode,
                 helpFlag;
};
/**
 * @struct ProgramState romPatcher.h "inc/romPatcher.h"
 * @brief Maintains the internal state of the program.
 * 
 * @property "char *" romFile
 * @property "char *" patchFile
 * @property "char *" outputFile
 * 
 * @property "unsigned int" mode
 * @property "unsigned int" helpFlag
 */


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


#endif
