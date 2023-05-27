#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "raylib.h"
enum GameScreen { UNKNOWN = -1, TITLE = 0, NONE};
extern enum GameScreen current_scene;

void scene_new(enum GameScreen scene);
void world_draw(void);
void screen_draw(void);
void resource_start(void);
#endif
