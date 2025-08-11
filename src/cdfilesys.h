#ifndef CDFILESYS_H
#define CDFILESYS_H



extern int cdTransferReady;
extern int cdState;
extern int cdReadStartSector;
extern int cdReadByteCount;
extern char* cdReadTargetAddr;

extern unsigned char cdPosDatTable[];



extern void loadRawSectorData(int startSector, int length, char* destination);
extern  void loadCdPosTablefromCd(void);
extern int loadByFileIdGroupId(int fileIndex, int resourceType, char* destBuffer, int maxSize);
extern int isDebugDisabled(void);

#endif //CDFILESYS_H
