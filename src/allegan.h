#ifndef ALLGAN_H
#define ALLGAN_H

#include <allegro5/allegro.h>



typedef struct {
	uint32_t magic;  // always 0x10
	uint32_t flags;  // image type and CLUT presence

	// Optional CLUT block
	struct {
		uint32_t size;
		uint16_t x, y;
		uint16_t colors_per_palette;
		uint16_t num_palettes;
		uint16_t* clut_data; // pointer to color data (RGB555)
	} clut;

	// Image data block
	struct {
		uint32_t size;
		uint16_t x, y;
		uint16_t width;  // in words (16-bit)
		uint16_t height; // in pixels
		uint8_t* image_data; // raw pixel data
	} image;

} TIM_IMAGE;




extern ALLEGRO_FILE* cdIsoFile;
extern ALLEGRO_PATH* resPath;


extern void initAllegro(void);

#endif //ALLGAN_H

