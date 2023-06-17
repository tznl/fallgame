#include "raylib.h"
#include "include/define.h"
#include "include/scenemanager.h"
#include <stdio.h>

bool init_loaded = false;

int main()
{
#ifndef PLATFORM_ANDROID
	ChangeDirectory("./assets");
#endif


	screen_height = GetMonitorHeight(GetCurrentMonitor());
	screen_width = GetMonitorWidth(GetCurrentMonitor()); 
	InitWindow(screen_width, screen_height, "fallgame");
	SetTargetFPS(fps_cap);
	

	while(!WindowShouldClose()) {
		if (IsWindowResized()) {
                        screen_height = GetRenderHeight();
                        screen_width = GetRenderWidth();
                        SetWindowSize(screen_width, screen_height);
                        resource_start();		
		}
		BeginDrawing();
	        if (IsKeyPressed(KEY_J)) {
	                screen_height = 1000;
			screen_width = 540;
			SetWindowSize(screen_width, screen_height);
			resource_start();
	        }

		if (!init_loaded) {
                        screen_height = GetRenderHeight();
                        screen_width = GetRenderWidth();
                        SetWindowSize(screen_width, screen_height);
			resource_start();
			printf("First scene loaded\n");
			init_loaded = true;
		}
		world_draw();
		screen_draw();

		EndDrawing();
	}

        CloseWindow();

	return 0;
}
