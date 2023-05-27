#include "raylib.h"
#include "include/scenemanager.h"
#include "include/scene.h"
#include "include/define.h"
#include <stdio.h>

void scene_new(enum GameScreen scene)
{
//	switch (current_scene) {
//		case TITLE: scene_unload_title(); break;
//		case TEST: scene_unload_test(); break;
//		default: break;
//	}
//	switch (scene) {
//		case TITLE: scene_load_title(); break;
//		case TEST: scene_load_test(); break;
//		default: break;
//	}
//	current_scene = scene;
}

void world_draw(void)
{
	BeginMode2D(world.cam);
	ClearBackground(RAYWHITE);

	switch (current_worldstate) {
		case STATIC: world_static(); break;
		case TRANSITION: world_transition(); break;
		case PLAY: world_play();  break;
		default: break;
	}

	EndMode2D();

}
void screen_draw(void)
{
	switch (current_scene) {
		case TITLE: screen_draw_title(); break;
		case NONE: break;
		default: break;
	}
}

void resource_start(void)
{
	world_load();
	screen_load_title();
}
