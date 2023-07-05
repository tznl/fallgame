#include "raylib.h"
#include "include/define.h"
#include "include/scenemanager.h"
#include <stdio.h>
/*needed to create a directory*/
#include <sys/stat.h>
#include <sys/types.h>

void reload(int *code);

int main(void)
{
#ifndef PLATFORM_ANDROID
	ChangeDirectory("./assets");
#endif
	screen_height = 0;
	screen_width = 0;

	InitWindow(screen_width, screen_height, "fallgame");
	InitAudioDevice();
	SetTargetFPS(fps_cap);

	int res_code = 1;
	if (!FileExists("save")) {
		mkdir("save", 0777);
		SaveFileText("save/personal_record", "0");
	}

	while(!WindowShouldClose()) {
		BeginDrawing();

		reload(&res_code);
		world_draw();
		screen_draw();

		EndDrawing();
	}

	unload_current_res();
	CloseAudioDevice();
        CloseWindow();

	return 0;
}

void reload(int *code) {
	if (IsWindowResized() ) {
		*code = 2;
	}   

	switch (*code) {
		case 0:
			break;
		case 1:
			sprintf(personal_best, "%s", LoadFileText("save/personal_record"));
			assign_default();
			current_res = &default_res;
                        screen_height = GetRenderHeight();
                        screen_width = GetRenderWidth();
                        resource_start();
                        *code = 0;
			break;
		case 2:
                        screen_height = GetRenderHeight();
                        screen_width = GetRenderWidth();
                        SetWindowSize(screen_width, screen_height);
                        resource_start();
			*code = 0;
			break;
	}
}
