#include <math.h>
#include <iostream>
#include <SDL/SDL.h>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include <vector>
#include <ctime>
#include <cstdlib>

const int scrwidth = 600, scrheight = 480, scrdepth = 32;

float distance(int x1, int y1, int x2, int y2, int r1, int r2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) - r1 - r2;
}

class Apple {
	public:
	SDL_Rect spritePos, pos;
	int dy;
	int radius;
	bool isCollided;

	Apple(SDL_Rect spritePosition, SDL_Rect surfacePosition, int deltaY, int radiusOfApple) {
		spritePos = spritePosition;
		pos = surfacePosition;
		dy = deltaY;
		radius = radiusOfApple;
		isCollided = false;
	}

	bool update(SDL_Rect posOfHedgehog, int petRadius) {
		if (pos.y + dy > 400 - spritePos.h) {
			dy = 0;
			pos.y = 400 - spritePos.h;
			isCollided = true;
		}
		pos.y += dy;

		if (distance(pos.x + spritePos.w / 2, pos.y + spritePos.h / 2, posOfHedgehog.x + 20, posOfHedgehog.y + 20, radius, petRadius) <= 0) {
			dy = 0;
			isCollided = true;
			return true;
		}
		return false;
	}
};

class Hedgehog {
	public:
	SDL_Rect spritePos, pos;
	int dx;
	int radius;
	int dir;
	bool isCollision = false;

	Hedgehog() {
		spritePos = {0, 0, 40, 40};
		pos = {20, 360, 40, 40};
		dx = 1;
		radius = 17;
		dir = 1;
	}

	void update() {
		if (!isCollision) {
			if (pos.x == scrwidth - 40) {
				dx *= -1;
				spritePos.x = 40;
			} else if (pos.x == 0) {
				dx *= -1;
				spritePos.x = 0;
			}
			pos.x += dx;
		}
	}
};

void Draw_Apple(SDL_Surface* screen, int x, int y, int radius, Uint32 color) { 
	Draw_FillCircle(screen, x, y, radius, color);
	for (size_t i = 0; i < 4; i++) {
		Draw_Line(screen, x - 1 + i, y - 5, x + 3 + i, y - radius, SDL_MapRGB(screen->format, 109,76,65));
	}
}

void Draw_Hedgehog(SDL_Surface* screen, int x, int y, int dir) {
	Draw_FillEllipse(screen, x, y, 17, 15, SDL_MapRGB(screen->format, 160, 160, 160));
	Draw_FillCircle(screen, x + 7 * dir, y, 3, SDL_MapRGB(screen->format, 0, 0, 0));
	float dfi = -dir * M_PI / 12, fi = dir == 1 ? M_PI : 0, radius = 12, length = 6;
	for (int i = 0; i < 10; i++, fi += dfi) {
		Draw_Line(screen, x + radius * cos(fi), y - radius * sin(fi), x + (radius + length) * cos(fi), y - (radius + length) * sin(fi), SDL_MapRGB(screen->format, 255,255,255));
	}
}

void Draw_Scene(SDL_Surface* background) {
	Draw_FillRect(background, 0, 0, 600, 400, SDL_MapRGB(background->format, 100,181,246));
	Draw_FillRect(background, 0, 400, 600, 80, SDL_MapRGB(background->format, 56,142,60));
}

int main() {
	srand(time(0));
	SDL_Surface* background, * sprites, * tmp;
	SDL_Event event;
	std::vector<Apple> apples;
	std::vector<SDL_Surface*> applesTmp;
	std::vector<SDL_Rect> spriteRectangles = {{80, 0, 30, 33}, {110, 0, 40, 44}, {150, 0, 20, 22}};
	std::vector<int> spriteRadiues = {15, 20, 10};
	Hedgehog pet;

	const int countOfApples = 4; // max possible 8

	for (size_t i = 0, index = rand() % 3; i < countOfApples; i++, index = rand() % 3) {
		apples.push_back(Apple(spriteRectangles[index], {50 + rand() % (scrwidth - 100), 0, 0, 0}, 1 + rand() % 2, spriteRadiues[index]));
		bool flag = true;
		while (flag) {
			flag = false;
			for (size_t j = 0; j < apples.size(); j++) {
				if (j == i) continue;
				if (distance(apples[i].pos.x, 0, apples[j].pos.x, 0, apples[i].radius, apples[j].radius) < 40) {
					flag = true;
					apples[i].pos.x = 50 + rand() % (scrwidth - 100);
				}
			}
		}
	}

	if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		std::cout << "Unable to init SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Surface* screen = SDL_SetVideoMode(scrwidth, scrheight, scrdepth, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if (!screen) {
		std::cout << "Unable to set 600x600 video: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	background = SDL_CreateRGBSurface(SDL_HWSURFACE |
		SDL_DOUBLEBUF, scrwidth, scrheight, scrdepth,
		screen->format->Rmask, screen->format->Gmask,
		screen->format->Bmask, screen->format->Amask);
	sprites = SDL_CreateRGBSurface(SDL_HWSURFACE |
		SDL_DOUBLEBUF, 600, 480, scrdepth,
		screen->format->Rmask, screen->format->Gmask,
		screen->format->Bmask, screen->format->Amask);
	tmp = SDL_CreateRGBSurface(SDL_HWSURFACE |
		SDL_DOUBLEBUF, 40, 40, scrdepth,
		screen->format->Rmask, screen->format->Gmask,
		screen->format->Bmask, screen->format->Amask);

	for (size_t i = 0; i < countOfApples; i++) {
		applesTmp.push_back(SDL_CreateRGBSurface(SDL_HWSURFACE |
			SDL_DOUBLEBUF, apples[i].spritePos.w, apples[i].spritePos.h, scrdepth,
			screen->format->Rmask, screen->format->Gmask,
			screen->format->Bmask, screen->format->Amask));
	}

	if(!(background && sprites) ) {
		std::cout << "Unable to create temporary surfaces: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Draw_Scene(background);
	SDL_BlitSurface(background, NULL, screen, NULL);

	SDL_SetColorKey(sprites, SDL_SRCCOLORKEY, SDL_MapRGB(sprites->format, 100,181,246));
	Draw_FillRect(sprites, 0, 0, 170, 44, SDL_MapRGB(sprites->format, 100,181,246));

	Draw_Hedgehog(sprites, 60, 25, -1);
	Draw_Hedgehog(sprites, 20, 25, 1);
	Draw_Apple(sprites, 95, 18, 15, SDL_MapRGB(screen->format, 244,67,54));
	Draw_Apple(sprites, 130, 24, 20, SDL_MapRGB(screen->format, 255,238,88));
	Draw_Apple(sprites, 160, 12, 10, SDL_MapRGB(screen->format, 76,175,80));

	for (size_t i = 0; i < countOfApples; i++) {
		SDL_BlitSurface(sprites, &apples[i].spritePos, screen, &apples[i].pos);
	}
	SDL_BlitSurface(sprites, &pet.spritePos, screen, &pet.pos);

	SDL_Flip(screen);
	while(SDL_WaitEvent(&event)) {
		if (event.type 							== SDL_QUIT ||
			 		(event.type 					== SDL_KEYDOWN &&
				 	 event.key.keysym.sym == SDLK_ESCAPE)
			 ) {
			SDL_Quit();
			return 0;
		}
		if (event.key.keysym.sym == SDLK_RETURN) {
			for (size_t i = 0; i < countOfApples; i++) {
				SDL_FillRect(screen, &apples[i].pos, SDL_MapRGB(background->format, 100,181,246));
			}
			SDL_FillRect(screen, &pet.pos, SDL_MapRGB(background->format, 100,181,246));
			int step = 0;
			bool isAllCollision = false;
			while (step < (50*30) && !(isAllCollision && pet.isCollision)) {
				isAllCollision = true;
				pet.update();
				SDL_BlitSurface(screen, &pet.pos, tmp, NULL);
				SDL_BlitSurface(sprites, &pet.spritePos, screen, &pet.pos);
				for (size_t i = 0; i < countOfApples; i++) {
					if (apples[i].update(pet.pos, pet.radius)) {
						pet.isCollision = true;
					}
					isAllCollision *= apples[i].isCollided;
					SDL_BlitSurface(screen, &apples[i].pos, applesTmp[i], NULL);
					SDL_BlitSurface(sprites, &apples[i].spritePos, screen, &apples[i].pos);
				}
				step++;
				SDL_Flip(screen);
				SDL_Delay(20);
				SDL_BlitSurface(tmp, NULL, screen, &pet.pos);
				for (size_t i = 0; i < countOfApples; i++) {
					SDL_BlitSurface(applesTmp[i], NULL, screen, &apples[i].pos);
				}
			}
		}
	}

	SDL_Quit();
	return 0;
}