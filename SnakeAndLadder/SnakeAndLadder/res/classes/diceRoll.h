#pragma once

#include "classes/image.h"

class diceRol {
	image img1, img2, img3, img4, img5, img6;
	image s_img1, s_img2, s_img3, s_img4, s_img5, s_img6;
	SDL_Surface* s1, * s2, * s3, * s4, * s5, * s6, * _s1, * _s2, * _s3, * _s4, * _s5, * _s6;
	SDL_Texture* t1, * t2, * t3, * t4, * t5, * t6, * _t1, * _t2, * _t3, * _t4, * _t5, * _t6;
public:
	diceRol(SDL_Renderer* rend) {
		s1 = img1.createSprite("res/images/dice_frames/1.png", 50, 50 , 0, 0);
		s2 = img2.createSprite("res/images/dice_frames/2.png", 50, 50, 0, 0);
		s3 = img3.createSprite("res/images/dice_frames/3.png", 50, 50, 0, 0);
		s4 = img4.createSprite("res/images/dice_frames/4.png", 50, 50, 0, 0);
		s5 = img5.createSprite("res/images/dice_frames/5.png", 50, 50, 0, 0);
		s6 = img6.createSprite("res/images/dice_frames/6.png", 50, 50, 0, 0);
		_s1 = img1.createSprite("res/images/dice_stills/one.png", 50, 50, 0, 0);
		_s2 = img2.createSprite("res/images/dice_stills/two.png", 50, 50, 0, 0);
		_s3 = img3.createSprite("res/images/dice_stills/three.png", 50, 50, 0, 0);
		_s4 = img4.createSprite("res/images/dice_stills/four.png", 50, 50, 0, 0);
		_s5 = img5.createSprite("res/images/dice_stills/five.png", 50, 50, 0, 0);
		_s6 = img6.createSprite("res/images/dice_stills/six.png", 50, 50, 0, 0);
		t1 = SDL_CreateTextureFromSurface(rend, s1);
		t2 = SDL_CreateTextureFromSurface(rend, s2);
		t3 = SDL_CreateTextureFromSurface(rend, s3);
		t4 = SDL_CreateTextureFromSurface(rend, s4);
		t5 = SDL_CreateTextureFromSurface(rend, s5);
		t6 = SDL_CreateTextureFromSurface(rend, s6);
		_t1 = SDL_CreateTextureFromSurface(rend, _s1);
		_t2 = SDL_CreateTextureFromSurface(rend, _s2);
		_t3 = SDL_CreateTextureFromSurface(rend, _s3);
		_t4 = SDL_CreateTextureFromSurface(rend, _s4);
		_t5 = SDL_CreateTextureFromSurface(rend, _s5);
		_t6 = SDL_CreateTextureFromSurface(rend, _s6);
	}

	SDL_Surface* stillS(int n) {
		switch (n) {
		case 1:
			return img1.getSurface();
			break;
		case 2:
			return img2.getSurface();
			break;
		case 3:
			return img3.getSurface();
			break;
		case 4:
			return img4.getSurface();
			break;
		case 5:
			return img5.getSurface();
			break;
		case 6:
			return img6.getSurface();
			break;
		}
	}

	SDL_Texture* still(int n) {
		switch (n) {
		case 1:
			return t1;
			break;
		case 2:
			return t2;
			break;
		case 3:
			return t3;
			break;
		case 4:
			return t4;
			break;
		case 5:
			return t5;
			break;
		case 6:
			return t6;
			break;
		}
	}

	SDL_Texture* stillT(int n) {
		switch (n) {
		case 1:
			return _t1;
			break;
		case 2:
			return _t2;
			break;
		case 3:
			return _t3;
			break;
		case 4:
			return _t4;
			break;
		case 5:
			return _t5;
			break;
		case 6:
			return _t6;
			break;
		}
	}

	~diceRol() {
		SDL_DestroyTexture(t1);
		SDL_DestroyTexture(t2);
		SDL_DestroyTexture(t3);
		SDL_DestroyTexture(t4);
		SDL_DestroyTexture(t5);
		SDL_DestroyTexture(t6);
		SDL_DestroyTexture(_t1);
		SDL_DestroyTexture(_t2);
		SDL_DestroyTexture(_t3);
		SDL_DestroyTexture(_t4);
		SDL_DestroyTexture(_t5);
		SDL_DestroyTexture(_t6);
	}
};