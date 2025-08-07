#include "allegan.h"
#include "cdfilesys.h"
#include <stdio.h>

int cdSystemFlags = 0;
int cdStae = 0; 


int CdInit(void)
{
	//We hijack this function to open the CD ISO file.
	int initSuccessFlag;
	cdIsoFile = al_fopen(al_path_cstr(resPath, ALLEGRO_NATIVE_PATH_SEP), "rb");
	//The function returns 1 on success  or 0 on failure.
	if (cdIsoFile == NULL) {
		printf("Failed to open CD ISO file.\n");
		initSuccessFlag = 0;
		cdState = 0;
	}
	else {
		initSuccessFlag = 1;
	}
	cdState = 1; 
	return initSuccessFlag;

}


void ProcessCdReadStateMachine(void)
{
	al_fclose(cdIsoFile);
	cdState = 0; //Set the state to idle.
	return;

}