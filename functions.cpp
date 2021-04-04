
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

using namespace std;
#define EMPTY 0
#define ISOPEN 128//2^7
#define ISBOOM 64//2^6
#define ISFLAG 32//2^5
   
int get_index(minefield* field, int x, int y) {
	if (x < 0 || x >= field->rows || y < 0 || y >= field->cols) {
		return -1;
	}
	return x * field->cols + y;
}
int test_status(unsigned int value, int c)
{	// 'isopen':1,'isboom'=2,'isflag'=3,'neighboom'=4//
	if (c == 1)
	{
		if (value & ISOPEN != 0)
			return 1;
		else return 0;
	}
	else if (c == 2)
	{
		if (value & ISBOOM != 0)
			return 1;
		else return 0;
	}
	else if (c == 3)
	{
		if (value & ISFLAG != 0)
			return 1;
		else return 0;
	}
	else if (c == 4)
	{// return number of boom of neighbor
		return value >> 3;
	}
	

}

minefield* create_field(int rows, int cols) {
	int i, j;
	srand((unsigned)time(NULL));
	/*bool mark[rows * cols];*/
	minefield* field = (minefield*)malloc(sizeof(minefield));
	field->rows = rows;
	field->cols = cols;
	field->cells = (cell*)malloc(rows * cols * sizeof(cell));
	int iminum = 0;
	int minum = rows * cols / 5;
	/*memset(mark, false, sizeof(mark));*/
	while (iminum < minum) {
		int random = rand() % (rows * cols);
		int row = random / rows;
		int col = random %cols;
		int index = get_index(field, rows, cols);
		field->cells[index].x = row;
		field->cells[index].y = col;
		field->cells[index].status = ISBOOM;
		mark[random] = true;
		iminum++;
	}
}
int check_index(minefield* field, int x, int y) {
	if (x < 0 || x >= field->rows || y < 0 || y >= field->cols) {
		return -1;
	}
	return x * field->cols + y;
}

int mi_count(minefield *field ,int x, int y) {
	int i, j;
	int neigbor_minenum = 0;
	int index = get_index(field, x, y);
	for (i = -1; i < 1; i++) {
		for (j = -1; j < 1; j++) {
			int neig_index = get_index(field,x+ i, y+j);
			if (neig_index != -1 && neig_index != index) 
			{
				if (test_status(field->cells[index].status, 1) == 1) // if there is boom, numberbomm neightbour is increasing
				{
					field->cells[index].status++;
				}
			}
		}
	}
	return field->cells[index].status;
}
// open or flag
int action_cell(minefield* field, int x, int y, char mode) {
	if (mode == 'o' || mode == 'O') {
		return open_cell(field, x, y);
	}
	else if (mode == 'f' || mode == 'F') {
		flag_cell(field, x, y);
	}
	return 0;
}	
int open_cell(minefield* field, int x, int y) 
{
	int index = get_index(field, x, y);

	if (test_status(field->cells[index].status,3)== 1)// check if there is flag, no action
	{
		return 0;
	}
	if (test_status(field->cells[index].status, 2) == 1) {//  if cell is boom, die
		open_empty_pos(field, x, y);
	}
	if (test_status(field->cells[index].status, 4) == 0) {//  if cell is 0, open all zero
		open_empty_pos(field, x, y);
	}
	return test_status(field->cells[index].status,4);
}
void open_empty_pos(minefield* field, int x, int y)
{
	int i, j;
	
	if (p[row][col] == EMPTY)
	{
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				if (i != 0 && j != 0)
				{
					if (check_index(row + i, col + j) == 1)
					{
						if (!opened[row + i][col + j])
							open_empty_pos(row + i, col + j);
					}
				}
			}
		}
	}
}
int flag_cell(minefield* field, int x, int y)
{

}