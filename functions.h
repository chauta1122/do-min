#pragma once
int check_index(int row, int col);
void print_board();
void gen_mine();
void gen_num();
void action_cell(int row, int col, char mode);
void open(int row, int col);
int mi_count(int row, int col);
void bomb_flag(int row, int col);
void open_empty_pos(int row, int col);
int unopened_count();
void check_win(int row, int col);
void newgame();
