#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"
#define clear() printf("\033[H\033[J")
int main() {
	int maxrow, maxcol, mines;
	int c_row, c_col;
	char c_level;
	int end_game = 0, is_win = 0;
	char again;
	clear();
	printf("=== Minesweeper ===\n");
	printf("please enter row ");
	do
	{
		printf("please enter row \n");
		scanf("%d", &maxrow);
		printf("please enter column\n ");
		scanf("%d", &maxrow);
	} while ((max_col < 1 || max_row < 1);
	clear();)
		return 0;
}