#include "cdfilesys.h"





char* rawProgdataFileBuffer[0x30000];
char* decompressedOutputBuffer[0x80000];



void decompressLZSS(int compressedDataPtr, unsigned char* outputBuffer);
void checkAndUnpackAmpack(unsigned char* buffer);
int readLittleEndian32(unsigned char* data);
void loadProgdata(int fileIndex, int resourceType);



void decompressLZSS(int compressedDataPtr, unsigned char* outputBuffer) 
{
}


void checkAndUnpackAmpack(unsigned char* buffer)
{
}


int readLittleEndian32(unsigned char* data)
{
}


void loadProgdata(int fileIndex, int resourceType)
{

    char* dataString;

    loadByFileIdGroupId(fileIndex, resourceType, &rawProgdataFileBuffer, 0x30000);
    while (1);
//    if (rawFileFirstByte == 0xc3) {
//        if (decompressionFlag == -1) {
//            decompressLZSS(&rawProgdataFileBuffer, &decompressedOutputBuffer);
//            return;
//        }
//        dataString = DATA_EQUALS;
//    }
//    else {
//        dataString = (char*)0x0;
//    }
//    reportIssue("Unpack Err:  no Ampack data", dataString, 0, 0, 0);
//
//    return;
}
