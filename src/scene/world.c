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

bool tmp_collide; /*trying to figure out how to modify a global*/

int offset              = 0;
int tunnel_spacing      = 150;
int real_tunnel_height;
int real_tunnel_width;
int seed		= 0; 
int starting_height	= 10*100; /*real world position is shown divided by 100 in game*/
int visibility		= 427;

Rectangle hitbox_tunnel_left;
Rectangle hitbox_tunnel_right;
Rectangle obstaclepos;

float collision_radius = 1;
float begin_speed = 10;
float speed;
float acceleration;
float terminal_velocity;
float character_scale	= 0.15;
float tunnel_scale      = 0.25;
float obstacle_scale	= 0.05;
float sound_volume;

Vector2 unit_max;
Vector2 unit_min;
Vector2 start_unit_max;
Vector2 start_unit_min;
Vector2 hitbox_character;

struct world_res *current_res;

void world_load()
{
	assign_default();
	current_res = &default_res;


        world.cam = (Camera2D){0};
        world.cam.target = (Vector2){ 0, 0 };
        world.cam.offset = (Vector2){ screen_width/2.0f, screen_height/2.0f };
        world.cam.rotation = 0.0f;
        world.cam.zoom = ((float)screen_height / visibility) / 2;

        start_unit_max =      GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam);
        start_unit_min =      GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam);

	speed = begin_speed;

	acceleration = 0.005;

	terminal_velocity = 25;

	charmain.move = 10;

	real_tunnel_height = current_res->tex.height*tunnel_scale;	
	real_tunnel_width = current_res->tex.width*tunnel_scale;

	srand(time(NULL));
	seed = rand();

}

void play_sound()
{
	if (!IsSoundPlaying(current_res->falling_sound)) {
		PlaySound(current_res->falling_sound);
	}
	if (sound_volume < 1) {
		SetSoundVolume(current_res->falling_sound, sound_volume+=0.01);
	}
}

void world_static()
{
	recursive_draw_env();
        DrawTexturePro(
                current_res->character,
                (Rectangle){0, 0, current_res->character.width, current_res->character.height},
                (Rectangle){
                        0,
                        0,
                        current_res->character.width*character_scale,
                        current_res->character.height*character_scale},
                (Vector2)       {(current_res->character.width*character_scale)/2,
                                current_res->character.height*character_scale},
                0,
                WHITE);

	recursive_draw();
}

void world_transition()
{
        charmain.x = GetScreenToWorld2D(GetMousePosition(), world.cam).x;
        charmain.y = (int)floor(GetScreenToWorld2D((Vector2){
                screen_width, screen_height/4}, world.cam).y);
        hitbox_character = (Vector2) {0, 0};

	tmp_collide = false;
        seed = rand();
        recursive_draw_env();
        draw_character_fall(charmain.x, charmain.y);
        recursive_draw();
	sound_volume = 0;
	speed = begin_speed;
	SetSoundVolume(current_res->falling_sound, sound_volume);
	PlaySound(current_res->falling_sound);
	current_worldstate = W_PLAY;
	current_scene = S_PLAY;
	world.cam.target = (Vector2){ 0.0f, screen_height/4 };
}

void world_play()
{
	charmain.x = GetScreenToWorld2D(GetMousePosition(), world.cam).x;
	charmain.y = (int)floor(GetScreenToWorld2D((Vector2){
		screen_width, screen_height/4}, world.cam).y);
	hitbox_character = (Vector2) {charmain.x, charmain.y};

        play_sound();
	recursive_draw_env();
	draw_character_fall(charmain.x, charmain.y);
	recursive_draw();

	if (tmp_collide ||
	charmain.x >= tunnel_spacing ||
	charmain.x <= -tunnel_spacing) {
		current_worldstate = W_DEATH;
		current_scene = S_DEATH;
		PlaySound(current_res->death_sound);
		if (atoi(personal_best) < (int)hitbox_character.y/100) {
			sprintf(personal_best, "%d", (int)hitbox_character.y/100);
			SaveFileText("personal_record", personal_best);
		}
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

        for (i  = floor(unit_min.y/real_tunnel_height);
                        i <= unit_max.y;
                        i += real_tunnel_height) {
		recursive_draw_env();
                draw_tunnel_unit(tunnel_spacing, i, current_res->tex);
        }

        if (tmp_collide ||
        charmain.x >= tunnel_spacing ||
        charmain.x <= -tunnel_spacing) {
                current_worldstate = W_DEATH;
                current_scene = S_DEATH;
                PlaySound(current_res->death_sound);
	}

	if (hitbox_character.y >= starting_height) {
		current_worldstate = W_PLAY;
	}

}

void world_death() 
{
        if (IsSoundPlaying(current_res->falling_sound)) {
                StopSound(current_res->falling_sound);
        }


	recursive_draw_env();
	draw_character_fall(charmain.x, charmain.y+=speed);

        recursive_draw();
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

        hitbox_tunnel_left = (Rectangle){
                        -tunnel_spacing-(current_res->tex.width*tunnel_scale),
                        floor(unit_min.y),
                        (current_res->tex.width*tunnel_scale),
                        (current_res->tex.height*tunnel_scale)};

        hitbox_tunnel_right = (Rectangle){
                        tunnel_spacing,
                        floor(unit_min.y),
                        (current_res->tex.width*tunnel_scale),
                        (current_res->tex.height*tunnel_scale)};

        for (i  = floor(unit_min.y/real_tunnel_height);
	i <= unit_max.y;
	i += real_tunnel_height) {
                draw_tunnel_unit(tunnel_spacing, i, default_res.tex);
                if (CheckCollisionCircleRec(
                        hitbox_character, collision_radius,  hitbox_tunnel_left)) {
                        tmp_collide = true;
                        draw_tunnel_left(
				tunnel_spacing, charmain.y-(real_tunnel_height/1.07), 
				current_res->tunnel_inner_death);
                } else if (CheckCollisionCircleRec(
                        hitbox_character, collision_radius,  hitbox_tunnel_right)) {
                        tmp_collide = true;
                        draw_tunnel_right(
				tunnel_spacing, charmain.y-(real_tunnel_height/1.25), 
				current_res->tunnel_inner_death);
		}
	        for (j  = tunnel_scale + real_tunnel_width;
        	j <= unit_max.x;
        	j += real_tunnel_width) {
        	        draw_tunnel_unit(j + tunnel_spacing, i, current_res->outer_world_tex);
                }
        }

/*temp obstacle code*/

        for (i  = floor(unit_min.y/real_tunnel_height);
	i <= unit_max.y;
	i += real_tunnel_height) {
		if (i < starting_height) {
			continue;
		}
                obstaclepos = (Rectangle){
                        obstacle_randomizer(&tmp),
                        i,
                        (current_res->obstacletex.width*obstacle_scale),
                        (current_res->obstacletex.height*obstacle_scale)};

                draw_obstacle_unit(obstaclepos, current_res->obstacletex);
                if (CheckCollisionCircleRec(hitbox_character, collision_radius,  obstaclepos)) {
                        tmp_collide = true;
			draw_obstacle_unit(obstaclepos, current_res->obstacle_death);
                }
		DrawCircleV(hitbox_character, collision_radius, RED);
        }

}

void recursive_draw_env()
{
        float i;

        unit_max =      GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam);
        unit_min =      GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam);
	float ultimate_max;
	if (unit_min.y <= 0) {
	        if ((screen_width) >= screen_height/2) {
                	ultimate_max = start_unit_max.x*2;
        	} else {
        	ultimate_max = fabs(start_unit_min.y);
        	}

        	Rectangle background = (Rectangle){
        	        -(ultimate_max/2),
        	        -(ultimate_max),
        	        ultimate_max,
        	        ultimate_max};

        	DrawTexturePro(
        	        current_res->sky_background,
        	        (Rectangle) {0, 0, current_res->tunnel_background.width, current_res->tunnel_background.height},
        	        background,
        	        (Vector2){0, 0},
        	        0,
        	        WHITE);
	}


        for (i  = floor(unit_min.y/real_tunnel_height);
        i <= unit_max.y*2;
        i += real_tunnel_height) {
		DrawTexturePro(
                	current_res->tunnel_background,
                	(Rectangle){0, 0, current_res->tunnel_background.width, current_res->tunnel_background.height},
                	(Rectangle){
                	        -tunnel_spacing,
                	        i,
                	        (tunnel_spacing*2),
                	        (current_res->tunnel_background.height*tunnel_scale)},
                	(Vector2){0, 0},
                	0,
                	WHITE);
	}
}

int obstacle_randomizer(int* x)
{
	int value;
	value = (abs(*x+=seed)) % /*random*/
	(int)(tunnel_spacing*2-(current_res->obstacletex.width*obstacle_scale)); /*limit*/
	value -= tunnel_spacing; /*centering the obstacle position*/
	return value;
}

void draw_character_fall(int x, int y)
{
	DrawTexturePro(
		current_res->character,
		(Rectangle){0, 0, current_res->character.width, -current_res->character.height},
		(Rectangle){
			charmain.x,
			charmain.y,
			current_res->character.width*character_scale,
			current_res->character.height*character_scale},
		(Vector2)	{(current_res->character.width*character_scale)/2, 
				current_res->character.height*character_scale},
		0,
		WHITE);
}

void draw_obstacle_unit(Rectangle draw_where, Texture2D tex)
{
        DrawTexturePro(
                tex,
                (Rectangle){0, 0, current_res->obstacletex.width, current_res->obstacletex.height},
                draw_where,
                (Vector2){0, 0}, 
                0,
                WHITE);

}
void draw_tunnel_unit(float x, float y, Texture2D tex)
{
        draw_tunnel_left(x, y, tex);
        draw_tunnel_right(x, y, tex);
}

void draw_tunnel_left(float x, float y, Texture2D tex)
{
        /*tunnel 1 (left)*/
        DrawTexturePro(
                tex,
                (Rectangle){0, 0, tex.width, tex.height},
                (Rectangle){
                        -x,
                        y,
                        (tex.width*tunnel_scale),
                        (tex.height*tunnel_scale)},
                (Vector2){tex.width*tunnel_scale, 0},
                0,
                WHITE);
}

void draw_tunnel_right(float x, float y, Texture2D tex)
{
        /*tunnel 2 (right)*/
        DrawTexturePro(
                tex,
                (Rectangle){0, 0, -tex.width, tex.height},
                (Rectangle){
                        x,
                        y,
                        (tex.width*tunnel_scale),
                        (tex.height*tunnel_scale)},
                (Vector2){0, 0},
                0,
                WHITE);
}
