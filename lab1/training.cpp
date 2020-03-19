#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"

#include <cmath>
/*
	export CFLAGS="`sdl-config --cflags` -I../../../libs/SDL_draw-1.2.13/include"
	export LIBS="`sdl-config --libs` ../../../libs/SDL_draw-1.2.13/src/.libs/libSDL_draw.a"
	g++ -o test training.cpp -Wall $CFLAGS $LIBS -lSDL -lSDL_ttf -lSDL_draw && ./test && rm test
*/


const int window_Width = 600;
const int window_Height = 600;

struct Field {
	int x1, x2, y1, y2, spX, spY, offsetX, offsetY;
};

char* Int_To_Chars(int number) {
	char* result;
	sprintf(result, "%d", number);
	return result;
}

int getBigger(int a, int b) {
	return a > b ? a : b;
}

void Draw_Field(SDL_Surface* screen, TTF_Font* fnt, Field field) {
	std::cout << "test";
	int lengthOfLine = 5;
	SDL_Surface* text_surface = NULL;
	SDL_Rect dest;
	dest.w = 1;
  dest.h = 1;

	if (field.y1 <= 0 && field.y2 >= 0) {
		Draw_HLine(screen,
            	0, field.offsetY, 600,
              SDL_MapRGB(screen->format, 255, 255, 255));
	}
	if (field.x1 <= 0 && field.x2 >= 0) {
		Draw_VLine(screen,
								field.offsetX, 0, 600,
								SDL_MapRGB(screen->format, 255, 255, 255));
	}

	// dest.y = offsetY + 10;
	for (int x = 0, charNumber = field.x1; x < 600; x += field.spX, charNumber++) {
		Draw_VLine(screen,
            	x, field.offsetY - lengthOfLine, field.offsetY + lengthOfLine,
              SDL_MapRGB(screen->format, 255, 255, 255));
		// dest.x = x - 2;
		// if (x == offsetX)
		// 	dest.x -= 16;
		// if (text_surface = TTF_RenderUTF8_Solid(fnt, Int_To_Chars(charNumber), {255,255,255})) {
		// 	SDL_BlitSurface(text_surface, NULL, screen, &dest);
		// 	SDL_FreeSurface(text_surface);
		// 	text_surface = NULL;
		// }
	}

	// dest.x = offsetX - 20;
	for (int y = 0, charNumber = field.y2; y < 600; y += field.spY, charNumber--) {
		Draw_HLine(screen,
            	field.offsetX - lengthOfLine, y, field.offsetX + lengthOfLine,
              SDL_MapRGB(screen->format, 255, 255, 255));
		// if (charNumber == 0)
		// 	continue;
		// dest.y = y - 8;
		// if (text_surface = TTF_RenderUTF8_Solid(fnt, Int_To_Chars(charNumber), {255,255,255})) {
		// 	SDL_BlitSurface(text_surface, NULL, screen, &dest);
		// 	SDL_FreeSurface(text_surface);
		// 	text_surface = NULL;
		// }
	}
}

float foo(float x) {
	return (x*x - 3) / (x + 2);
}

// void Draw_Graphic(SDL_Surface* screen) {
// 	int y = 0;
// 	for (int x = 0; x < 600; x++) {
// 		y = int(460 - foo((x - 60) / 60.0) * 60);
// 		if (y < 0 || y > 600)
// 			break;
// 		Draw_Pixel(screen,
//             	x, y,
//               SDL_MapRGB(screen->format, 0, 255, 0));
// 	}
// }

Field readField() {
	Field field;
	std::cout << "Enter x1 and x2 coords of borders" << std::endl;
	std::cin >> field.x1 >> field.x2;
	field.y1 = (int) foo(field.x1);
	field.y2 = (int) foo(field.x2);
	field.spX = (int) (window_Width / (field.x2 - field.x1));
	field.spY = (int) (window_Height / abs(field.y2 - field.y1));

	if (field.x1 <= 0 && field.x2 >= 0) {
		field.offsetX = field.spX * (-field.x1);
	} else if (field.x2 < 0) {
		field.offsetX = 600;
	} else if (field.x1 > 0) {
		field.offsetX = 0;
	}

	if (field.y1 <= 0 && field.y2 >= 0) {
		field.offsetY = field.spY * field.y2;
	} else if (field.y2 < 0) {
		field.offsetX = 0;
	} else if (field.y1 > 0) {
		field.offsetX = 600;
	}

	return field;
}

int main() {
	SDL_Surface* screen;
	SDL_Event event;
	TTF_Font* fnt = NULL;
	Field field = readField();

	if (SDL_Init(SDL_INIT_VIDEO))
		return 1;
	if (TTF_Init())
 		return 1;

	screen = SDL_SetVideoMode(600,600,32,SDL_ANYFORMAT);
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

	Draw_Field(screen, fnt, field);
	// Draw_Graphic(screen);

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