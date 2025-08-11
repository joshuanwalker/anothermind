#ifndef DEBUG_H
#define DEBUG_H


extern int debugLockState;

extern void resetToReleaseMode(void);
extern int intToAscii(int value, char* buffer, int base);
void reportIssue(const char* msg0, const char* msg1, const char* msg2, const char* msg3, const char* msg4);

#endif //DEBUG_H
