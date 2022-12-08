#pragma once

#include "SDL_main.h"
#include "SDL.h"
#include <stdbool.h>
#include "sprite.h"

struct Object
{
	SDL_Rect box;
	SDL_Point center;
	float speed;
	float angle;
};