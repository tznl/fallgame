#include "raylib.h"
#include "include/scenemanager.h"
#include <stdio.h>

GameScreen current_scene = TITLE;
bool init_loaded = false;
extern int screen_width;
extern int screen_height;
extern int fps_cap;

int main()
{
	printf("test\n");

	InitWindow(screen_width, screen_height, "fallgame");
	SetTargetFPS(fps_cap);
	

	while(!WindowShouldClose()) {
		BeginDrawing();

		if (!init_loaded) {
			scene_start();
			printf("First scene loaded\n");
			init_loaded = true;
		}
		scene_draw();

		EndDrawing();
//		if (IsKeyPressed(KEY_Q == true)){
//		}
	}

//        UnloadTexture(tex);
//        UnloadModel(model);
//	UnloadFont(noto);
        CloseWindow();

	return 0;
}
