#include "raylib.h"
#include "include/scenemanager.h"
#include "include/scene.h"

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
	scene_draw_world();
}
void screen_draw(void)
{
	scene_draw_title();
}

void resource_start(void)
{
	scene_load_world();
	scene_load_title();
}
