#include <stdlib.h>
#include <string.h>

#include "patching.h"


const uint8_t FILE_SIGNATURE_IPS[SIGNATURE_LENGTH_IPS] = {0x50, 0x41, 0x54, 0x43, 0x48, 0x0A}; // ASCII "PATCH"
const uint8_t FILE_SIGNATURE_UPS[SIGNATURE_LENGTH_UPS] = {0x55, 0x50, 0x53, 0x31};             // ASCII "UPS1"


unsigned int verifySignature(FILE * patchData, const uint8_t * signature, unsigned int signatureLength)
{
    // Move file pointer to beginning of file
    fseek(patchData, 0, SEEK_SET);

    // Create a temporary buffer and read from file
    uint8_t * signatureBuffer = malloc(signatureLength);
    fread(signatureBuffer, signatureLength, 1, patchData);

    // Compare file to signature
    unsigned int result = memcmp(signatureBuffer, signature, signatureLength);

    // Clean up and return
    fseek(patchData, 0, SEEK_SET);
    free(signatureBuffer);
    signatureBuffer = NULL; // Dangling pointer
    return !(result); // Negate the result because want 0 to indicate failure, but strcmp indicates 0 as success
}


unsigned int validateUPS(FILE * patchData)
{
    // Check that the UPS signature is present
    if(!(verifySignature(patchData, FILE_SIGNATURE_UPS, SIGNATURE_LENGTH_UPS)))
        return 0;

    uint64_t referenceROMSize,
             outputROMSize;
    
    fseek(patchData, SIGNATURE_LENGTH_UPS, SEEK_SET); // Position file pointer to number
    referenceROMSize = readEncodedNumber(patchData);
    outputROMSize = readEncodedNumber(patchData);
}


unsigned int patchUPS(FILE * referenceROM, FILE * patchData, FILE * outputROM)
{
    if(!(validateUPS(patchData)))
        return 0;

    return 1;
}


uint64_t readEncodedNumber(FILE * patchData)
{
    // Code adapted from http://justsolve.archiveteam.org/wiki/UPS_(binary_patch_format)

    uint64_t value = 0,
             shift = 0;
    uint8_t octet = 0;

    // Read encoded integer from file
    do
    {
        octet = fgetc(patchData);
        if(octet & 0x80) // End of chunk has been reached
        {
            value += (octet & 0x7f) << shift;
            break;
        }
        value += (octet | 0x80) << shift;
        shift += 7;
    } while(1);

    return value;
}
