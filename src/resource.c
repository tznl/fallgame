#include "include/define.h"

struct world_res default_res;
void assign_default()
{
	default_res.sky_background =	LoadTexture("sky.png"),
	default_res.outer_world_tex =	LoadTexture("dirt_outer.png"),
	default_res.tunnel_background = LoadTexture("dirt_background.png"),
	default_res.obstacle_death =	LoadTexture("obstacle_death.png"),
	default_res.tunnel_inner_death =LoadTexture("tunnel_inner_death.png"),
	default_res.obstacletex =	LoadTexture("obstacle.png"),
	default_res.character =		LoadTexture("bury_fall.png"),
	default_res.tex =		LoadTexture("dirt_flat.png"),
	default_res.title =		LoadTexture("title.png"),
	default_res.restart_text =	LoadTexture("restart.png"),

	default_res.falling_sound =	LoadSound("falling.wav"),
	default_res.death_sound =	LoadSound("death.wav"),

	default_res.font =	LoadFontEx(
		"font/temp/NotoSans-Regular.ttf",
		50,
		0,
		0);

	SetTextureFilter(default_res.font.texture, TEXTURE_FILTER_BILINEAR);
}
