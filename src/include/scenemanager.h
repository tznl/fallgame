#pragma once
#include "raylib.h"
typedef enum GameScreen { UNKNOWN = -1, START = 0, TITLE, TEST } GameScreen;

void scene_new(GameScreen scene);
void scene_draw(void);
void scene_start(void);
