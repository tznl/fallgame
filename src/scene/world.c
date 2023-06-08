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

Vector2 hitbox_character;
Rectangle hitbox_tunnel_left;
Rectangle hitbox_tunnel_right;

float character_scale	= 0.15;
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

	world.obstacletex = LoadTexture("resource/obstacle.png");

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
        if (IsMouseButtonPressed(0)) {
                current_worldstate = W_TRANSITION;
        }
	recursive_draw();

        DrawTexturePro(
                world.character,
                (Rectangle){0, 0, world.character.width, world.character.height},
                (Rectangle){
                        0,
                        0,
                        world.character.width*character_scale,
                        world.character.height*character_scale},
                (Vector2)       {(world.character.width*character_scale)/2,
                                world.character.height*character_scale},
                0,
                WHITE);
}

void world_transition()
{
	world.cam.target = (Vector2){ 0.0f, screen_height/4 };
	starting = false;
	printf("starting tripped\n");
	recursive_draw();
	draw_character_fall(0, 0);
	current_worldstate = W_PLAY;
}

void world_play()
{
	charmain.x = GetScreenToWorld2D(GetMousePosition(), world.cam).x;
	charmain.y = (int)floor(GetScreenToWorld2D((Vector2){
		screen_width, screen_height/4}, world.cam).y);

	draw_character_fall(charmain.x, charmain.y);
	recursive_draw();

        hitbox_character = (Vector2) {charmain.x, charmain.y};
        hitbox_tunnel_left = (Rectangle){
                        -tunnel_spacing-(world.tex.width*tunnel_scale),
                        floor(unit_min),
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)};

        hitbox_tunnel_right = (Rectangle){
                        tunnel_spacing,
                        floor(unit_min),
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)};

	if (	CheckCollisionPointRec(hitbox_character, hitbox_tunnel_left) ||
		CheckCollisionPointRec(hitbox_character, hitbox_tunnel_right)) {
		current_worldstate = W_DEATH;
	}
	world.cam.target = (Vector2){ 0, speed+world.cam.target.y };

}

void world_death() 
{
	draw_character_fall(charmain.x, charmain.y);
        recursive_draw();
}
void recursive_draw() 
{
        unit_max =      (float)(GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam).y);
        unit_min =      (float)(GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam).y);

        for (float      i  = floor(unit_min/real_tunnel_height);
                        i <= unit_max;
                        i += real_tunnel_height) {

                draw_tunnel_unit(i);
        }
//temp obstacle code

        for (float      i  = floor(unit_min/real_tunnel_height);
                        i <= unit_max;
                        i += real_tunnel_height) {

                draw_obstacle_unit(i);
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

void draw_obstacle_unit(float offset)
{
        DrawTexturePro(
                world.obstacletex,
                (Rectangle){0, 0, world.obstacletex.width, world.obstacletex.height},
                (Rectangle){
                        0,
                        0 + offset,
                        (world.obstacletex.width*0.01),
                        (world.obstacletex.height*0.01)},
                (Vector2){world.obstacletex.width*0.01, 0}, 
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
