#include "include/define.h"

struct world_res *current_res;
void unload_current_res(void) {
	UnloadTexture(current_res->sky_background);	
	UnloadTexture(current_res->outer_world_tex);
	UnloadTexture(current_res->tunnel_background);
	UnloadTexture(current_res->obstacle_death);
	UnloadTexture(current_res->tunnel_inner_death);
	UnloadTexture(current_res->obstacletex);
	UnloadTexture(current_res->character);
	UnloadTexture(current_res->tex);
	UnloadTexture(current_res->title);
	UnloadTexture(current_res->restart_text);

	UnloadSound(current_res->falling_sound);
	UnloadSound(current_res->death_sound);

	UnloadFont(current_res->font);
}

struct world_res default_res;
void assign_default()
{
	default_res.sky_background =	LoadTexture("default/sky.png"),
	default_res.outer_world_tex =	LoadTexture("default/dirt_outer.png"),
	default_res.tunnel_background = LoadTexture("default/dirt_background.png"),
	default_res.obstacle_death =	LoadTexture("default/obstacle_death.png"),
	default_res.tunnel_inner_death =LoadTexture("default/tunnel_inner_death.png"),
	default_res.obstacletex =	LoadTexture("default/obstacle.png"),
	default_res.character =		LoadTexture("default/bury_fall.png"),
	default_res.tex =		LoadTexture("default/dirt_flat.png"),
	default_res.title =		LoadTexture("default/title.png"),
	default_res.restart_text =	LoadTexture("default/restart.png"),

	default_res.falling_sound =	LoadSound("default/falling.wav"),
	default_res.death_sound =	LoadSound("default/death.wav"),

	default_res.font =	LoadFontEx(
		"default/NotoSans-Regular.ttf",
		50,
		0,
		0);

	SetTextureFilter(default_res.font.texture, TEXTURE_FILTER_BILINEAR);
}
