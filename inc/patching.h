#ifndef PATCHING_H
#define PATCHING_H

#include <stdint.h>
#include <stdio.h>


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
 * 
 */
unsigned int patchUPS(FILE *, FILE *, FILE *);

/**
 * 
 */
uint64_t readEncodedNumber(FILE *);

#endif
