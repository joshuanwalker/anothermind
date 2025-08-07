#ifndef PROGDATA_H
#define PROGDATA_H


extern void decompressLZSS(int compressedDataPtr, unsigned char* outputBuffer);
extern void checkAndUnpackAmpack(unsigned char* buffer);
extern int readLittleEndian32(unsigned char* data);
extern void loadProgdata(int fileIndex, int resourceType);

#endif //PROGDATA_H
