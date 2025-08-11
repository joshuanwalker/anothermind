#include <stdint.h>
#include <stdbool.h>
#include "allegan.h"
#include "cdfilesys.h"
#include "titlescreen.h"


int debugLockState=1;


void resetToReleaseMode(void);
int getDebugLockState(void);
void lockoutDebug(int state);
int intToAscii(int value, char* buffer, int base);
void reportIssue(const char* msg0, const char* msg1, const char* msg2, const char* msg3, const char* msg4);


void resetToReleaseMode(void)

{
    int debugCheck;

    lockoutDebug(false);
    loadCdPosTablefromCd();
    debugCheck = isDebugDisabled();
     if (debugCheck == true) {
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



int intToAscii(int value, char* buffer, int base)
{
    if (base < 2 || base > 36) { *buffer = '\0'; return 0; }

    char* p = buffer;

    // Record sign, but build digits from an unsigned magnitude
    unsigned int mag;
    if (value < 0) {
        *p++ = '-';
        // Convert safely: handle INT_MIN without overflow
        mag = (unsigned int)(-(value + 1)) + 1U;
    }
    else {
        mag = (unsigned int)value;
    }

    // Collect digits (at least one for zero)
    uint8_t tmp[64];          // big enough for 32-bit in base 2
    int n = 0;
    do {
        tmp[n++] = (uint8_t)(mag % (unsigned)base);
        mag /= (unsigned)base;
    } while (mag);

    // NUL-terminate where digits will end
    p[n] = '\0';

    // Emit in reverse
    for (int i = n - 1; i >= 0; --i) {
        uint8_t d = tmp[i];
        *p++ = (char)(d + (d < 10 ? '0' : '7'));  // 10→'A'
    }

    return n; // digits only, no sign, no NUL (matches original convention)
}


void reportIssue(const char* msg0, const char* msg1, const char* msg2, const char* msg3, const char* msg4)
{
    const float x = 0;
    float y = 0;
    const float lh = (float)al_get_font_line_height(debugFont);

    al_clear_to_color(al_map_rgb(0, 0, 0));

    if (msg0) { al_draw_text(debugFont, al_map_rgb(255, 255, 255), x, y, 0, msg0); y += lh; }
    if (msg1) { al_draw_text(debugFont, al_map_rgb(255, 255, 255), x, y, 0, msg1); y += lh; }
    if (msg2) { al_draw_text(debugFont, al_map_rgb(255, 255, 255), x, y, 0, msg2); y += lh; }
    if (msg3) { al_draw_text(debugFont, al_map_rgb(255, 255, 255), x, y, 0, msg3); y += lh; }
    if (msg4) { al_draw_text(debugFont, al_map_rgb(255, 255, 255), x, y, 0, msg4); y += lh; }

    y += lh * 0.5f;
    al_draw_text(debugFont, al_map_rgb(180, 180, 180), x, y, 0,
        "[Press any key / gamepad button to continue]");

    al_flip_display();
    while (1);
}