#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>





ALLEGRO_TRANSFORM scaleTrasform;


ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_PATH* resPath = NULL;
ALLEGRO_FILE* cdIsoFile = NULL;

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

	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP | ALLEGRO_MIN_LINEAR);

	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(gameWidth, gameHeight);
	if (!display)
	{
		printf("Failed to create display!\n");
		exit(1);
	}
	al_get_backbuffer(display);

	//This scales the display up
	al_identity_transform(&scaleTrasform);
	al_scale_transform(&scaleTrasform, 1280.0 / 320.0, 960.0 / 240.0);
	al_use_transform(&scaleTrasform);

	initPaths();

}

void initPaths(void)
{
	resPath = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(resPath, "rom");
	al_set_path_filename(resPath, "another.iso");
}



