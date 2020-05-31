#pragma once

class font {
	SDL_Surface* surf;
	SDL_Rect rec;
	TTF_Font* fon;
public:
	font() {
		surf = NULL;
		fon = NULL;
		rec.x = 0;
		rec.y = 0;
		rec.w = 0;
		rec.h = 0;
	}
	font(const char* ref, int size, const char text[], SDL_Color color, int x = 0, int y = 0, unsigned int w = 100, unsigned int h = 100) {
		fon = TTF_OpenFont(ref, size);
		surf = TTF_RenderText_Solid(fon, text, color);
		rec.x = x;
		rec.y = y;
		rec.w = w;
		rec.h = h;
	}
	void BlitRect() {
		SDL_BlitSurface(surf, NULL, NULL, &rec);
	}
	void setSurfSize(unsigned int w, unsigned int h) {
		surf->w = w;
		surf->h = h;
	}
	SDL_Surface* getSurface() {
		return surf;
	}
	TTF_Font* getFont() {
		return fon;
	}
	SDL_Rect getRect() {
		return rec;
	}
	void createFont(const char ref[], unsigned int size, const char text[], SDL_Color color) {
		fon = TTF_OpenFont(ref, size);
		surf = TTF_RenderText_Solid(fon, text, color);
	}
	~font() {
		SDL_FreeSurface(surf);
		TTF_CloseFont(fon);
	}
};