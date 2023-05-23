#include "raylib.h"
#include "include/scenemanager.h"
#include "include/scene.h"

extern GameScreen current_scene;

void scene_new(GameScreen scene)
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
	switch (current_scene) {
		case TITLE: scene_draw_title(); break;
//		case TEST: scene_draw_test(); break;
		default: break;
	}
}

void scene_start(void)
{
	switch (current_scene) {
		case TITLE: scene_load_title(); break;
//              case TEST: scene_load_test(); break;
		default: break;
        }
}
