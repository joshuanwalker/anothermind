#ifndef PROGDATA_H
#define PROGDATA_H

extern uint8_t decompressedOutputBuffer[0x80000];



extern void decompressLZSS(uint8_t* compressedDataPtr, uint8_t* outputBuffer);
extern void checkAndUnpackAmpack(uint8_t* buffer);
extern uint32_t readLittleEndian32(const uint8_t* data);
extern void loadProgdata(int fileIndex, int resourceType);


#endif //PROGDATA_H
