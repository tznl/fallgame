#include "raylib.h"
#include "../include/define.h"
#include "../include/scene.h"
#include <stdio.h>

struct resource world;

extern int screen_width;
extern int screen_height;

void scene_load_world()
{
        world.tex = LoadTexture("resource/dirt_flat.png");

        world.cam = (Camera2D){0};
        world.cam.target = (Vector2){ 0.0f, 0.0f };
        world.cam.offset = (Vector2){ screen_width/2.0f, screen_height/2.0f };
        world.cam.rotation = 0.0f;
        world.cam.zoom = 1.0f;
}

void scene_draw_world()
{
        int tunnel_spacing = 150;
        int tunnel_height = 0;
        float tunnel_scale = 0.25;

        ClearBackground(RAYWHITE);
 
        BeginMode2D(world.cam);
        //tunnel 1 (left)
        DrawTexturePro(
                world.tex,
                (Rectangle){0, 0, world.tex.width, world.tex.height},
                (Rectangle){
                        -tunnel_spacing,
                        tunnel_height,
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
                        tunnel_height,
                        (world.tex.width*tunnel_scale),
                        (world.tex.height*tunnel_scale)},
                (Vector2){0, 0},
                0,
                WHITE);

		Vector2 tmp_pos = GetScreenToWorld2D( (Vector2){0 , 427}, world.cam );
		float tmp_x = tmp_pos.x;
		float tmp_y = tmp_pos.y;
		printf("x: %f, y: %f\n", tmp_x, tmp_y);

        EndMode2D();
}
