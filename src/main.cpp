#include <cmath>
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

int random(int min, int max)
{
	int r = rand() % (max + 1);
	if (r < min) r += min;
	return r;
}

void RenderTree(int lineLength, int startX, int startY, int angle)
{
	// Uncomment for slow animation
	//SDL_RenderPresent(renderer);
	
	double angleInRad = ((double)angle * M_PI) / 180.0;
	
	int endX = (int)(startX - (double)lineLength * cos(angleInRad));
	int endY = (int)(startY - (double)lineLength * sin(angleInRad));
	
	SDL_SetRenderDrawColor(renderer, random(0, 255), random(0, 255), random(0, 255), 100);
	SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
	
	if (lineLength > 25)
	{
		RenderTree(lineLength - (random(5, 10)), endX, endY, angle + random(15, 25));
		RenderTree(lineLength - (random(5, 10)), endX, endY, angle - random(15, 25));
		
		// Uncomment for a little faster animation
		//SDL_RenderPresent(renderer);
	}
}

int main()
{
	srand(time(NULL));
	
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		cout << "SDL VIDEO INITIALIZATION ERROR!, ERROR TEXT: " << SDL_GetError() << endl;
		return 0;
	}
	
	SDL_Rect* r = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	SDL_GetDisplayBounds(0, r);
	int SCREEN_WIDTH = r -> w;
	int SCREEN_HEIGHT = r -> h;
	free(r);
	
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN, &window, &renderer);
	
	if (window == NULL || renderer == NULL)
	{
		cout << "ERROR WHILE CREATING WINDOW OR RENDERER! ERROR TEXT: " << SDL_GetError() << endl;
		return 0;
	}
	
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	RenderTree((SCREEN_HEIGHT - 100) / 10, (SCREEN_WIDTH >> 1) - 1, SCREEN_HEIGHT - 100, 90);
	
	SDL_RenderPresent(renderer);
	
	bool done = false;
	
	while (!done)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					done = true;
				}
				
				else if (event.key.keysym.sym == SDLK_SPACE)
				{
					SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderClear(renderer);
					RenderTree((SCREEN_HEIGHT - 100) / 10, (SCREEN_WIDTH >> 1) - 1, SCREEN_HEIGHT - 100, 90);
					SDL_RenderPresent(renderer);
				}
			}
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}