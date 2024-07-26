#include <stdlib.h>
#include <string.h>

#include "patching.h"

const uint8_t FILE_SIGNATURE_IPS[6] = {0x50, 0x41, 0x54, 0x43, 0x48, 0x0A}; // ASCII "PATCH"
const uint8_t FILE_SIGNATURE_UPS[4] = {0x55, 0x50, 0x53, 0x31};             // ASCII "UPS1"


unsigned int verifySignature(FILE * patchData, const uint8_t * signature)
{
    // Move file pointer to beginning of file
    fseek(patchData, 0, SEEK_SET);

    // Create a temporary buffer and read from file
    uint8_t * signatureBuffer = malloc(sizeof(signature));
    fread(signatureBuffer, sizeof(signature), sizeof(uint8_t), patchData);

    // Compare file to signature
    unsigned int compareLength = sizeof(signatureBuffer);
    unsigned int result = memcmp(signatureBuffer, signature, compareLength);

    // Clean up and return
    fseek(patchData, 0, SEEK_SET);
    free(signatureBuffer);
    signatureBuffer = NULL;
    return !(result); // Negate the result because want 0 to indicate failure, but strcmp indicates 0 as success
}


unsigned int patchUPS(FILE * referenceROM, FILE * patchData, FILE * outputROM)
{
    // Check that the UPS signature is present
    if(!(verifySignature(patchData, FILE_SIGNATURE_UPS)))
        return 0;


    return 1;
}



