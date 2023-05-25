#pragma once
#include "raylib.h"
enum GameScreen { UNKNOWN = -1, START = 0, TITLE, TEST };
extern enum GameScreen current_scene;

void scene_new(enum GameScreen scene);
void scene_draw(void);
void scene_start(void);
