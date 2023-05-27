#include "include/define.h"
#include "include/scenemanager.h"

//world data. move to a seperate file later
enum worldstate current_worldstate = STATIC;

struct resource world;

//universal data
enum GameScreen current_scene = TITLE;
int screen_width  = 480;
int screen_height = 854;
int fps_cap      = 60; 
