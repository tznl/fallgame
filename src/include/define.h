#ifndef DEFINE_H
#define DEFINE_H
#include "raylib.h"

extern int screen_width;
extern int screen_height;
extern int fps_cap;

struct resource
{
        Camera2D cam;
        Font noto;
	Texture2D tex;
	Image image;
};
#endif
