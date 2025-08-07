#include <stdbool.h>
#include "globals.h"
#include "debug.h"



void runGameLoop(void);





void runGameLoop(void)

{
    int inputStatus;

	// Initialize the stack pointer to a specific address on PSX. Not used in this port
    //initialStackPointer = SetSp(0x80200000);
    //SetSp();
    vibrationDeviceType = 0;
    //initGpuAndCdromEvents();
    //resetMovieIRQSystem();
    globalGameFlags = globalGameFlags & 0xfb;
    //do {
        resetToReleaseMode();
        //resetFullGameRuntimeState();
        //resetFullGameRuntimeState();
        //runtimeStateFlag = 1;
    //    while (inputStatus = pollAndProcessControllerInput(), inputStatus == 1) {
    //        FUN_8010cb14();
    //    }
    //    SetDispMask(0);
    //    ResetGraph(1);
    //    DrawSync(0);
    //    do {
    //        VSync(0);
    //        DrawSync(0);
    //        inputStatus = pollAndProcessControllerInput();
    //    } while (inputStatus != 0);
    //    shutdownSoundSystem();
    //    ResetGraph(0);
    //    SetSp(initialStackPointer);
    //} while (true);
}
