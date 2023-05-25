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
int real_tunnel_height;

float tunnel_scale 	= 0.25;
float unit_max;

bool started            = false;


void scene_load_world()
{
//	float bs = GetScreenToWorld2D((Vector2){screen_width, screen_height}, world.cam).y;
	float bs = 0;
        world.tex = LoadTexture("resource/dirt_flat.png");

        world.cam = (Camera2D){0};
        world.cam.target = (Vector2){ 0.0f, bs };
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

	if (IsKeyPressed(KEY_SPACE)) {
		started = true;
	}

	BeginMode2D(world.cam);
	if (!started) unstarted();
	if (started) move_to_start();
	if (started) tunnel_height--;
	printf("out of for loop: %d\n\n", count);
	count++;
        EndMode2D();

}

void move_to_start()
{
	world.cam.target = (Vector2){ 0.0f, screen_height/4 };

        for (float i = tunnel_height; i <= unit_max; i += real_tunnel_height) {
                draw_tunnel_unit(i);
		printf("for: i: %f\n", i);
        }
}

void unstarted()
{
        for (float i = tunnel_height; i <= unit_max; i += real_tunnel_height) {
                draw_tunnel_unit(i);
        }
}

void draw_tunnel_unit(float offset)
{
        unit_max                =
                (float)(GetScreenToWorld2D(
                (Vector2){screen_width, screen_height}, world.cam).y); 


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
