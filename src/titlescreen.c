#include "allegan.h"
#include "progdata.h"


void ShowSquaresoftLogo(void);
void loadSquaresoftLogo(void);


void ShowSquaresoftLogo(void)
{
	loadSquaresoftLogo();
}




void loadSquaresoftLogo(void)

{
	TIM_IMAGE tim;

	loadProgdata(1, 1);
	//OpenTIM((u_long*)&decompressedOutputBuffer);
	//ReadTIM(&tim);
	//LoadTPage(tim.paddr, 2, 0, 0x140, 0, 0x140, 0xf0);
	///return;
}