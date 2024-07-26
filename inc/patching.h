#ifndef PATCHING_H
#define PATCHING_H

#include <stdint.h>
#include <stdio.h>

// === Reusable Functions ==============================================================================================
unsigned int verifySignature(FILE *, const uint8_t *);


// === IPS Code ========================================================================================================
extern const uint8_t FILE_SIGNATURE_IPS[];


// === UPS Code ========================================================================================================
extern const uint8_t FILE_SIGNATURE_UPS[];
unsigned int patchUPS(FILE *, FILE *, FILE *);

#endif
