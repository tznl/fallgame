#include "raylib.h"
#include "../include/scene.h"
#include "../include/define.h"
#include "../include/codepoints.h"
#include <stdlib.h>
#include <string.h>

struct resource title;

char *titlename = "fallgame";

void scene_load_title()
{
	int codepointCount = 0;
	int *codepoints = LoadCodepoints(titlename, &codepointCount);
	int codepointsNoDupsCount = 0;
	int *codepointsNoDups = CodepointRemoveDuplicates(
	                codepoints, 
	                codepointCount, 
	                &codepointsNoDupsCount);

	UnloadCodepoints(codepoints);
	
	title.tex = LoadTexture("resource/dirt.png");

	title.cam = (Camera2D){0};
	title.cam.target = (Vector2){ 0.0f, 0.0f };
	title.cam.offset = (Vector2){ screen_width/2.0f, screen_height/2.0f };
	title.cam.rotation = 0.0f;
	title.cam.zoom = 1.0f;

	title.noto = LoadFontEx(
                "resource/font/noto/NotoSerifSC-Regular.otf", 
                20, 
                codepointsNoDups, 
                codepointsNoDupsCount);

	SetTextureFilter(title.noto.texture, TEXTURE_FILTER_BILINEAR);
	free(codepointsNoDups);
}

void scene_draw_title()
{
	int tunnel_spacing = 100;
	int tunnel_height = 0;
	float tunnel_scale = 4;

	ClearBackground(RAYWHITE);
 
	BeginMode2D(title.cam);
	//tunnel 1 (left)
	DrawTexturePro(
		title.tex, 
		(Rectangle){0, 0, title.tex.width, title.tex.height}, 
		(Rectangle){
			-tunnel_spacing, 
			tunnel_height, 
			(title.tex.width/tunnel_scale), 
			(title.tex.height/tunnel_scale)},
		(Vector2){title.tex.width/tunnel_scale, 0},
		0, 
		WHITE);
	//tunnel 2 (right)
        DrawTexturePro(
                title.tex, 
                (Rectangle){0, 0, -title.tex.width, title.tex.height}, 
                (Rectangle){
                        tunnel_spacing, 
                        tunnel_height, 
                        (title.tex.width/tunnel_scale), 
                        (title.tex.height/tunnel_scale)},
                (Vector2){0, 0}, 
                0,  
                WHITE);
	EndMode2D();

	DrawTextEx(
		title.noto, 
		titlename, 
		(Vector2){(screen_width/2) - 20, (screen_height/2) - 20},
		48, 
		5, 
		BLACK);
	DrawFPS(10, 10);
}
