#pragma once
typedef struct cell {
	int x;
	int y;
	unsigned int status;
} cell;

typedef struct minefield {
	int rows;
	int cols;
	cell* cells;
} minefield;

