#pragma once

#include "orientations.h"

class snake {
	unsigned int top_x, top_y;
	unsigned int bottom_x, bottom_y;
public:
	snake() {
		top_x = 0;
		bottom_x = 0;
		top_y = 0;
		bottom_y = 0;

	}
	void setSnake(int top_x, int bottom_x, int top_y, int bottom_y) {
		this->top_x = top_x;
		this->bottom_x = bottom_x;
		this->top_y = top_y;
		this->bottom_y = bottom_y;
	}
	unsigned int getTopx() {
		return top_x;
	}
	unsigned int getTopy() {
		return top_y;
	}
	unsigned int getBottomx() {
		return bottom_x;
	}
	unsigned int getBottomy() {
		return bottom_y;
	}
};

class ladder {
	unsigned int top_x, top_y;
	unsigned int bottom_x, bottom_y;
public:
	ladder() {
		top_x = 0;
		bottom_x = 0;
		top_y = 0;
		bottom_y = 0;

	}
	void setLadder(unsigned int top_x, unsigned int bottom_x, unsigned int top_y, unsigned int bottom_y) {
		this->top_x = top_x;
		this->bottom_x = bottom_x;
		this->top_y = top_y;
		this->bottom_y = bottom_y;

	}
	int getTopx() {
		return top_x;
	}
	int getTopy() {
		return top_y;
	}
	int getBottomx() {
		return bottom_x;
	}
	int getBottomy() {
		return bottom_y;
	}
};