#include "engine.h"
#include "sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "object.h"
#include <math.h>

// Forward function declarations
void Update(float dt);
void RenderFrame(float dt);

#define WW 1680	
#define WH 1050

int mx;
int my;
int wx;
int wy;
Object playert = { { 450 ,450 ,64 , 64 }, { playert.box.w / 2, playert.box.h / 2 }, 500, 0 };
Object test{ 0,0,60,60};
Sprite playert_sprite;

//=============================================================================
int main(int argc, char* argv[])
{
	if (!InitSDL())
	{
		return 1;
	}

	if (!CreateWindow("PeeDee", WW, WH))
	{
		return 1;
	}
	SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_BORDERLESS);
	

	playert_sprite = LoadSprite("assets/playert.png");

	// Push functions to the game loop
	StartLoop(Update, RenderFrame);
	
	FreeSprite(playert_sprite);
	CleanUp();
	return 0;
}

//=============================================================================

// This needs more work, seems to be pointing towards bottom right of the cursor
int LookAt()
{
	int DeltaX = playert.box.x + playert.centert.x - mx;
	int DeltaY = playert.box.y +	playert.center.y - my;
	double result = (atan2(-DeltaX, DeltaY) * 180.00000) / 3.141592;
	return (int)result;
}

void Inputs(double dt)
{
	if (IsKeyDown(SDL_SCANCODE_W) && playert.box.y >= 0)
	{
		playert.box.y -= (int)(playert.speed * dt + 0.5f);
		
	}
	if (IsKeyDown(SDL_SCANCODE_S) && playert.box.y + playert.box.h <= WH)
	{
		playert.box.y += (int)(playert.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_A) && playert.box.x >= 0)
	{
		playert.box.x -= (int)(playert.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_D) && playert.box.x + playert.box.w <= WW)
	{
		playert.box.x += (int)(playert.speed * dt + 0.5f);
	}
}

void Update(float dt)
{
	SDL_GetMouseState(&mx, &my);
	Inputs(dt);
	if (IsKeyDown(SDL_SCANCODE_ESCAPE))
		ExitGame();

}

void RenderFrame(float interpolation)
{
	// Clear screen
	SDL_SetRenderDrawColor(gRenderer, 65, 105, 225, 255);
	SDL_RenderClear(gRenderer);
	SDL_RenderCopyEx(gRenderer, playert_sprite.texture, NULL, &playert.box, LookAt() , &playert.center, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);
	SDL_RenderFillRect(gRenderer, &test.box);
}
