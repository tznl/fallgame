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
void scene_draw(void)
{
	scene_draw_world();
	switch (current_scene) {
		case TITLE: scene_draw_title(); break;
//		case TEST: scene_draw_test(); break;
		default: break;
	}
}

void scene_start(void)
{
	scene_load_world();
	scene_load_title();
}
