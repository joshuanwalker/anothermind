#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "cdfilesys.h"
#include "allegan.h"
#include "debug.h"


#define LZSS_WINDOW_SIZE 4096




uint8_t rawProgdataFileBuffer[0x30000];
uint8_t decompressedOutputBuffer[0x80000];
int usingCompressedFiles = true; // -1 system is using compressed data




void decompressLZSS(uint8_t* compressedDataPtr, uint8_t* outputBuffer);
void checkAndUnpackAmpack(uint8_t* buffer);
uint32_t readLittleEndian32(const uint8_t* data);
void loadProgdata(int fileIndex, int resourceType);





void decompressLZSS(uint8_t* compressedDataPtr, uint8_t* outputBuffer)
{
    // Header: [0..1]=magic (C3 FF), [2..5]=total size of this compressed blob (including header)
    uint32_t total_size = readLittleEndian32(compressedDataPtr + 2);
    if (total_size < 7) return; // needs at least one flag byte

    uint8_t* cur = compressedDataPtr + 7;                 // after first flag byte
    uint8_t* end = compressedDataPtr + total_size;        // exclusive
    uint8_t  flags = compressedDataPtr[6];

    uint8_t  lzssWindow[0x1000];
    memset(lzssWindow, 0, sizeof(lzssWindow));
    uint16_t dictIndex = 0x0FEE;                          // start index

    for (;;) {
        // Process 8 bits from the current flags byte (LSB first)
        uint16_t fb = (uint16_t)(0xFF00u | flags);
        for (int i = 0; i < 8; ++i) {
            if (fb & 1) {
                // Literal
                if (cur >= end) return;                   // truncated / done
                uint8_t lit = *cur++;
                *outputBuffer++ = lit;
                lzssWindow[dictIndex] = lit;
                dictIndex = (dictIndex + 1) & 0x0FFF;
            }
            else {
                // Match (2 bytes)
                if (cur + 1 >= end) return;               // truncated / done
                uint8_t lo = cur[0];
                uint8_t hi = cur[1];
                cur += 2;

                uint16_t offset = (uint16_t)(lo | ((uint16_t)(hi & 0xF0) << 4)); // 12-bit
                int length = (hi & 0x0F) + 3;

                for (int k = 0; k < length; ++k) {
                    uint8_t b = lzssWindow[(offset + k) & 0x0FFF];
                    *outputBuffer++ = b;
                    lzssWindow[dictIndex] = b;
                    dictIndex = (dictIndex + 1) & 0x0FFF;
                }
            }
            fb >>= 1;
            if ((fb & 0x100u) == 0) break;               // consumed 8 bits
        }

        // Next flags byte
        if (cur >= end) return;                           // no more flags → done
        flags = *cur++;
    }
 
}




void checkAndUnpackAmpack(uint8_t* buffer)
{
}


uint32_t readLittleEndian32(const uint8_t* data) {
    return ((uint32_t)data[0]) |
        ((uint32_t)data[1] << 8) |
        ((uint32_t)data[2] << 16) |
        ((uint32_t)data[3] << 24);
}



void loadProgdata(int fileIndex, int resourceType)
{
    ALLEGRO_USTR* dataString = al_ustr_new("test");
   
    loadByFileIdGroupId(fileIndex, resourceType, rawProgdataFileBuffer, 0x30000);
    if (rawProgdataFileBuffer[0] == 0xc3) {
        if (usingCompressedFiles == true) {
            decompressLZSS(rawProgdataFileBuffer, decompressedOutputBuffer);
            return;
        }
        dataString = al_ustr_new("data=");
        //Dummied but I bet this was the filename and filesize
    }
    else {
        dataString = al_ustr_new("");
    }
    reportIssue("Unpack Err:  no Ampack data", al_cstr(dataString), 0, 0, 0);
    al_ustr_free(dataString);
    return;
}
