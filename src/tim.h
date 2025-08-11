#ifndef TIM_H
#define TIM_H

#include <stdint.h>

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



extern TIM_IMAGE  OpenTIM(char* decompressedOutputBuffer);
//extern ALLEGRO_BITMAP ReadTIM(TIM_IMAGE timData);
//extern void LoadTPage(ALLEGRO_BITMAP *tim,int bithdepth, int transparent, int x, int y, int width, int hight);




#endif //TIM_H
