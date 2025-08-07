#include "allegan.h"
#include "game.h"
#include "globals.h"
#include <stdbool.h>


int main() {
	initAllegro();
	doGame();
	do {} while (true);
	return 0;
}	