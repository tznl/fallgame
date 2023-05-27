#include "raylib.h"
#include "../include/scenemanager.h"
#include "../include/scene.h"
#include "../include/define.h"
#include "../include/codepoints.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct resource title;

char *titlename = "fallgame";

void screen_load_title()
{
	int codepointCount = 0;
	int *codepoints = LoadCodepoints(titlename, &codepointCount);
	int codepointsNoDupsCount = 0;
	int *codepointsNoDups = CodepointRemoveDuplicates(
	                codepoints, 
	                codepointCount, 
	                &codepointsNoDupsCount);

	UnloadCodepoints(codepoints);
	title.tex  = LoadTexture("resource/title.png");	
	title.noto = LoadFontEx(
                "resource/font/noto/NotoSerifSC-Regular.otf", 
                20, 
                codepointsNoDups, 
                codepointsNoDupsCount);

	SetTextureFilter(title.noto.texture, TEXTURE_FILTER_BILINEAR);
	free(codepointsNoDups);
}

void screen_draw_title()
{
        if (IsKeyPressed(KEY_SPACE)) {
                current_scene = NONE;
        }

	float font_scale = 0.25;

        DrawTexturePro(
                title.tex,
                (Rectangle){0, 0, title.tex.width, title.tex.height},
                (Rectangle){
                        screen_width/2,
                        screen_height/4,
                        (title.tex.width*font_scale),
                        (title.tex.height*font_scale)},
                (Vector2){(
			title.tex.width*font_scale)/2, 
			title.tex.height*font_scale/2}, 
                0,
                WHITE);

/*	DrawTextEx(
		title.noto, 
		titlename, 
		(Vector2){(screen_width/2), (screen_height/4)},
		48, 
		5, 
		BLACK);*/
}
