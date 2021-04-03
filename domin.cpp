#include<iostream>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#pragma warning(disable : 4996)
#include <iostream>
using namespace std;


// functions to catch signals
#define clear() printf("\033[H\033[J")

int p[10][10] = { 0 };
int opened[10][10] = { 0 };
int flag[10][10] = { 0 };
int minum=10*10/5;
int maxrow = 10;
int maxcol = 10;
int bomb_flag_number = 0;
int end_of_game = 0;
#define MINE 9
#define EMPTY 0

#define BOMB_FLAG 100
#define NO_FLAG 0
void print_board() {
    int i, j;
  
    printf("\n");

    for (i = 0; i <= maxrow; i++) {
        for (j = 0; j <= maxcol; j++) {
            printf("%d", p[i][j]);
        }
        
       
        printf("\n");
    }
    printf("\n");
}
int mi_count(int row, int col) {
    int i, j;
    int neigbor_minenum = 0;
    for (i = -1; i <=1; i++) {
        for (j = -1; j <=1; j++) {
            if ((row + i )>= 0 &&(row + i) <=maxrow  && (col + j) >= maxcol && (col + j) <=maxcol) {
                if (p[row + i][col + j] == MINE)
                    neigbor_minenum += 1;
            }
        }
    }
    return neigbor_minenum;
}

void gen_mine() {
    int i, j;
   
    int random;
    int row, col;
    int iminum = 0; //number of mines already put
   
    while (iminum < minum) {
        random = rand() % (maxrow * maxcol);
        row = random / maxrow;
        col = random % maxcol;

        int should_add = 1; //should add mine to this position? If number of around mines < 4 then we can add more mines here.
        for (i = -1; i <=1; i++) {
            for (j = -1; j <= 1; j++) {
                if (p[row + i][col + j] != MINE && mi_count(row + i, col + j) > 3) {
                    should_add = 0;
                }
            }
        }
        if (p[row][col] == EMPTY && should_add == 1) {
            p[row][col] = MINE;
            iminum ++;
        };
    }
}

void gen_num() {
    int i, j;
    for (i = 0; i <= maxrow; i++) {
        for (j = 0; j <= maxcol; j++) {
            if (p[i][j] == EMPTY) {
                p[i][j] = mi_count(i, j);
            }
        }
    }
}
int unopened_count() {
    int unopened=0, i, j;
    for (i = 0; i <= maxrow; i++) {
        for (j = 0; j <= maxcol; j++) {
            if (!opened[i][j])
                unopened += 1;
        }
    }
    return unopened;
}
void check_win(int row, int col) { // row, col already opened
    int i, j;
    int won = 0; // =-1: Lose; =1: Won; =0: Default
    if (p[row][col] == MINE) {
        won = -1; // If open a mine -> Lose
    }
    else if (unopened_count() == minum) {
        won = 1; // If unopened positions = number of mines -> Won
    }
    else if (bomb_flag_number == minum) { // Number of Bomb flag = Number of Mines
        won = 1;
        for (i = 0; i <= maxrow; i++) {
            for (j = 0; j <= maxcol; j++) {
                if (flag[i][j] == BOMB_FLAG && p[i][j] != MINE) {
                    won = 0;
                }
            }
        }
    }
   if(won==-1) { //Lose
        
        print_board();
        printf("You Lose! ");
        end_of_game = 1;
        
    }
    else if(won==1) { //Won
       
        print_board();
        printf("You Won!");
        end_of_game = 1;        
    }
   
}

// Bomb Flag for the position you're sure that it has a bomb
void bomb_flag(int row, int col) {
    if (!opened[row][col]) {
        if (flag[row][col] != BOMB_FLAG) {
            flag[row][col] = BOMB_FLAG;
            bomb_flag_number += 1;
        }
        else {
            flag[row][col] = NO_FLAG;
            bomb_flag_number -= 1;
        }
        print_board();
    }
}
void open_empty_pos(int row, int col)
{
    int i, j;
    opened[row][col] = 1;
    if (p[row][col] == EMPTY)
    {
        for (i = -1; i <= 1; i++)
        {
            for (j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    if (row + i >= 0 && row + i <= maxrow && col + j >= 0 && col + j <= maxcol) 
                    {
                        if (!opened[row + i][col + j])
                            open_empty_pos(row + i, col + j);
                    }
                }
            }
        }
    }
}

void open(int row, int col) {
    if (!opened[row][col]) {
        switch (p[row][col]) {
        case 1:
        case 2:
        case 3:
        case 4: opened[row][col] = 1; break;
        case EMPTY: open_empty_pos(row, col); break;
        }
        print_board();
    }

    // Check Win :D
    check_win(row, col);
}

void newgame() {
    int i, j;
    for (i = 0; i <= maxrow; ++i) {
        for (j = 0; j <= maxcol; ++j) {
            p[i][j] = 0;
            opened[i][j] = 0;
            flag[i][j] = 0;
        }
    }

    bomb_flag_number = 0;
    end_of_game = 0;

 

    print_board();
}

int main()
{	
   
    int c = 8;
    printf("%d", sizeof(int));
   
     return 0;
}