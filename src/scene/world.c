#include "raylib.h"
#include "../include/define.h"
#include "../include/scene.h"
#include <stdio.h>
#include <math.h>

struct character
{
	int x;
	int y;
	int move;
};
struct character charmain;

int offset              = 0;
int tunnel_spacing      = 150;
int tunnel_height       = 0;
int speed               = 10; 
int real_tunnel_height;

float character_scale	= 0.19;
float tunnel_scale      = 0.25;
float unit_max;
float unit_min;

bool started            = false;
bool starting           = true;

void world_load()
{
        world.tex = LoadTexture("resource/dirt_flat.png");
        world.cam = (Camera2D){0};
        world.cam.target = (Vector2){ 0, 0 };
        world.cam.offset = (Vector2){ screen_width/2.0f, screen_height/2.0f };
        world.cam.rotation = 0.0f;
        world.cam.zoom = 1.0f;

	world.character = LoadTexture("resource/bury_fall.png");

	charmain.y = (int)floor(GetScreenToWorld2D(
		(Vector2){screen_width/2, screen_height/4}, 
		world.cam).y);
	charmain.x = 0;
	charmain.move = 10;
	real_tunnel_height = world.tex.height*tunnel_scale;
	
}

void world_static()
{
        if (IsKeyPressed(KEY_SPACE)) {
                current_worldstate = TRANSITION;
        }
	recursive_draw();
	draw_character_fall(0, 0);
}

void world_transition()
{
	world.cam.target = (Vector2){ 0.0f, screen_height/4 };
	starting = false;
	printf("starting tripped\n");
	recursive_draw();
	draw_character_fall(0, 0);
	current_worldstate = PLAY;
}

void world_play()
{
	if (IsKeyDown(KEY_LEFT)) {
		charmain.x-=charmain.move;
	}else if (IsKeyDown(KEY_RIGHT)) {
		charmain.x+=charmain.move;
	}
	charmain.y = (int)floor(GetScreenToWorld2D((Vector2){
		screen_width, screen_height/4}, world.cam).y);
	draw_character_fall(charmain.x, charmain.y);
	recursive_draw();
	world.cam.target = (Vector2){ 0, speed+world.cam.target.y };
//	printf("charmain.y: %d\ntarget: %f\n", charmain.y, world.cam.target.y);
}

void recursive_draw() 
{
        unit_max =      (float)(GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam).y);
        unit_min =      (float)(GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam).y);

        for (float      i = tunnel_height + floor(unit_min/real_tunnel_height);
                        i <= unit_max;
                        i += real_tunnel_height) {

                draw_tunnel_unit(i);
        }
}

void draw_character_fall(int x, int y)
{
	DrawTexturePro(
		world.character,
		(Rectangle){0, 0, world.character.width, -world.character.height},
		(Rectangle){
			charmain.x,
			charmain.y,
			world.character.width*character_scale,
			world.character.height*character_scale},
		(Vector2)	{(world.character.width*character_scale)/2, 
				world.character.height*character_scale},
		0,
		WHITE);
}

void draw_tunnel_unit(float offset)
{
	//tunnel 1 (left)
        DrawTexturePro(
                world.tex,
                (Rectangle){0, 0, world.tex.width, world.tex.height},
                (Rectangle){
                        -tunnel_spacing,
                        tunnel_height + offset,
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)},
                (Vector2){world.tex.width*tunnel_scale, 0}, 
                0,
                WHITE);
        //tunnel 2 (right)
        DrawTexturePro(
                world.tex,
                (Rectangle){0, 0, -world.tex.width, world.tex.height},
                (Rectangle){
                        tunnel_spacing,
                        tunnel_height + offset,
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)},
                (Vector2){0, 0}, 
                0,
                WHITE);
}
