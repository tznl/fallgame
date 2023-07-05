#include "raylib.h"
#include "include/scenemanager.h"
#include "include/scene.h"
#include "include/define.h"
#include <stdio.h>

void world_draw(void)
{
	BeginMode2D(cam);
	ClearBackground(RAYWHITE);

	switch (current_worldstate) {
		case W_STARTING: world_starting(); break;
		case W_STATIC: world_static(); break;
		case W_TRANSITION: world_transition(); break;
		case W_PLAY: world_play();  break;
		case W_DEATH: world_death(); break;
		default: break;
	}

	EndMode2D();

}
void screen_draw(void)
{
	switch (current_scene) {
		case S_TITLE: screen_draw_title(); break;
		case S_PLAY: screen_draw_play(); break; 
		case S_NONE: break;
		case S_DEATH: screen_draw_death(); break;
		default: break;
	}
}

void resource_start(void)
{
	world_load();
}
