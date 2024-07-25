#ifndef ENDIAN_H
#define ENDIAN_H

/**
 * Determines if the host system uses a little endian architecture.
 * 
 * @returns The evaluation of if the host is little endian.
 * @retval 0 Host uses a non-little endian architecture, which could imply either big endian or mixed endian.
 * @retval 1 Host uses little endian as its architecture.
 */
unsigned int isLittleEndian();

#endif
