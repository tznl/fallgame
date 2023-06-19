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
extern int tunnel_spacing;
Texture2D restart_text;
float font_scale;

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
                "font/temp/NotoSans-Regular.ttf",
                50,
                NULL,
                0);
	SetTextureFilter(title.noto.texture, TEXTURE_FILTER_BILINEAR);
}

void screen_load_title()
{
	screen_load_font();
	sprintf(personal_best, "%s", LoadFileText("personal_record"));

	font_scale = screen_height/20;
	restart_text = LoadTexture("restart.png");
	title.tex  = LoadTexture("title.png");	
	SetTextureFilter(title.noto.texture, TEXTURE_FILTER_BILINEAR);
}

void screen_draw_title()
{
	extern int tunnel_spacing;
	float text_scale = world.cam.zoom*0.25;
	char pb_cat[24] = "personal best ";
	strcat(pb_cat, personal_best);
        int pb_size = MeasureTextEx(
                title.noto,
                pb_cat,
                font_scale,
                5).x;

        if (IsMouseButtonPressed(0) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x <= -tunnel_spacing) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x  >= tunnel_spacing)) {
		current_scene = S_PLAY;
		current_worldstate = W_TRANSITION;
        }

        DrawTexturePro(
                title.tex,
                (Rectangle){0, 0, title.tex.width, title.tex.height},
                (Rectangle){
                        screen_width/2,
                        screen_height/4,
                        (title.tex.width*text_scale),
                        (title.tex.height*text_scale)},
                (Vector2){(
			title.tex.width*text_scale)/2, 
			title.tex.height*text_scale/2}, 
                0,
                WHITE);

	if (strcmp(personal_best, "0") != 0 &&
	strcmp(personal_best, "(null)") != 0) {
        DrawTextEx(
                title.noto,
                pb_cat,
                (Vector2){(screen_width/2) - (pb_size/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);
	}
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
                font_scale,
                5).x;

        int speed_size = MeasureTextEx(
                title.noto,
                speedarray,
                font_scale,
                5).x;

        DrawTextEx(
                title.noto,
                posarray,
                (Vector2){(screen_width/2) - (pos_size/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);

        DrawTextEx(
                title.noto,
                speedarray,
                (Vector2){(screen_width/12) - (speed_size/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);
}

void screen_draw_death()
{
        char pb_cat[24] = "personal best ";
        strcat(pb_cat, personal_best);

        char posarray[64] = "current attempt ";
	char posbuffer[10];
        sprintf(posbuffer, "%d", (int)hitbox_character.y/100);
	strcat(posarray, posbuffer);

        char speedarray[64];
        sprintf(speedarray, "%d", (int)speed);

	float restart_scale = world.cam.zoom*0.35;

	extern float collision_radius;

        Vector2 pb_size = MeasureTextEx(
                title.noto,
                pb_cat,
                font_scale,
                5);

        Vector2 speed_size = MeasureTextEx(
                title.noto,
                speedarray,
                font_scale,
                5);

	Vector2 pos_size = MeasureTextEx(
		title.noto,
		posarray,
		font_scale,
		5);

        DrawTextEx(
                title.noto,
                pb_cat,
                (Vector2){(screen_width/2) - (pb_size.x/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);

        DrawTextEx(
                title.noto, 
                posarray, 
                (Vector2){(screen_width/2) - (pos_size.x/2), (screen_height/50)+pb_size.y},
                font_scale,
                5,
                BLACK);

        DrawTextEx(
                title.noto,
                speedarray,
                (Vector2){(screen_width/12) - (speed_size.x/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);

        DrawTexturePro(
                restart_text,
                (Rectangle){0, 0, restart_text.width, restart_text.height},
                (Rectangle){
                        screen_width/2,
                        screen_height/2,
                        (restart_text.width*restart_scale),
                        (restart_text.height*restart_scale)},
                (Vector2){(
                        restart_text.width*restart_scale)/2, 
                        restart_text.height*restart_scale/2}, 
                0,
                WHITE);

        if (IsMouseButtonPressed(0) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x <= 
	-tunnel_spacing + collision_radius) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x  >= 
	tunnel_spacing - collision_radius)) {
                screen_load_font();
                current_scene = S_TITLELOAD;
		current_worldstate = W_TRANSITION;
        }
}
