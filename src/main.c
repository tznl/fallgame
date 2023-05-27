#include "raylib.h"
#include "include/define.h"
#include "include/scenemanager.h"
#include <stdio.h>

//GameScreen current_scene = TITLE;
bool init_loaded = false;

int main()
{
	printf("test\n");

	InitWindow(screen_width, screen_height, "fallgame");
	SetTargetFPS(fps_cap);
	

	while(!WindowShouldClose()) {
		BeginDrawing();

		if (!init_loaded) {
			resource_start();
			printf("First scene loaded\n");
			init_loaded = true;
		}
		world_draw();
		screen_draw();
		DrawFPS(10, 10);

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
