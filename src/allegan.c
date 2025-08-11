#include "allegan.h"
#include <stdio.h>






ALLEGRO_TRANSFORM scaleTrasform;


ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_PATH* romPath = NULL;
ALLEGRO_PATH* fontPath = NULL;
ALLEGRO_FILE* cdIsoFile = NULL;

ALLEGRO_FONT* debugFont = NULL;

ALLEGRO_BITMAP* testBitmap = NULL;





void initAllegro(void);
void initPaths(void);




void initAllegro(void)
{
	int gameWidth = 1280, gameHeight = 960;

	if (!al_init()) {
		printf("Could not init Allegro.\n");
		exit(1);
	}
	if (!al_install_keyboard()) {
		printf("Error installing keyboard.\n");
		exit(1);
	}
	if (!al_init_image_addon()) {
		printf("Could not init Allegro Image Loader.\n");
		exit(1);
	}
	if (!al_init_font_addon()) {
		printf("Could not init Allegro Font Addon.\n");
		exit(1);
	}
	if (!al_init_ttf_addon()) {
		printf("Could not init Allegro TTF Addon.\n");
		exit(1);
	}



	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP | ALLEGRO_MIN_LINEAR);

	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(gameWidth, gameHeight);
	if (!display)
	{
		printf("Failed to create display!\n");
		exit(1);
	}
	
	//This scales the display up
	al_identity_transform(&scaleTrasform);
	al_scale_transform(&scaleTrasform, 1280.0 / 320.0, 960.0 / 240.0);
	al_use_transform(&scaleTrasform);

	al_set_target_backbuffer(display);

	initPaths();

		//check if iso image exists
	cdIsoFile = al_fopen(al_path_cstr(romPath, ALLEGRO_NATIVE_PATH_SEP), "rb");
	if (cdIsoFile == NULL) {
		printf("Failed to open CD ISO file.\n");
		exit(1);
	}
	al_fclose(cdIsoFile);

	//load debug font
	debugFont = al_load_font(al_path_cstr(fontPath, ALLEGRO_NATIVE_PATH_SEP), 10, 0);
	if (!debugFont) {
		printf("Failed to load debug font.\n");
		exit(1);
	} 


}

void initPaths(void)
{
	romPath = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(romPath, "rom");
	al_set_path_filename(romPath, "another.iso");

	fontPath = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(fontPath, "font");
	al_set_path_filename(fontPath, "SpaceMono-Regular.ttf");
}



