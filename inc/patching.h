#ifndef PATCHING_H
#define PATCHING_H

#include <stdint.h>
#include <stdio.h>


// === Constants =======================================================================================================
// Defines are used here because `sizeof` wasn't getting the size of the arrays properly
/**
 * @def SIGNATURE_LENGTH_IPS
 * The length of the FILE_SIGNATURE_IPS array.
 * @see patching.c
 */
#define SIGNATURE_LENGTH_IPS 6

/**
 * @def SIGNATURE_LENGTH_UPS
 * The length of the FILE_SIGNATURE_UPS array.
 * @see patching.c
 */
#define SIGNATURE_LENGTH_UPS 4


// === Data Structures =================================================================================================
/**
 * @todo
 */
struct PatchMetadata
{
    // File size information
    unsigned int sourceSize,
                 destinationSize;

    // CRC32 checksums of related files
    uint32_t sourceChecksum,
             destinationChecksum,
             patchChecksum;

    unsigned int validatedSignature;
};


// === Reusable Functions ==============================================================================================
/**
 * 
 */
unsigned int verifySignature(FILE *, const uint8_t *, unsigned int);


// === IPS Code ========================================================================================================
/**
 * Global constant reference value for the file signature present at the beginning of a IPS patch file.
 * @see patching.c
 */
extern const uint8_t FILE_SIGNATURE_IPS[];


// === UPS Code ========================================================================================================
/**
 * Constant value to serve as reference for the file signature of a UPS patch file.
 * @see patching.c
 */
extern const uint8_t FILE_SIGNATURE_UPS[];

/**
 * @todo
 */
unsigned int validateUPS(FILE *);

/**
 * @todo
 */
unsigned int patchUPS(FILE *, FILE *, FILE *);

/**
 * Reads in a variable-width integer from the given file stream and converts it to fixed-width.
 * 
 * @pre The provided file pointer must be opened in "rb" mode.
 * @pre The provided file pointer must be positioned to the start of the number beforehand.
 * 
 * @param[in] patchData An active file pointer associated with a file containing encoded numbers.
 * 
 * @returns The variable-width value read from the file stream as a fixed-width unsigned integer.
 * 
 * @note The file pointer is moved during this operation and is not reset to the position it was at at the beginning of
 *       the function call.
 */
uint64_t readEncodedNumber(FILE *);

#endif
