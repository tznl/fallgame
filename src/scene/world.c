#include "raylib.h"
#include "../include/define.h"
#include "../include/scene.h"
#include <stdio.h>
#include <math.h>

struct resource world;


int offset		= 0;
int tunnel_spacing	= 150;
int tunnel_height 	= 0;
int speed		= 10;
int real_tunnel_height;

float tunnel_scale 	= 0.25;
float unit_max;
float unit_min;

bool started            = false;
bool starting		= true;

void scene_load_world()
{
        world.tex = LoadTexture("resource/dirt_flat.png");

        world.cam = (Camera2D){0};
        world.cam.target = (Vector2){ 0., 0 };
        world.cam.offset = (Vector2){ screen_width/2.0f, screen_height/2.0f };
        world.cam.rotation = 0.0f;
        world.cam.zoom = 1.0f;

	real_tunnel_height = world.tex.height*tunnel_scale;
}

void scene_draw_world()
{
        ClearBackground(RAYWHITE);

	if (IsKeyPressed(KEY_SPACE)) {
		started = true;
	}

	BeginMode2D(world.cam);

	recursive_draw();
	printf("current target.y: %f\n", world.cam.target.y); 

        EndMode2D();

}

void recursive_draw() 
{
        unit_max =      (float)(GetScreenToWorld2D(
                        (Vector2){screen_width, screen_height}, world.cam).y);
        unit_min =      (float)(GetScreenToWorld2D(
                        (Vector2){0, 0}, world.cam).y);

        if (started && starting) {
                world.cam.target = (Vector2){ 0.0f, screen_height/4 };
                starting = false;
                printf("starting tripped\n");
        } else if (started) {
		world.cam.target = (Vector2){ 0, speed+world.cam.target.y };
	}

        for (float i = tunnel_height; i <= unit_max; i += real_tunnel_height) {
                draw_tunnel_unit(i);
        }
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
