#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
/*
	export CFLAGS="`sdl-config --cflags` -I../../../libs/SDL_draw-1.2.13/include"
	export LIBS="`sdl-config --libs` ../../../libs/SDL_draw-1.2.13/src/.libs/libSDL_draw.a"
	g++ -o test 1.cpp -Wall $CFLAGS $LIBS -lSDL -lSDL_ttf -lSDL_draw && ./test && rm test
*/

// y = x^2 - 3 / x + 2, x in [-1,9]

char* IntToChars(int number) {
	char* result;
	sprintf(result, "%d", number);
	return result;
}

void Draw_Field(SDL_Surface* screen, TTF_Font* fnt) {
	int lengthOfLine = 5;
	SDL_Surface* text_surface = NULL;
	SDL_Rect dest;
	dest.w = 1;
  dest.h = 1;

	Draw_HLine(screen,
            	0, 460, 600,
              SDL_MapRGB(screen->format, 255, 255, 255));
	Draw_VLine(screen,
            	60, 0, 600,
              SDL_MapRGB(screen->format, 255, 255, 255));
	dest.y = 470;
	for (int dx = 0; dx < 600; dx += 60) {
		Draw_VLine(screen,
            	dx, 460 - lengthOfLine, 460 + lengthOfLine,
              SDL_MapRGB(screen->format, 255, 255, 255));
		dest.x = dx - 2;
		if (dx == 60)
			dest.x -= 16;
		if (text_surface = TTF_RenderUTF8_Solid(fnt, IntToChars((dx - 60) / 60), {255,255,255})) {
			SDL_BlitSurface(text_surface, NULL, screen, &dest);
			SDL_FreeSurface(text_surface);
			text_surface = NULL;
		}
	}

	dest.x = 40;
	for (int dy = 40; dy < 600; dy += 60) {
		Draw_HLine(screen,
            	60 - lengthOfLine, dy, 60 + lengthOfLine,
              SDL_MapRGB(screen->format, 255, 255, 255));
		if (dy == 460)
			continue;
		dest.y = dy - 8;
		if (text_surface = TTF_RenderUTF8_Solid(fnt, IntToChars(-(dy - 460) / 60), {255,255,255})) {
			SDL_BlitSurface(text_surface, NULL, screen, &dest);
			SDL_FreeSurface(text_surface);
			text_surface = NULL;
		}
	}
}

float foo(float x) {
	return (x*x - 3) / (x + 2);
}

void Draw_Graphic(SDL_Surface* screen) {
	int y = 0;
	for (int x = 0; x < 600; x++) {
		y = int(460 - foo((x - 60) / 60.0) * 60);
		if (y < 0 || y > 600)
			break;
		Draw_Pixel(screen,
            	x, y,
              SDL_MapRGB(screen->format, 0, 255, 0));
	}
}

int main() {
	SDL_Surface* screen;
	SDL_Event event;
	TTF_Font* fnt = NULL;

	if (SDL_Init(SDL_INIT_VIDEO))
		return 1;
	if (TTF_Init())
 		return 1;

	screen = SDL_SetVideoMode(600, 600, 32, SDL_ANYFORMAT);
	if (!screen) {
		TTF_Quit();
		SDL_Quit();
		return 1;
	}
	if (!(fnt = TTF_OpenFont("Ubuntu.ttf", 14))){
		TTF_Quit();
		SDL_Quit();
		return 3;
	}
	
	Draw_Field(screen, fnt);
	Draw_Graphic(screen);

	SDL_Flip(screen);
	while(SDL_WaitEvent(&event)) {
		if (event.type 							== SDL_QUIT ||
			 		(event.type 					== SDL_KEYDOWN &&
				 	 event.key.keysym.sym == SDLK_ESCAPE)
			 ) {
			TTF_CloseFont(fnt);
			TTF_Quit();
			SDL_Quit();
			return 0;
		}
	}
	TTF_CloseFont(fnt);
	SDL_Quit();
	TTF_Quit();
	return 2; 
}