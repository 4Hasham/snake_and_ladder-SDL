#pragma once

class image {
	SDL_Surface* surf;
	SDL_Rect rec;
public:
	image() {
		surf = NULL;
		rec.x = 0;
		rec.y = 0;
		rec.w = 0;
		rec.h = 0;
	}
	image(const char ref[], unsigned int w = 100, unsigned int h = 100, int x = 0, int y = 0) {
		rec.w = w;
		rec.h = h;
		rec.x = x;
		rec.y = y;
		surf = IMG_Load(ref);
	}
	void setSurfSize(unsigned int w, unsigned int h) {
		surf->w = w;
		surf->h = h;
	}
	void BlitRect() {
		SDL_BlitSurface(surf, NULL, NULL, &rec);
	}
	SDL_Surface* createSprite(const char *ref, unsigned int w, unsigned int h, int x, int y) {
		rec.w = w;
		rec.h = h;
		rec.x = x;
		rec.y = y;
		surf = IMG_Load(ref);
		return surf;
	}
	SDL_Surface* getSurface() {
		return surf;
	}
	SDL_Rect getRect() {
		return rec;
	}
	~image() {
		SDL_FreeSurface(surf);
	}
};