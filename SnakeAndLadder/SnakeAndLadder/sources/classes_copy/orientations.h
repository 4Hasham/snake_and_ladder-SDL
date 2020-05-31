#pragma once

struct easy {
	unsigned int snake_tx[3] = { 3, 4, 3 };
	unsigned int snake_ty[3] = { 9, 8, 4 };
	unsigned int snake_bx[3] = { 2, 7, 9 };
	unsigned int snake_by[3] = { 5, 10, 3 };
	unsigned int ladder_tx[5] = { 9, 5, 2, 6, 5 };
	unsigned int ladder_ty[5] = { 10, 9, 10, 7, 4 };
	unsigned int ladder_bx[5] = { 8, 3, 3, 8, 5 };
	unsigned int ladder_by[5] = { 8, 3, 8, 5, 2 };
};

struct medium {
	unsigned int snake_tx[4] = { 7, 4, 10, 10 };
	unsigned int snake_ty[4] = { 9, 6, 6, 9 };
	unsigned int snake_bx[4] = { 6, 7, 7, 8 };
	unsigned int snake_by[4] = { 4, 3, 1, 7 };
	unsigned int ladder_tx[4] = { 2, 3, 9, 9 };
	unsigned int ladder_ty[4] = { 9, 10, 5, 6 };
	unsigned int ladder_bx[4] = { 4, 4, 3, 2 };
	unsigned int ladder_by[4] = { 7, 8, 2, 3 };
};

struct hard {
	unsigned int snake_tx[7] = { 8, 3, 6, 6, 1, 3, 9 };
	unsigned int snake_ty[7] = { 10, 10, 10, 9, 7, 6, 5  };
	unsigned int snake_bx[7] = { 8, 3, 6, 4, 3, 1, 1 };
	unsigned int snake_by[7] = { 8, 8, 8, 3, 3, 4, 3 };
	unsigned int ladder_tx[9] = { 9, 8, 2, 4, 4, 7, 2, 4, 10 };
	unsigned int ladder_ty[9] = { 10, 8, 5, 9, 6, 2, 10, 4, 4 };
	unsigned int ladder_bx[9] = { 10, 10, 1, 8, 5, 4, 1, 10, 2 };
	unsigned int ladder_by[9] = { 8, 6, 3, 3, 4, 1, 8, 3, 2 };
};