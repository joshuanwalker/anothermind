#include <stdbool.h>
#include <stdio.h>
#include "allegan.h"
#include "defines.h"
#include "dummypsyq.h"


int cdTransferReady = 0;
int cdState = 0; 
int cdReadStartSector = 0;
int cdReadByteCount = 0;
char* cdReadTargetAddr = 0;


const int fileGroupOffsetTable[] = {
    -1,     // [0] unused?
    2,      // [1]
    68,     // [2]
    129,    // [3]
    169,    // [4]
    222,    // [5]
    461,    // [6]
    804,    // [7]
    2023,   // [8]
    2834,   // [9]
    3121,   // [10]
    3122    // [11]
};

typedef struct {
    int startSector;
    int fileLength;
} CdSectorInfo;

unsigned char cdPosDatTable[0x6190]; 

void getCdFileSectorInfo(int* outSectorInfo, int logicalOffset, int resourceType);
void loadRawSectorData(int startSector, int length, char* destination);
void loadCdPosTablefromCd(void);
int loadByFileIdGroupId(int fileIndex, int resourceType, char* destBuffer, int maxSize);
bool WaitForCdIdle(int nonBlocking);
int isDebugAllowed(void);
void SetCdBusyStatus(int newCdBusyStatus);
void resetCdTransferReadyFlag(void);




void getCdFileSectorInfo(CdSectorInfo* out, int logicalOffset, int resourceType)
{
    int globalIndex = fileGroupOffsetTable[resourceType + 1] + logicalOffset;
    int offset = globalIndex * 8;

    uint32_t startSector =
        (uint32_t)cdPosDatTable[offset + 0] |
        ((uint32_t)cdPosDatTable[offset + 1] << 8) |
        ((uint32_t)cdPosDatTable[offset + 2] << 16) |
        ((uint32_t)cdPosDatTable[offset + 3] << 24);

    uint32_t fileLength =
        (uint32_t)cdPosDatTable[offset + 4] |
        ((uint32_t)cdPosDatTable[offset + 5] << 8) |
        ((uint32_t)cdPosDatTable[offset + 6] << 16) |
        ((uint32_t)cdPosDatTable[offset + 7] << 24);

    out->startSector = (int)(startSector - 1);  // matching original PSX logic
    out->fileLength = (int)fileLength;
}


void loadRawSectorData(int startSector, int length, char* destination)
{
    
        if (cdIsoFile == NULL || destination == NULL || startSector < 0 || length <= 0) {
            return; // Handle invalid arguments
        }

        // Calculate byte offset in ISO file
        int byteOffset = startSector * SECTOR_SIZE;


        if (!al_fseek(cdIsoFile, byteOffset, ALLEGRO_SEEK_SET)) {
            printf("Seek failed: %s\n", al_ferrmsg(cdIsoFile));
            return;
        }

        // Read sector data into destination buffer
        int bytesRead = (int)al_fread(cdIsoFile, destination, length);
        if (bytesRead != length) {
            printf("Error reading sector data: expected %d bytes, got %d bytes\n", length, bytesRead);
            printf("al_ferror: %s\n", al_ferrmsg(cdIsoFile));
        }

        cdReadStartSector = startSector;
        cdReadByteCount = length;
        cdReadTargetAddr = destination;
        cdState = 1;

}




void loadCdPosTablefromCd(void)

{
	CdInit();
	loadRawSectorData(0x17, 0x6190, (char*)&cdPosDatTable);
    WaitForCdIdle(0);
	return;
}



int loadByFileIdGroupId(int fileIndex, int resourceType, char* destBuffer, int maxSize)
{
    int totalFilesInGroup = getFileCountInGroup(resourceType);
    CdSectorInfo info;

    unsigned char* fileNumStr[32];
    unsigned char* resourceTypeStr[32];

    totalFilesInGroup = getFileCountInGroup(resourceType);


    if (fileIndex >= totalFilesInGroup) {
        fileIndex = totalFilesInGroup - 1; // Clamp to last valid file
    }
    getCdFileSectorInfo(&info, fileIndex, resourceType);
    if ((maxSize == 0) || (info.fileLength <= maxSize)) {
        SetCdBusyStatus(1);
        loadRawSectorData(info.startSector, info.fileLength, destBuffer);
        WaitForCdIdle(0);
    }
    //else {
    //    intToAscii(fileIndex, fileNumStr, 10);
    //    intToAscii(resourceType, resourceTypeStr, 10);
    //    reportIssue("File Size Over \n", "FileNum = ", fileNumStr, "\nUser ID = ", resourceTypeStr);
    //    sectorSize = 0;
    //}
    //return sectorSize;
}



bool WaitForCdIdle(int nonBlocking)

{
    bool cdBusy;

    if (nonBlocking == 0) {
        cdBusy = false;
        if (cdState != 0) {
            do {
                ProcessCdReadStateMachine();
                cdBusy = false;
            } while (cdState != 0);
        }
    }
    else {
        cdBusy = cdState != 0;
    }
    return cdBusy;
}



int isDebugAllowed(void)

{
	return -1; // -1 = Retail Mode (not allowed an locked down) 
}



int getFileCountInGroup(int fileGroupIndex)

{
    return fileGroupOffsetTable[fileGroupIndex + 2] -
        fileGroupOffsetTable[fileGroupIndex + 1];
}



///////////////////////////////
// I AM HERE
///////////////////////////////
void SetCdBusyStatus(int newCdBusyStatus)
{
    //We hijack this function to open the CD ISO file.
    cdIsoFile = al_fopen(al_path_cstr(resPath, ALLEGRO_NATIVE_PATH_SEP), "rb");
    //The function returns 1 on success  or 0 on failure.
    if (cdIsoFile == NULL) {
        printf("Failed to open CD ISO file.\n");
    }
    else {
        cdState = 1;
    }
	printf("SetCdBusyStatus called with status: %d\n", newCdBusyStatus);
    

}


void resetCdTransferReadyFlag(void)

{
	cdTransferReady = 0;
	return;
}




