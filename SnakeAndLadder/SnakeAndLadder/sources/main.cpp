#define VERIFY(x) if(x == NULL) std::cout << "NULL ALERT\n";
#define PEEK(x) { if(x != NULL) std::cout << x; else VERIFY(x); }

#include <iostream>
#include <random>
#include <include/SDL_ttf.h>
#include <include/SDL_image.h>
#include <include/SDL_mixer.h>
#include <classes/player.h>
#include <classes/diceRoll.h>
#include <classes/font.h>

void render_(SDL_Renderer*, SDL_Texture*);
void render_(SDL_Renderer*, player*);
void render_(SDL_Renderer*, SDL_Texture*, SDL_Rect);
void render_(SDL_Renderer*, SDL_Texture*, SDL_Rect, Uint8, Uint8, Uint8, Uint8);
SDL_Rect setRect(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int diceRoll();
void reset();
void restart();

unsigned int playerWon = 0;
unsigned int difficulty = 0;
unsigned int page = 0;
signed int turn = 1;
unsigned int gameOver = 0;
unsigned int setDiff = 0;
unsigned int close = 0;
unsigned int diceR = 0;
unsigned int i = 1;
unsigned int p = 0;
unsigned int lastTime = 0, currentTime;
unsigned int sound = 1;
int mousex, mousey;

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 307200);

	SDL_Window* window = SDL_CreateWindow("Snake and Ladder Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, SDL_WINDOW_SHOWN);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_Texture* texture, * texture1, * texture2, * tf0, * tf1, * tfront, * tdiff, * tsett, * tw, * topt, * topt_, * hover, * dicer, * soundOnT, * soundOffT;
	SDL_Surface* surf0, * surf1, * surf2, * surf3, * surf4, * surfa, * surfs, * surfd, * surf5, * surf6, * surfh, * soundOn, * soundOff;
	Mix_Chunk* slip, * win, * success;
	SDL_Event event;
	snake snakes[8];
	ladder ladders[9];
	easy easy;
	medium medium;
	hard hard;
	SDL_Rect mess, opt, opt_, hoverR, dic, soundRect;
	player pl(render, "res/images/jerrywa.png", 60, 55, 20, 635, 1);
	player pl_(render, "res/images/tomwa.png", 60, 55, 20, 635, -1);
	image img("res/images/background_easy.png", 200, 200, 150, 50);
	image img1("res/images/background_medium.png", 200, 200, 150, 50);
	image img2("res/images/background_hard.png", 200, 200, 150, 50);
	image front("res/images/main_.png", 200, 200, 150, 50);
	image diff("res/images/difficulty_.png", 200, 200, 150, 50);
	image sett("res/images/settings.png", 200, 200, 150, 50);
	image sOn("res/images/sound.png", 200, 200, 150, 50);
	image sOff("res/images/mute.png", 200, 200, 150, 50);
	font fn("res/font/Roboto/Roboto-Medium.ttf", 1000, "Player 1 Won!", { 255, 255, 255 }, 300, 300, 200, 100);
	font fn1("res/font/Roboto/Roboto-Medium.ttf", 1000, "Player 2 Won!", { 255, 255, 255 }, 300, 300, 200, 100);
	font fn2("res/font/Roboto/Roboto-Medium.ttf", 1000, "Main Menu", { 255, 255, 255 }, 300, 300, 200, 200);
	font fn3("res/font/Roboto/Roboto-Medium.ttf", 1000, "Play again!", { 255, 255, 255 }, 300, 300, 200, 200);
	diceRol dicerll(render);
	SDL_Surface* di = dicerll.stillS(1);
	surf0 = fn.getSurface();
	surf1 = fn1.getSurface();
	surf2 = img.getSurface();
	surf3 = img1.getSurface();
	surf4 = img2.getSurface();
	surf5 = fn2.getSurface();
	surf6 = fn3.getSurface();
	surfa = front.getSurface();
	surfs = sett.getSurface();
	surfd = diff.getSurface();
	soundOn = sOn.getSurface();
	soundOff = sOff.getSurface();

	surfh = SDL_CreateRGBSurface(0, 200, 200, 32, NULL, NULL, NULL, NULL);
	tf0 = SDL_CreateTextureFromSurface(render, surf0);
	tf1 = SDL_CreateTextureFromSurface(render, surf1);
	tfront = SDL_CreateTextureFromSurface(render, surfa);
	tdiff = SDL_CreateTextureFromSurface(render, surfd);
	tsett = SDL_CreateTextureFromSurface(render, surfs);
	tw = pl.getTexture();
	texture = SDL_CreateTextureFromSurface(render, surf2);
	texture1 = SDL_CreateTextureFromSurface(render, surf3);
	texture2 = SDL_CreateTextureFromSurface(render, surf4);
	topt = SDL_CreateTextureFromSurface(render, surf5);
	topt_ = SDL_CreateTextureFromSurface(render, surf6);
	hover = SDL_CreateTextureFromSurface(render, surfh);
	dicer = SDL_CreateTextureFromSurface(render, di);
	soundOnT = SDL_CreateTextureFromSurface(render, soundOn);
	soundOffT = SDL_CreateTextureFromSurface(render, soundOff);

	slip = Mix_LoadWAV("res/sounds/slip.wav");
	win = Mix_LoadWAV("res/sounds/win.wav");
	success = Mix_LoadWAV("res/sounds/success.wav");
	mess = setRect(850 + (100 / 2), 450, 150, 70);
	opt = setRect(850, 525, 100, 60);
	soundRect = setRect(550, 300, 100, 100);
	opt_ = setRect(1000, 525, 100, 60);
	hoverR = setRect(0, 0, 0, 0);
	dic = setRect(915, 470, 100, 100);
	SDL_FreeSurface(surfh);

	while (!close) {

		if (!setDiff) {
			switch (difficulty) {
			case 1:
				std::cout << "DIFFICULTY LEVEL LOADED: EASY" << std::endl;
				for (int i = 0; i < 5; i++) {
					if (i < 3)
						snakes[i].setSnake(easy.snake_tx[i], easy.snake_bx[i], easy.snake_ty[i], easy.snake_by[i]);
					ladders[i].setLadder(easy.ladder_tx[i], easy.ladder_bx[i], easy.ladder_ty[i], easy.ladder_by[i]);
				}
				setDiff = 1;
				break;
			case 2:
				std::cout << "DIFFICULTY LEVEL LOADED: MEDIUM" << std::endl;
				for (int i = 0; i < 4; i++) {
					snakes[i].setSnake(medium.snake_tx[i], medium.snake_bx[i], medium.snake_ty[i], medium.snake_by[i]);
					ladders[i].setLadder(medium.ladder_tx[i], medium.ladder_bx[i], medium.ladder_ty[i], medium.ladder_by[i]);
				}
				setDiff = 2;
				break;
			case 3:
				std::cout << "DIFFICULTY LEVEL LOADED: HARD" << std::endl;
				for (int i = 0; i < 9; i++) {
					if (i < 7)
						snakes[i].setSnake(hard.snake_tx[i], hard.snake_bx[i], hard.snake_ty[i], hard.snake_by[i]);
					ladders[i].setLadder(hard.ladder_tx[i], hard.ladder_bx[i], hard.ladder_ty[i], hard.ladder_by[i]);
				}
				setDiff = 3;
				break;
			}
		}

		//sound

		switch (sound) {
		case 1:
			break;
		case 0:
			slip = NULL;
			success = NULL;
			win = NULL;
			break;
		}

		//Event Handling

		SDL_PollEvent(&event);
		SDL_GetMouseState(&mousex, &mousey);

		switch (event.type) {
		case SDL_QUIT:
			close = 1;
			break;
		case SDL_KEYDOWN:
			if (page == 1) {
				if (event.key.keysym.sym == SDLK_UP) {
					diceR = 1;
					p = diceRoll();
					turn = pl_.incr(p, turn);
					if (!pl_.check(snakes, ladders, slip, win, success)) {
						gameOver = 1;
						playerWon = 1;
						turn = 0;
					}
					SDL_Delay(1000);
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					diceR = 1;
					p = diceRoll();
					turn = pl.incr(p, turn);
					if (!pl.check(snakes, ladders, slip, win, success)) {
						gameOver = 1;
						playerWon = 0;
						turn = 0;
					}
					SDL_Delay(1000);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			std::cout << mousex << "\t" << mousey << std::endl;
			if (page == 0) {
				if (mousex > 330 && mousex < 660) {
					if (mousey > 250 && mousey < 350) {
						SDL_Delay(2000);
						page = 2;
					}
					else if (mousey > 430 && mousey < 585) {
						page = 3;
						SDL_Delay(2000);
					}
				}
			}
			else if (page == 1) {
				if (mousey > opt.y && mousey < opt.y + opt.h) {
					if (mousex > opt.x && mousex < opt.x + opt.w) {
						pl.reset(1);
						pl_.reset(-1);
						reset();
					}
					else if (mousex > opt_.x && mousex < opt_.x + opt_.w) {
						pl.reset(1);
						pl_.reset(-1);
						restart();
					}
				}
			}
			else if (page == 2) {
				if (mousex > 340 && mousex < 490) {
					if (mousey > 190 && mousey < 310) {
						difficulty = 3;
						page = 1;
						SDL_Delay(2000);
					}
					else if (mousey > 340 && mousey < 460) {
						difficulty = 2;
						page = 1;
						SDL_Delay(2000);
					}
					else if (mousey > 490 && mousey < 595) {
						difficulty = 1;
						page = 1;
						SDL_Delay(2000);
					}
				}
				else if (mousex > 40 && mousex < 170) {
					if (mousey > 45 && mousey < 110) {
						page = 0;
						SDL_Delay(2000);
					}
				}
			}
			else if (page == 3) {
				if (mousex > soundRect.x && mousex < soundRect.x + soundRect.w) {
					if (mousey > soundRect.y && mousey < soundRect.y + soundRect.h) {
						if (sound == 0)
							sound = 1;
						else if (sound == 1)
							sound = 0;
						SDL_Delay(1000);
						page = 0;
						SDL_Delay(2000);
					}
				}
			}
			break;
		}

		//Pagination
		switch (page) {
		case 0:
			render_(render, tfront);
			break;
		case 1:
			if (difficulty == 1)
				render_(render, texture);
			else if (difficulty == 2)
				render_(render, texture1);
			else if (difficulty == 3)
				render_(render, texture2);
			if (diceR == 1) {
				currentTime = SDL_GetTicks();
				if (currentTime > lastTime + 700) {
					lastTime = currentTime;
					render_(render, dicerll.still(i), dic);
					if (i < 6)
						i++;
					else
						diceR = 0;
				}
			}
			else if (diceR == 0 && gameOver == 0) {
				render_(render, dicerll.stillT(p), dic);
			}
			render_(render, &pl);
			render_(render, &pl_);
			break;
		case 2:
			render_(render, tdiff);
			break;
		case 3:
			render_(render, tsett);
			if (sound == 1)
				render_(render, soundOnT, soundRect);
			else if (sound == 0)
				render_(render, soundOffT, soundRect);
			break;
		}

		//Pop-up
		if (gameOver == 1 && playerWon == 0) {
			render_(render, tf0, mess);
			render_(render, topt, opt);
			render_(render, topt_, opt_);
		}
		else if (gameOver == 1 && playerWon == 1) {
			render_(render, tf1, mess);
			render_(render, topt, opt);
			render_(render, topt_, opt_);
		}
		else if (gameOver == 0) {
			if (page == 1) {
				switch (turn) {
				case 1:
					hoverR = setRect(800, 100, 165, 200);
					break;
				case -1:
					hoverR = setRect(970, 100, 185, 200);
					break;
				}
				render_(render, hover, hoverR, 0x00, 0xFF, 0x00, 32);
			}
		}

		SDL_RenderPresent(render);
	}

	Mix_FreeChunk(success);
	Mix_FreeChunk(win);
	Mix_FreeChunk(slip);
	SDL_DestroyTexture(soundOnT);
	SDL_DestroyTexture(soundOffT);
	SDL_DestroyTexture(tw);
	SDL_DestroyTexture(topt);
	SDL_DestroyTexture(topt_);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(tsett);
	SDL_DestroyTexture(tdiff);
	SDL_DestroyTexture(tfront);
	SDL_DestroyTexture(texture1);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(tf0);
	SDL_DestroyTexture(tf1);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	
	return 0;
}

void render_(SDL_Renderer* rend, player *player) {
	SDL_RenderDrawRect(rend, &player->getRect());
	SDL_RenderCopyEx(rend, player->getTexture(), NULL, &player->getRect(), NULL, NULL, SDL_FLIP_NONE);
}

void render_(SDL_Renderer* rend, SDL_Texture* text) {
	SDL_RenderClear(rend);
	SDL_RenderCopyEx(rend, text, NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
}

void render_(SDL_Renderer* rend, SDL_Texture* text, SDL_Rect rect) {
	SDL_RenderDrawRect(rend, &rect);
	SDL_RenderCopyEx(rend, text, NULL, &rect, NULL, NULL, SDL_FLIP_NONE);
}

void render_(SDL_Renderer* rend, SDL_Texture* text, SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(rend, r, g, b, a);
	SDL_RenderDrawRect(rend, &rect);
	SDL_RenderFillRect(rend, &rect);
	SDL_RenderCopyEx(rend, text, NULL, &rect, NULL, NULL, SDL_FLIP_NONE);
}

SDL_Rect setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	SDL_Rect rec;
	rec.h = h;
	rec.w = w;
	rec.x = x;
	rec.y = y;
	return rec;
}

unsigned int diceRoll() {
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, 6);
	return distr(eng);
}

void reset() {
	gameOver = 0;
	playerWon = 0;
	turn = 1;
	page = 0;
	setDiff = 0;
	difficulty = 0;
}

void restart() {
	gameOver = 0;
	playerWon = 0;
	turn = 1;
}