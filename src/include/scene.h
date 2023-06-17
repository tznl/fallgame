#ifndef SCENE_H
#define SCENE_H

void screen_load_font();
void scene_unload_title();
void screen_load_title();
void screen_draw_title();
void screen_draw_play();
void screen_draw_death();

void world_load();
void world_static();
void world_transition();
void world_death();
void world_play();
void world_starting();
void draw_obstacle_unit(Rectangle draw_where);
void draw_tunnel_unit(float x, float y, Texture2D tex);
void draw_character_fall(int x, int y);
int obstacle_randomizer(int* x);
void recursive_draw();

#endif
