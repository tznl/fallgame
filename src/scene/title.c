#include "raylib.h"
#include "../include/scene.h"
#include "../include/define.h"
#include "../include/codepoints.h"
#include <stdlib.h>
#include <string.h>

struct resource title;

char *titlename = "fallgame";

void scene_load_title()
{
	int codepointCount = 0;
	int *codepoints = LoadCodepoints(titlename, &codepointCount);
	int codepointsNoDupsCount = 0;
	int *codepointsNoDups = CodepointRemoveDuplicates(
	                codepoints, 
	                codepointCount, 
	                &codepointsNoDupsCount);

	UnloadCodepoints(codepoints);
	
	title.noto = LoadFontEx(
                "resource/font/noto/NotoSerifSC-Regular.otf", 
                20, 
                codepointsNoDups, 
                codepointsNoDupsCount);

	SetTextureFilter(title.noto.texture, TEXTURE_FILTER_BILINEAR);
	free(codepointsNoDups);

	scene_load_world();
}

void scene_draw_title()
{
	scene_draw_world();

	DrawTextEx(
		title.noto, 
		titlename, 
		(Vector2){(screen_width/2) - 20, (screen_height/2) - 20},
		48, 
		5, 
		BLACK);
}
