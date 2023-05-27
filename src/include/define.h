#ifndef DEFINE_H
#define DEFINE_H
#include "raylib.h"

//world data. move to a seperate file later
enum worldstate { STATIC = 0, PLAY, TRANSITION};

extern struct resource world;
extern enum worldstate current_worldstate;

//universal data
extern int screen_width;
extern int screen_height;
extern int fps_cap;

struct resource
{
	Texture2D character;
        Camera2D cam;
        Font noto;
	Texture2D tex;
	Image image;
};
#endif
