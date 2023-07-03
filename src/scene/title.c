#include "raylib.h"
#include "../include/scenemanager.h"
#include "../include/scene.h"
#include "../include/define.h"
#include "../include/codepoints.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void screen_load_title()
{
	sprintf(personal_best, "%s", LoadFileText("personal_record"));
}

void screen_draw_title()
{
	float font_scale = screen_height/20;
	extern int tunnel_spacing;
	float text_scale = world.cam.zoom*0.25;
	char pb_cat[24] = "personal best ";
	strcat(pb_cat, personal_best);
        int pb_size = MeasureTextEx(
                current_res->font,
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
                current_res->title,
                (Rectangle){0, 0, current_res->title.width, current_res->title.height},
                (Rectangle){
                        screen_width/2,
                        screen_height/4,
                        (current_res->title.width*text_scale),
                        (current_res->title.height*text_scale)},
                (Vector2){(
			current_res->title.width*text_scale)/2, 
			current_res->title.height*text_scale/2}, 
                0,
                WHITE);

	if (strcmp(personal_best, "0") != 0 &&
	strcmp(personal_best, "(null)") != 0) {
        DrawTextEx(
                current_res->font,
                pb_cat,
                (Vector2){(screen_width/2) - (pb_size/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);
	}
}


void screen_draw_play()
{
	float font_scale = screen_height/20;
        char posarray[64];
        sprintf(posarray, "%d", (int)hitbox_character.y/100);

        char speedarray[64];
        sprintf(speedarray, "%d", (int)speed);

        int pos_size = MeasureTextEx(
                current_res->font,
                posarray,
                font_scale,
                5).x;

        int speed_size = MeasureTextEx(
                current_res->font,
                speedarray,
                font_scale,
                5).x;

        DrawTextEx(
                current_res->font,
                posarray,
                (Vector2){(screen_width/2) - (pos_size/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);

        DrawTextEx(
                current_res->font,
                speedarray,
                (Vector2){(screen_width/12) - (speed_size/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);
}

void screen_draw_death()
{
	float font_scale = screen_height/20;
	extern int tunnel_spacing;
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
                current_res->font,
                pb_cat,
                font_scale,
                5);

        Vector2 speed_size = MeasureTextEx(
                current_res->font,
                speedarray,
                font_scale,
                5);

	Vector2 pos_size = MeasureTextEx(
		current_res->font,
		posarray,
		font_scale,
		5);

        DrawTextEx(
                current_res->font,
                pb_cat,
                (Vector2){(screen_width/2) - (pb_size.x/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);

        DrawTextEx(
                current_res->font, 
                posarray, 
                (Vector2){(screen_width/2) - (pos_size.x/2), (screen_height/50)+pb_size.y},
                font_scale,
                5,
                BLACK);

        DrawTextEx(
                current_res->font,
                speedarray,
                (Vector2){(screen_width/12) - (speed_size.x/2), (screen_height/50)},
                font_scale,
                5,
                BLACK);

        DrawTexturePro(
                current_res->restart_text,
                (Rectangle){0, 0, current_res->restart_text.width, current_res->restart_text.height},
                (Rectangle){
                        screen_width/2,
                        screen_height/2,
                        (current_res->restart_text.width*restart_scale),
                        (current_res->restart_text.height*restart_scale)},
                (Vector2){(
                        current_res->restart_text.width*restart_scale)/2, 
                        current_res->restart_text.height*restart_scale/2}, 
                0,
                WHITE);

        if (IsMouseButtonPressed(0) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x <= 
	-tunnel_spacing + collision_radius) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x  >= 
	tunnel_spacing - collision_radius)) {
                current_scene = S_TITLELOAD;
		current_worldstate = W_TRANSITION;
        }
}

/*
void screen_load_font()
{
        int codepointCount = 0;
        int *codepoints = LoadCodepoints(codepoint_text, &codepointCount);
        int codepointsNoDupsCount = 0;
        int *codepointsNoDups = CodepointRemoveDuplicates(
                        codepoints, 
                        codepointCount, 
                        &codepointsNoDupsCount);

        UnloadCodepoints(codepoints);

        current_res->font = LoadFontEx(
                "resource/font/noto/NotoSerifSC-Regular.otf", 
                20, 
                codepointsNoDups, 
                codepointsNoDupsCount);

        free(codepointsNoDups);

}
*/

