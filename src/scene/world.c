#include "raylib.h"
#include "../include/define.h"
#include "../include/scene.h"
#include "../include/scenemanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
int real_tunnel_height;
int seed		= 0; 
int starting_height	= 10*100; //real world position is shown divided by 100 in game

Vector2 hitbox_character;
Rectangle hitbox_tunnel_left;
Rectangle hitbox_tunnel_right;

float speed;
float acceleration;
float terminal_velocity;
float character_scale	= 0.15;
float tunnel_scale      = 0.25;
float obstacle_scale	= 0.05;
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

	speed = 10;
	acceleration = 0.01;
	terminal_velocity = 25;

	charmain.move = 10;
	real_tunnel_height = world.tex.height*tunnel_scale;	
	
	srand(time(NULL));
	seed = rand();
	puts("world loaded");

}

void world_static()
{
        if (IsMouseButtonPressed(0)) {
                current_worldstate = W_TRANSITION;
        }

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

		recursive_draw();
}

void world_transition()
{
	world.cam.target = (Vector2){ 0.0f, screen_height/4 };
	starting = false;
	printf("starting tripped\n");
	current_worldstate = W_PLAY;
}

void world_play()
{
	charmain.x = GetScreenToWorld2D(GetMousePosition(), world.cam).x;
	charmain.y = (int)floor(GetScreenToWorld2D((Vector2){
		screen_width, screen_height/4}, world.cam).y);
	hitbox_character = (Vector2) {charmain.x, charmain.y};
	draw_character_fall(charmain.x, charmain.y);

	recursive_draw();

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
		current_scene = S_DEATH;
	}
	world.cam.target = (Vector2){ 0, speed+world.cam.target.y };

	if (hitbox_character.y > starting_height && speed <= terminal_velocity) {
		speed+=acceleration;
	}
}

void world_starting()
{
        charmain.x = GetScreenToWorld2D(GetMousePosition(), world.cam).x;
        charmain.y = (int)floor(GetScreenToWorld2D((Vector2){
                screen_width, screen_height/4}, world.cam).y);
        hitbox_character = (Vector2) {charmain.x, charmain.y};
        draw_character_fall(charmain.x, charmain.y);

        unit_max =      (float)(GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam).y);
        unit_min =      (float)(GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam).y);

        for (float      i  = floor(unit_min/real_tunnel_height);
                        i <= unit_max;
                        i += real_tunnel_height) {

                draw_tunnel_unit(i);
        }

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

        if (    CheckCollisionPointRec(hitbox_character, hitbox_tunnel_left) ||
                CheckCollisionPointRec(hitbox_character, hitbox_tunnel_right)) {
                current_worldstate = W_DEATH;
        }
        world.cam.target = (Vector2){ 0, speed+world.cam.target.y };

	if (hitbox_character.y >= starting_height) {
		current_worldstate = W_PLAY;
	}

}

void world_death() 
{
	draw_character_fall(charmain.x, charmain.y);
        recursive_draw();
	speed = 10;
        if (IsMouseButtonPressed(0)) {
                current_worldstate = W_TRANSITION;
        }
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

	int tmp = 1;

        for (float      i  = floor(unit_min/real_tunnel_height);
                        i <= unit_max;
                        i += real_tunnel_height) {
		if (i < starting_height) {

		continue;
		}

                Rectangle obstaclepos = (Rectangle){
                        obstacle_randomizer(&tmp),
                        0 + i,
                        (world.obstacletex.width*obstacle_scale),
                        (world.obstacletex.height*obstacle_scale)};

                draw_obstacle_unit(obstaclepos);
	        if (CheckCollisionPointRec(hitbox_character, obstaclepos)) {
	                current_worldstate = W_DEATH;
			current_scene = S_DEATH;
	        }
        }

}

int obstacle_randomizer(int* x)
{
	int value;
	value = (abs(*x+=seed)) %//random
	(int)(tunnel_spacing*2-(world.obstacletex.width*obstacle_scale)); //limit
	value -= tunnel_spacing;
	return value;
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

void draw_obstacle_unit(Rectangle draw_where)
{
        DrawTexturePro(
                world.obstacletex,
                (Rectangle){0, 0, world.obstacletex.width, world.obstacletex.height},
                draw_where,
                (Vector2){0, 0}, 
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
