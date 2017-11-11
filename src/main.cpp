#include <cmath>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <SDL2/SDL.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
Uint8 r, g, b;

int random(int min, int max)
{
	int ret = rand() % (max + 1);
	if (ret < min) ret += min;
	return ret;
}

// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm

double inline round(double x) { return floor(x + 0.5); }
double inline fPart(double x) { return x - floor(x); }
double inline rfPart(double x) { return 1 - fPart(x); }

void plot(int x, int y, double brightness)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, brightness * 0xFF);
	SDL_RenderDrawPoint(renderer, x, y);
}

void wuLine(double x0, double y0, double x1, double y1)
{
	bool steep = fabs(y1 - y0) > fabs(x1 - x0);

	if (steep)
	{
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	double dx = x1 - x0;
	double dy = y1 - y0;

	double gradient = dx == 0.0  ? 1.0 : dy / dx;

	double xEnd = round(x0);
	double yEnd = y0 + gradient * (xEnd - x0);
	double xGap = rfPart(x0 + 0.5);
	double xPixel1 = xEnd;
	double yPixel1 = floor(yEnd);

	if (steep)
	{
		plot(yPixel1,     xPixel1, rfPart(yEnd) * xGap);
		plot(yPixel1 + 1, xPixel1,  fPart(yEnd) * xGap);
	}

	else
	{
		plot(xPixel1, yPixel1,    rfPart(yEnd) * xGap);
		plot(xPixel1, yPixel1 + 1, fPart(yEnd) * xGap);
	}
	
	double yIntersection = yEnd + gradient;
	
	xEnd = round(x1);
	yEnd = y1 + gradient * (xEnd - x1);
	xGap = fPart(x1 + 0.5);
	double xPixel2 = xEnd;
	double yPixel2 = floor(yEnd);

	if (steep)
	{
		plot(yPixel2,     xPixel2, rfPart(yEnd) * xGap);
		plot(yPixel2 + 1, xPixel2,  fPart(yEnd) * xGap);
		
		for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
		{
			plot(yIntersection    , x, rfPart(yIntersection));
			plot(yIntersection + 1, x,  fPart(yIntersection));
			yIntersection += gradient;
		}
	}

	else
	{
		plot(xPixel2, yPixel2,    rfPart(yEnd) * xGap);
		plot(xPixel2, yPixel2 + 1, fPart(yEnd) * xGap);
		
		for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
		{
			plot(x, yIntersection    , rfPart(yIntersection));
			plot(x, yIntersection + 1,  fPart(yIntersection));
			yIntersection += gradient;
		}
	}
}

void RenderTree(int lineLength, int startX, int startY, int angle)
{
	// Uncomment for slow animation
	//SDL_RenderPresent(renderer);
	
	double angleInRad = ((double)angle * M_PI) / 180.0;
	
	int endX = (int)(startX - (double)lineLength * cos(angleInRad));
	int endY = (int)(startY - (double)lineLength * sin(angleInRad));
	
	r = random(0, 255);
	g = random(0, 255);
	b = random(0, 255);
	
	wuLine(startX, startY, endX, endY);
	
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(renderer);
	
	RenderTree((double)(SCREEN_HEIGHT - 100) / 7.5, (SCREEN_WIDTH >> 1) - 1, SCREEN_HEIGHT - 100, 90);
	
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
					RenderTree((double)(SCREEN_HEIGHT - 100) / 7.5, (SCREEN_WIDTH >> 1) - 1, SCREEN_HEIGHT - 100, 90);
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
