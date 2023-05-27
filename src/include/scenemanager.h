#pragma once
#include "raylib.h"
enum GameScreen { UNKNOWN = -1, START = 0, TITLE, TEST };
extern enum GameScreen current_scene;

void scene_new(enum GameScreen scene);
void world_draw(void);
void screen_draw(void);
void resource_start(void);
