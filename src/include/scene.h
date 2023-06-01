#ifndef SCENE_H
#define SCENE_H

void screen_load_font();
void scene_unload_title();
void screen_load_title();
void screen_draw_title();
void screen_draw_play();

//void scene_unload_world();
void world_load();
void world_static();
void world_transition();
void world_death();
void world_play();
void draw_tunnel_unit(float offset);
void draw_character_fall();
//void move_to_start();
//void unstarted();
void recursive_draw();

//void scene_unload_test();
//void scene_load_test();
//void scene_draw_test();
#endif
