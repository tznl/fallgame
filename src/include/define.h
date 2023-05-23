#pragma once
#include "raylib.h"

int screen_width  = 854;
int screen_height = 480;
int fps_cap      = 60; 

struct resource
{
        Camera2D cam;
        Font noto;
	Texture2D tex;
	Image image;
};
