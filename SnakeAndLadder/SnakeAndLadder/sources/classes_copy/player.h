#pragma once

#include <classes/paraphernalia.h>

class player {
	unsigned int slot_x;
	unsigned int slot_y;
	unsigned int turn;
	unsigned int winner = 0;
	SDL_Rect rect;
	SDL_Texture* t;
public:
	player() {
		rect.x = 0;
		rect.y = 0;
		rect.w = 0;
		rect.h = 0;
		turn = 0;
		t = NULL;
		slot_x = 1;
		slot_y = 1;
	}
	player(SDL_Renderer* rend, const char *ref, unsigned int w, unsigned int h, signed int x, unsigned int y, signed int tn) {
		t = IMG_LoadTexture(rend, ref);
		rect.w = w;
		rect.h = h;
		rect.x = x;
		rect.y = y;
		slot_x = 1;
		slot_y = 1;
		turn = tn;
	}
	SDL_Rect getRect() {
		return rect;
	}
	signed int incr(unsigned int in, signed int t) {
		if (turn == t) {
			if (slot_x + in > 10) {
				slot_y++;
				slot_x = (slot_x + in) - 10;
				rect.y = rect.y - 70;
				if (slot_y % 2 != 0) {
					rect.x = 20;
					rect.x += (60 + 15) * (slot_x - 1);
				}
				else if (slot_y % 2 == 0) {
					rect.x = (9 * (60 + 15)) + 20;
					rect.x -= (60 + 15) * (slot_x - 1);
				}
			}
			else {
				if (slot_y % 2 != 0) {
					slot_x += in;
					rect.x += (60 + 15) * in;
				}
				else if (slot_y % 2 == 0) {
					slot_x += in;
					rect.x -= (60 + 15) * in;
				}
			}
			std::cout << (turn == -1 ? "Tom: " : "Jerry: ") << in << "\nPlayer Slot x: " << slot_x << std::endl << "Player Slot y: " << slot_y << std::endl << std::endl;
			return turn * -1;
		}
		else
			return t;
	}
	SDL_Texture* getTexture() {
		return t;
	}
	int check(snake s[], ladder l[], Mix_Chunk* slip, Mix_Chunk* win, Mix_Chunk* success) {
		if (slot_x == 10 && slot_y == 10 || slot_y > 10) {
			Mix_PlayChannel(-1, win, 0);
			rect.x =  0;
			rect.y = 0;
			winner = 1;
			turn = 0;
			return turn;
		}
		for (unsigned int i = 0; i < 9; i++) {
			if (slot_x == s[i].getTopx() && slot_y == s[i].getTopy()) {
				Mix_PlayChannel(-1, slip, 0);
				if (s[i].getBottomy() % 2 != 0 && slot_y % 2 != 0)
					rect.x = rect.x - ((slot_x - s[i].getBottomx()) * (60 + 15));
				else if (s[i].getBottomy() % 2 != 0 && slot_y % 2 == 0)
					rect.x = rect.x - ((((10 - s[i].getBottomx()) - slot_x) + 1) * (60 + 15));
				else if (s[i].getBottomy() % 2 == 0 && slot_y % 2 != 0)
					rect.x = rect.x - ((((10 - s[i].getBottomx()) - slot_x) - 1) * (60 + 15));
				else if (s[i].getBottomy() % 2 == 0 && slot_y % 2 == 0)
					rect.x = rect.x + ((slot_x - s[i].getBottomx()) * (60 + 15));
				rect.y = rect.y + ((slot_y - s[i].getBottomy()) * 70);
				slot_x = s[i].getBottomx();
				slot_y = s[i].getBottomy();
				break;
			}
			else if (slot_x == l[i].getBottomx() && slot_y == l[i].getBottomy()) {
				Mix_PlayChannel(-1, success, 0);
				if (l[i].getTopy() % 2 != 0 && slot_y % 2 != 0)
					rect.x = rect.x + ((l[i].getTopx() - slot_x) * (60 + 15));
				else if (l[i].getTopy() % 2 != 0 && slot_y % 2 == 0)
					rect.x = rect.x - ((((10 - slot_x) - l[i].getTopx()) + 1) * (60 + 15));
				else if (l[i].getTopy() % 2 == 0 && slot_y % 2 != 0)
					rect.x = rect.x + ((((10 - slot_x) - l[i].getTopx()) + 1) * (60 + 15));
				else if (l[i].getTopy() % 2 == 0 && slot_y % 2 == 0)
					rect.x = rect.x - ((l[i].getTopx() - slot_x) * (60 + 15));
				rect.y = rect.y - ((l[i].getTopy() - slot_y) * 70);
				slot_x = l[i].getTopx();
				slot_y = l[i].getTopy();
				break;
			}
		}
		return 1;
	}
	~player() {
		SDL_DestroyTexture(t);
	}
};