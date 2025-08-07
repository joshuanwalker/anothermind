#include <stdbool.h>
#include "cdfilesys.h"
#include "titlescreen.h"


int debugLockState=1;


void resetToReleaseMode(void);
int getDebugLockState(void);
void lockoutDebug(int state);


void resetToReleaseMode(void)

{
    int debugCheck;

    lockoutDebug(false);
    resetCdTransferReadyFlag();
    loadCdPosTablefromCd();
    debugCheck = isDebugAllowed();
     if (debugCheck == -1) {
      ShowSquaresoftLogo();
      lockoutDebug(true);
     }
    //resetMovieDecoderState();
    //resetVibrationSystem();
    return;
}



int getDebugLockState(void)

{
    return debugLockState;
}


void lockoutDebug(int state)

{
    debugLockState = state;
    return;
}
