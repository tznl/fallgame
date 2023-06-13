#ifndef DEFINE_H
#define DEFINE_H
#include "raylib.h"

/*
world data. move to a seperate file later
*/

enum worldstate { W_STATIC = 0, W_STARTING, W_PLAY, W_DEATH, W_TRANSITION};

extern struct resource world;
extern enum worldstate current_worldstate;

extern float speed;
extern Vector2 hitbox_character;
extern Rectangle hitbox_tunnel_left;
extern Rectangle hitbox_tunnel_right;

/*
universal data
*/

extern int screen_width;
extern int screen_height;
extern int fps_cap;

struct resource
{
	Texture2D obstacletex;
	Texture2D character;
        Camera2D cam;
        Font noto;
	Texture2D tex;
	Image image;
};
#endif
