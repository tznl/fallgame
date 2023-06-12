#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "raylib.h"
enum GameScreen { S_UNKNOWN = -1, S_TITLE = 0, S_DEATH, S_NONE, S_PLAY, S_TITLELOAD};
extern enum GameScreen current_scene;

void scene_new(enum GameScreen scene);
void world_draw(void);
void screen_draw(void);
void resource_start(void);
#endif
