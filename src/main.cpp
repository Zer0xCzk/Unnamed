#include "engine.h"
#include "sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "object.h"

// Forward function declarations
void Update(float dt);
void RenderFrame(float dt);

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int mx;
int my;
Object player{ 450,450,64,64,LoadSprite("assets/Test.png"),{player.box.w / 2,player.box.h / 2}};

//=============================================================================
int main(int argc, char* argv[])
{
	if (!InitSDL())
	{
		return 1;
	}

	if (!CreateWindow("The Game", WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		return 1;
	}

	player.sprite = LoadSprite("assets/Test.png");

	// Push functions to the game loop
	StartLoop(Update, RenderFrame);
	
	FreeSprite(player.sprite);
	CleanUp();
	return 0;
}

//=============================================================================
float getangle(int xplayer, int yplayer, int xcursor, int ycursor)
{
	float angle = -90 + atan2(yplayer - ycursor, xplayer - xcursor) * (180 / M_PI);
	return angle >= 0 ? angle : 360 + angle;
}

void Inputs()
{
	if (IsKeyDown(SDL_SCANCODE_A))
	{
		player.angle -= 1;
	}
	if (IsKeyDown(SDL_SCANCODE_D))
	{
		player.angle += 1;
	}
}

void Update(float dt)
{
	GetMousePosition(&mx, &my);
	Inputs();
	if (IsKeyDown(SDL_SCANCODE_ESCAPE))
		ExitGame();
}

void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);
	SDL_RenderCopyEx(gRenderer, player.sprite.texture, NULL, &player.box, getangle(player.center.x,player.center.y,mx,my), &player.center, SDL_FLIP_NONE);
}
