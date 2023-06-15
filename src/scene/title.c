#include "raylib.h"
#include "../include/scenemanager.h"
#include "../include/scene.h"
#include "../include/define.h"
#include "../include/codepoints.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct resource title;

void screen_load_font()
{
/*        int codepointCount = 0;
        int *codepoints = LoadCodepoints(codepoint_text, &codepointCount);
        int codepointsNoDupsCount = 0;
        int *codepointsNoDups = CodepointRemoveDuplicates(
                        codepoints, 
                        codepointCount, 
                        &codepointsNoDupsCount);

        UnloadCodepoints(codepoints);

        title.noto = LoadFontEx(
                "resource/font/noto/NotoSerifSC-Regular.otf", 
                20, 
                codepointsNoDups, 
                codepointsNoDupsCount);

	free(codepointsNoDups);
*/
        title.noto = LoadFontEx(
                "resource/font/noto/NotoSerifSC-Regular.otf",
                50,
                NULL,
                0);
	SetTextureFilter(title.noto.texture, TEXTURE_FILTER_BILINEAR);
	current_scene = S_PLAY;
}

void screen_load_title()
{
	title.tex  = LoadTexture("resource/title.png");	
	SetTextureFilter(title.noto.texture, TEXTURE_FILTER_BILINEAR);
}

void screen_draw_title()
{
	extern int tunnel_spacing;
        if (IsMouseButtonPressed(0) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x <= -tunnel_spacing) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x  >= tunnel_spacing)) {
                screen_load_font();
		current_scene = S_TITLELOAD;
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
}


void screen_draw_play()
{
        char posarray[64];
        sprintf(posarray, "%d", (int)hitbox_character.y/100);

        char speedarray[64];
        sprintf(speedarray, "%d", (int)speed);

        int pos_size = MeasureTextEx(
                title.noto,
                posarray,
                48,
                5).x;

        DrawTextEx(
                title.noto,
                posarray,
                (Vector2){(screen_width/2) - (pos_size/2), (screen_height/50)},
                48,
                5,
                BLACK);

        int speed_size = MeasureTextEx(
                title.noto,
                speedarray,
                48,
                5).x;

        DrawTextEx(
                title.noto,
                speedarray,
                (Vector2){(screen_width/12) - (speed_size/2), (screen_height/50)},
                48,
                5,
                BLACK);
}

void screen_draw_death()
{
        char posarray[64];
        sprintf(posarray, "%d", (int)hitbox_character.y/100);

	int pos_size = MeasureTextEx(
		title.noto,
		posarray,
		48,
		5).x;

        DrawTextEx(
                title.noto, 
                posarray, 
                (Vector2){(screen_width/2) - (pos_size/2), (screen_height/50)},
                48,
                5,
                BLACK);

	char* restart_array = "tap again to restart";

        int restart_size = MeasureTextEx(
                title.noto,
                restart_array,
                48,
                5).x;

        DrawTextEx(
                title.noto,
                restart_array,
                (Vector2){(screen_width/2) - (restart_size/2), (screen_height/2)},
                48,
                5,
                BLACK);

        if (IsMouseButtonPressed(0)) {
                screen_load_font();
                current_scene = S_TITLELOAD;
        }
}
