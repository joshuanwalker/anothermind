#include "allegan.h"
#include "progdata.h"
#include "tim.h"


void ShowSquaresoftLogo(void);
void loadSquaresoftLogo(void);


void ShowSquaresoftLogo(void)
{
	loadSquaresoftLogo();
}




void loadSquaresoftLogo(void)

{
	ALLEGRO_BITMAP* tim;

	loadProgdata(1, 1);
	OpenTIM(decompressedOutputBuffer);
	//ReadTIM(&tim);
	//LoadTPage(tim.paddr, 2, 0, 0x140, 0, 0x140, 0xf0);
	///return;
}