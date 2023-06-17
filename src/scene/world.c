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
int real_tunnel_height;
int real_tunnel_width;
int seed		= 0; 
int starting_height	= 10*100; /*real world position is shown divided by 100 in game*/
int visibility		= 427;

Vector2 hitbox_character;
Rectangle hitbox_tunnel_left;
Rectangle hitbox_tunnel_right;

float collision_radius = 1;
float speed;
float acceleration;
float terminal_velocity;
float character_scale	= 0.15;
float tunnel_scale      = 0.25;
float obstacle_scale	= 0.05;
Vector2 unit_max;
Vector2 unit_min;

Texture2D outer_world_tex;

void world_load()
{
        world.tex = LoadTexture("dirt_flat.png");
        world.cam = (Camera2D){0};
        world.cam.target = (Vector2){ 0, 0 };
        world.cam.offset = (Vector2){ screen_width/2.0f, screen_height/2.0f };
        world.cam.rotation = 0.0f;
        world.cam.zoom = ((float)screen_height / visibility) / 2;
	world.obstacletex = LoadTexture("obstacle.png");
	world.character = LoadTexture("bury_fall.png");
	outer_world_tex = LoadTexture("dirt_outer.png");


	speed = 10;

	acceleration = 0.005;

	terminal_velocity = 25;

	charmain.move = 10;

	real_tunnel_height = world.tex.height*tunnel_scale;	
	real_tunnel_width = world.tex.width*tunnel_scale;

	srand(time(NULL));
	seed = rand();

}

void world_static()
{
        if (IsMouseButtonPressed(0) &&
	!(GetScreenToWorld2D(GetMousePosition(), world.cam).x <= -tunnel_spacing) &&
	!(GetScreenToWorld2D(GetMousePosition(), world.cam).x  >= tunnel_spacing)) {
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
                        floor(unit_min.y),
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)};

        hitbox_tunnel_right = (Rectangle){
                        tunnel_spacing,
                        floor(unit_min.y),
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)};

	if (	CheckCollisionCircleRec(hitbox_character, collision_radius, hitbox_tunnel_left) ||
		CheckCollisionCircleRec(hitbox_character, collision_radius, hitbox_tunnel_right)) {
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
	float i;

        charmain.x = GetScreenToWorld2D(GetMousePosition(), world.cam).x;

        charmain.y = (int)floor(GetScreenToWorld2D((Vector2){
                screen_width, screen_height/4}, world.cam).y);

        hitbox_character = (Vector2) {charmain.x, charmain.y};

	speed = 10;

        unit_max =      GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam);
        unit_min =      GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam);

	world.cam.target = (Vector2){ 0, speed+world.cam.target.y };

	draw_character_fall(charmain.x, charmain.y);

        hitbox_tunnel_left = (Rectangle){
                        -tunnel_spacing-(world.tex.width*tunnel_scale),
                        floor(unit_min.y),
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)};

        hitbox_tunnel_right = (Rectangle){
                        tunnel_spacing,
                        floor(unit_min.y),
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)};

        for (i  = floor(unit_min.y/real_tunnel_height);
                        i <= unit_max.y;
                        i += real_tunnel_height) {

                draw_tunnel_unit(0, i, world.tex);
        }

        if (    CheckCollisionPointRec(hitbox_character, hitbox_tunnel_left) ||
                CheckCollisionPointRec(hitbox_character, hitbox_tunnel_right)) {
                current_worldstate = W_DEATH;
        }

	if (hitbox_character.y >= starting_height) {
		current_worldstate = W_PLAY;
	}

}

void world_death() 
{
	draw_character_fall(charmain.x, charmain.y);
        recursive_draw();
        if (IsMouseButtonPressed(0) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x <= -tunnel_spacing) &&
        !(GetScreenToWorld2D(GetMousePosition(), world.cam).x  >= tunnel_spacing)) {
                current_worldstate = W_TRANSITION;
        }
}

void recursive_draw() 
{
	float i;
	float j;
	int tmp = 1;

        unit_max =      GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam);
        unit_min =      GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam);

        for (i  = floor(unit_min.y/real_tunnel_height);
	i <= unit_max.y;
	i += real_tunnel_height) {
                draw_tunnel_unit(0, i, world.tex);

	        for (j  = tunnel_scale + real_tunnel_width;
        	j <= unit_max.x;
        	j += real_tunnel_width) {
        	        draw_tunnel_unit(j, i, outer_world_tex); 
        	}
        }

/*temp obstacle code*/

        for (i  = floor(unit_min.y/real_tunnel_height);
	i <= unit_max.y;
	i += real_tunnel_height) {
		if (i < starting_height) {

			continue;
		}

                Rectangle obstaclepos = (Rectangle){
                        obstacle_randomizer(&tmp),
                        i,
                        (world.obstacletex.width*obstacle_scale),
                        (world.obstacletex.height*obstacle_scale)};

                draw_obstacle_unit(obstaclepos);
		DrawCircleV(hitbox_character, collision_radius, RED);
	        if (CheckCollisionCircleRec(hitbox_character, collision_radius,  obstaclepos)) {
	                current_worldstate = W_DEATH;
			current_scene = S_DEATH;
	        }
        }

}

int obstacle_randomizer(int* x)
{
	int value;
	value = (abs(*x+=seed)) % /*random*/
	(int)(tunnel_spacing*2-(world.obstacletex.width*obstacle_scale)); /*limit*/
	value -= tunnel_spacing; /*centering the obstacle position*/
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
void draw_tunnel_unit(float x, float y, Texture2D tex)
{
	/*tunnel 1 (left)*/
        DrawTexturePro(
                tex,
                (Rectangle){0, 0, tex.width, tex.height},
                (Rectangle){
                        -tunnel_spacing - x,
                        y,
                        (tex.width*tunnel_scale),
                        (tex.height*tunnel_scale)},
                (Vector2){tex.width*tunnel_scale, 0}, 
                0,
                WHITE);

        /*tunnel 2 (right)*/
        DrawTexturePro(
                tex,
                (Rectangle){0, 0, -tex.width, tex.height},
                (Rectangle){
                        tunnel_spacing + x,
                        y,
                        (tex.width*tunnel_scale),
                        (tex.height*tunnel_scale)},
                (Vector2){0, 0}, 
                0,
                WHITE);

}
