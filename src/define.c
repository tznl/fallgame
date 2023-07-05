#include "include/define.h"
#include "include/scenemanager.h"

/*
world data. move to a seperate file later
*/

enum worldstate current_worldstate = W_STATIC;

/*
universal data
*/

Camera2D cam;
enum GameScreen current_scene = S_TITLE;
int screen_width;
int screen_height;
int fps_cap      = 60;
char personal_best[10]; 
