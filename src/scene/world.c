#include "raylib.h"
#include "../include/define.h"
#include "../include/scene.h"
#include <stdio.h>
#include <math.h>

struct resource world;


int offset		= 0;
int tunnel_spacing	= 150;
int tunnel_height 	= 0;
int count 		= 0; // test variable delete later

float tunnel_scale 	= 0.25;

int real_tunnel_height;
float unit_max;

void scene_load_world()
{
        world.tex = LoadTexture("resource/dirt_flat.png");

        world.cam = (Camera2D){0};
        world.cam.target = (Vector2){ 0.0f, 0.0f };
        world.cam.offset = (Vector2){ screen_width/2.0f, screen_height/2.0f };
        world.cam.rotation = 0.0f;
        world.cam.zoom = 1.0f;

	real_tunnel_height = world.tex.height*tunnel_scale;
	unit_max		= 
		(float)(GetScreenToWorld2D(
        	(Vector2){screen_width, screen_height}, world.cam).y); 
}

void scene_draw_world()
{
        ClearBackground(RAYWHITE);

	BeginMode2D(world.cam);
	for (int i = tunnel_height; i <= unit_max; i += real_tunnel_height) {
		draw_tunnel_unit(i);
	}
	printf("out of for loop: %d\n", count);
	count++;
        EndMode2D();

	tunnel_height--;
}

void draw_tunnel_unit(int offset)
{
	printf("test: %d\n", offset);
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
