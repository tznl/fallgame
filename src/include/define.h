#ifndef DEFINE_H
#define DEFINE_H
#include "raylib.h"

/*
world data. move to a seperate file later
*/

enum worldstate { W_STATIC = 0, W_STARTING, W_PLAY, W_DEATH, W_TRANSITION};

extern enum worldstate current_worldstate;
extern struct world_res default_res;
extern struct world_res *current_res;
extern float speed;
extern Vector2 hitbox_character;

extern Camera2D cam;

/*
universal data
*/

extern int screen_width;
extern int screen_height;
extern int fps_cap;
extern char personal_best[10];

void assign_default();
void unload_current_res(void);

struct world_res
{
	Texture2D sky_background;
	Texture2D outer_world_tex;
	Texture2D tunnel_background;
	Texture2D obstacle_death;
	Texture2D tunnel_inner_death;
	Texture2D obstacletex;
	Texture2D character;
	Texture2D tex;
	Texture2D title;
	Texture2D restart_text;

	Sound falling_sound;
	Sound death_sound;

	Font font;
};
#endif
