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

#define WW 1920
#define WH 1080

int mx;
int my;
int wx;
int wy;
Object player{ 450,450,64,64,LoadSprite("assets/Test.png"),{player.box.w / 2,player.box.h / 2},500};
Object test{ 0,0,60,60};

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
	

	player.sprite = LoadSprite("assets/Test.png");

	// Push functions to the game loop
	StartLoop(Update, RenderFrame);
	
	FreeSprite(player.sprite);
	CleanUp();
	return 0;
}

//=============================================================================

// This needs more work, seems to be pointing towards bottom right of the cursor
int LookAt()
{
	int DeltaX;
	int DeltaY;
	double result;
	DeltaX = player.box.x - mx;
	DeltaY = player.box.y - my;
	result = (atan2(-DeltaX, DeltaY) * 180.00000) / 3.141592;
	return result;
}

void Inputs(double dt)
{
	if (IsKeyDown(SDL_SCANCODE_W) && player.box.y >= 0)
	{
		player.box.y -= (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_S) && player.box.y + player.box.h <= WH)
	{
		player.box.y += (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_A) && player.box.x >= 0)
	{
		player.box.x -= (int)(player.speed * dt + 0.5f);
	}
	if (IsKeyDown(SDL_SCANCODE_D) && player.box.x + player.box.w <= WW)
	{
		player.box.x += (int)(player.speed * dt + 0.5f);
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
	SDL_RenderCopyEx(gRenderer, player.sprite.texture, NULL, &player.box, LookAt(), &player.center, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255);
	SDL_RenderFillRect(gRenderer, &test.box);
}
