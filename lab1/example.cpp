#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"

const int scrwidth = 1027, scrheight = 768, scrdepth = 32;

void draw_heli(SDL_Surface *surf, int centre_x, int centre_y,int phase_big, int phase_samll) {
	const int lw = 200, lh = 80;
	if (surf) {
		if (surf->w >= centre_x + lw/2 && surf->h >= centre_y + lh/2 && centre_x - lw/2 >= 0 && centre_y - lh/2 >= 0) {
			SDL_Rect dstarea;
			double phase;
			Sint16 x1, y1, x2, y2;
			Uint32 keycolor = SDL_MapRGB(surf->format, 0, 255, 0);
			Uint32 helicolor = SDL_MapRGB(surf->format, 100, 100, 255);
			Uint32 phasecolor = SDL_MapRGB(surf->format, 255, 100, 200);
			int i;
			dstarea.x = centre_x - lw/2;
			dstarea.y = centre_y - lh/2;
			dstarea.w = lw;
			dstarea.h = lh;
			SDL_FillRect(surf, &dstarea, keycolor);
			Draw_FillEllipse(surf, centre_x + 40, centre_y + 10, 60, 30, helicolor);
			Draw_FillEllipse(surf, centre_x + 60, centre_y, 25, 15, keycolor);
			dstarea.x = centre_x + 35;
			dstarea.y = centre_y - 30;
			dstarea.w = 10;
			dstarea.h = 15;
			SDL_FillRect(surf, &dstarea, helicolor);
			dstarea.x = centre_x - 80;
			dstarea.y = centre_y - 20;
			dstarea.w = 120;
			dstarea.h = 10;
			SDL_FillRect(surf, &dstarea, helicolor);
			dstarea.x = centre_x - 80;
			dstarea.y = centre_y - 30;
			dstarea.w = 10;
			dstarea.h = 30;
			SDL_FillRect(surf, &dstarea, helicolor);
			for (i = 0; i < 15; i++) {
				phase = M_PI / 180 * (phase_samll + i) ;
				x1 = floor(centre_x - 75 - (15 - i/2)*cos(phase));
				y1 = floor(centre_y - 25 + (15 - i/2)*sin(phase));
				x2 = floor(centre_x - 75 + (15 - i/2)*cos(phase));
				y2 = floor(centre_y - 25 - (15 - i/2)*sin(phase));
				Draw_Line(surf, x1, y1, x2, y2, phasecolor);
			}
			for (i = 0; i < 100; i++) {
				phase = M_PI / 180 * (phase_big + i) ;
				x1 = centre_x + 40;
				y1 = centre_y - 30;
				x2 = floor(x1 + (60 - i/2)*cos(phase));
				y2 = floor(y1 - (7 - i/2));
				Draw_Line(surf, x1, y1, x2, y2, phasecolor);
				x2 = floor(x1 - (60 - i/2)*cos(phase));
				Draw_Line(surf, x1, y1, x2, y2, phasecolor);
			}
		}
	}
}

void draw_sky(SDL_Surface *surf, int cloud_cnt) {
	int i;
	Sint16 x0, y0;
	Uint16 xr, yr;
	Uint8 cl;
	Draw_FillRect(surf, 0, 0, surf->w, surf->h,
	SDL_MapRGB(surf->format,0,200,255));
	for (i = 0; i < cloud_cnt; i++) {
		xr = floor((rand()*0.05)/RAND_MAX * surf->w);
		yr = floor((rand()*0.05)/RAND_MAX * surf->h);
		x0 = xr + floor((rand()*1.0)/RAND_MAX * (surf->w - 2*xr));
		y0 = yr + floor((rand()*1.0)/RAND_MAX * (surf->h - 2*yr));
		cl = 220 + floor((rand()*1.0)/RAND_MAX * 35);
		Draw_FillEllipse(surf, x0, y0, xr, yr,
		SDL_MapRGB(surf->format, cl, cl, cl));
	}
}

int main ( int argc, char** argv ) {
	SDL_Surface *background, *temp, *sprites;
	int frame_num;
	SDL_Rect frame_src, frame_dst, frame_tmp;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "Unable to init SDL: %s\n", SDL_GetError() );
		return 1;
	}
	SDL_Surface* screen = SDL_SetVideoMode(scrwidth,
	scrheight, scrdepth, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if (!screen) {
		printf("Unable to set 640x480 video: %s\n",
		SDL_GetError());
		return 1;
	}

	background = SDL_CreateRGBSurface(SDL_HWSURFACE |
		SDL_DOUBLEBUF, scrwidth, scrheight, scrdepth,
		screen->format->Rmask, screen->format->Gmask,
		screen->format->Bmask, screen->format->Amask);
	temp = SDL_CreateRGBSurface(SDL_HWSURFACE |
		SDL_DOUBLEBUF, 200, 80, scrdepth,
		screen->format->Rmask, screen->format->Gmask,
		screen->format->Bmask, screen->format->Amask);
	sprites = SDL_CreateRGBSurface(SDL_HWSURFACE |
		SDL_DOUBLEBUF, 200, 80*36, scrdepth,
		screen->format->Rmask, screen->format->Gmask,
		screen->format->Bmask, screen->format->Amask);

	if( !(background && temp && sprites) ) {
		printf("Unable to create temporary surfaces: %s\n",
		SDL_GetError());
		return 1;
	}
	SDL_SetColorKey(sprites, SDL_SRCCOLORKEY, SDL_MapRGB(sprites->format, 0, 255, 0));
	for(frame_num = 0; frame_num < 36; frame_num++)
		draw_heli(sprites, 100, 40+80*frame_num, 10*frame_num, 10*frame_num);

	draw_sky(background, 250);

	SDL_BlitSurface(background, NULL, screen, NULL);
	int step = 0;
	while (step < (50*5)) /* Примерно 1 минута */ {
		frame_tmp.x = 0;
		frame_tmp.y = 0;
		frame_tmp.w = 200;
		frame_tmp.h = 80;
		frame_dst.x = -200 + step % (scrwidth +200);
		frame_dst.y = scrheight/2 - 100;
		frame_dst.w = 200;
		frame_dst.h = 80;
		SDL_BlitSurface(screen, &frame_dst, temp, &frame_tmp);
		frame_src.x = 0;
		frame_src.y = 80*(step % 36);
		frame_src.w = 200;
		frame_src.h = 80;
		SDL_BlitSurface(sprites, &frame_src, screen, &frame_dst);
		step++;
		SDL_Flip(screen);
		SDL_Delay(20); /* 50 кадров/с */
		SDL_BlitSurface(temp, &frame_tmp, screen, &frame_dst);
	}
	SDL_Quit();
	return 0;
}