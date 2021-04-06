#include <stdlib.h>
#pragma warning(disable : 4996)
#include <iostream>
using namespace std;
#define clear() printf("\033[H\033[J")
#define MINE 64
#define EMPTY 0
#define OFFLAG 223
#define ONOPEN 128
#define MAX 100000
int bomb_flag_number = 0;
int end_of_game = 0;

int getIsOpenStatus(unsigned char cell) {
    if ((cell & 0x080) != 0)
        return 1;
    else return 0;

}
int getIsBomStatus(unsigned char cell)
{
    if ((cell & 0x040) != 0)
        return 1;
    else return 0;

}
int getIsFlagStatus(unsigned char cell)
{
    if ((cell & 0x020) != 0)
        return 1;
    else return 0;

}
int getNeigBomStatus(unsigned char cell)
{
    return cell & 0x0F;
}

void print_board(unsigned char** T, int maxrow, int maxcol)
{
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            printf("%u", T[i][j]);
        }
        printf("\n");
    }

}

void mi_count(unsigned char** T, int row, int col, int maxrow, int maxcol)
{
    int i, j;
   
    for (i = -1; i < 2; i++)
    {
        for (j = -1; j < 2; j++)
        {
            if (row + i >= 0 && row + i <maxrow && col + j >= 0 && col + j < maxcol == 1 && T[row][col] != 64)
            {
                {  
                    if (T[row + i][col + j] == 64)

                        T[row][col] += 1;
                  
                }
            }
        }
    }

}
void  gen_mi_count(unsigned char** T, int row, int col, int maxrow, int maxcol) {
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            mi_count(T, i, j, maxrow, maxcol);
        }


        printf("\n");
    }

}
unsigned char** createT(int r, int c)
{
    unsigned char** ans = (unsigned char**)malloc(r * sizeof(unsigned char*));
    for (int i = 0; i < r; i++)
    {
        ans[i] = (unsigned char*)malloc(c * sizeof(unsigned char));
        for (int j = 0; j < c; j++)
        {
            ans[i][j] = 0;
        }

    }

    return ans;
}
void gen_mine_count(unsigned char** T, int maxrow, int maxcol)
{
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            mi_count(T, i, j, maxrow, maxcol);
        }


        printf("\n");
    }
}
void gen_mine(unsigned char** T, int maxrow, int maxcol) {
    int i, j;
    int iminum = 0;
    int minum = maxrow * maxcol / 5;
    int mark[MAX] = { 0 };
    while (iminum < minum) {
        int random = rand() % (maxrow * maxcol);
        if (mark[random] == 0)
        {
            int row = random / maxrow;
            int col = random % maxcol;

            int should_add = 1;
            if (row >= 0 && row < maxrow && col >= 0 && col < maxcol == 1)
            {
                T[row][col] = 64;
                mark[random] = 1;
                iminum += 1;
            }
            }
    }
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            mi_count(T, i, j, maxrow, maxcol);
        }


        printf("\n");
    }

}
void newgame(unsigned char** T, int maxrow, int maxcol) {
    int i, j;

    for (i = 0; i <= maxrow; ++i) {
        for (j = 0; j <= maxcol; ++j) {
            T[i][j] = 0;

        }
    }

    bomb_flag_number = 0;
    end_of_game = 0;



    print_board(T, maxrow, maxcol);
}
int open_all_zero(unsigned char** T, int x, int y, int maxrow, int maxcol)
{

    int i, j;
    T[x][y] = T[x][y] | ONOPEN;



    if (getNeigBomStatus(T[x][y]) == 0)
    {

        for (i = -1; i < 2; i++)
        {
            for (j = -1; j < 2; j++)
            {

                if (!(i == 0 && j == 0))
                {


                    if (x + i >= 0 && x + i < maxrow && y + j >= 0 && y + j < maxcol == 1)
                    {

                        int test;
                        test = getIsOpenStatus(T[x + i][y + j] && T[x + i][y + j]);

                        if (test == 0)
                        {

                            open_all_zero(T, x + i, y + j, maxrow, maxcol);
                            return T[1][1];
                        }

                    }
                }
            }
        }
    }

}
void end_game_win(unsigned char** T, int maxrow, int maxcol)
{
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            T[i][j] = T[i][j] & OFFLAG;
            T[i][j] = T[i][j] | ONOPEN;

        }
    }
}
void end_game_lose(unsigned char** T, int maxrow, int maxcol)
{
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            if (getIsBomStatus(T[i][j] == 1))
            {
                T[i][j] = T[i][j] & OFFLAG;
                T[i][j] = T[i][j] | ONOPEN;

            }

        }
    }

}
void check_win(unsigned char** T, int x, int y, int maxrow, int maxcol)
{

    int win = 0;
    if (getIsBomStatus(T[x][y]) == 1)
        win = -1;
    if (win == -1)
    {
        printf(" VOUS AVEZ DECU\n");
        end_game_lose(T, maxrow, maxcol);
    }
    else
    {
        for (int i = 0; i < maxrow; i++)
        {
            for (int j = 0; j < maxcol; j++)
            {
                if (getIsOpenStatus(T[x][y]) == 0 && getIsBomStatus(T[x][y]) == 0)
                {
                    win = 0;
                }
            }
        }
        win = 1;


   /*     if (win == 1)
        {
            printf(" FELICITATION\n");
            end_game_win(T, maxrow, maxcol);
        }*/

    }
}
void open_cell(unsigned char** T, int x, int y, int maxrow, int maxcol)
{
   
    if (T[x][y] == 0)
    {
        open_all_zero(T, x, y, maxrow, maxcol);
    }

    if (getIsOpenStatus(T[x][y]) == 0)
    {
        T[x][y] = T[x][y] | ONOPEN;

    }
    print_board(T, maxrow, maxcol);

    check_win(T, x, y, maxrow, maxcol);
}

void flag_cell(unsigned char** T, int x, int y)
{
    if (getIsOpenStatus(T[x][y]) == 0)
    {

        if (getIsFlagStatus(T[x][y]) == 0)
            T[x][y] = T[x][y] | 32;
        else if (getIsFlagStatus(T[x][y]) == 1)
            T[x][y] = T[x][y] & OFFLAG;

    }

}
void action_cell(unsigned char** T, int x, int y, char mode, int maxrow, int maxcol)
{
    
    if (mode == 'o' || mode == 'O')
    {
        open_cell(T, x, y, maxrow, maxcol);
        

    }

    else if (mode == 'f' || mode == 'F')
    {
        flag_cell(T, x, y);
    }

}


int main()
{
    unsigned char** T;
    int maxrow = 4;
    int maxcol = 4;
    clear();
    int p_row, p_col;
    char action;
    char again;

   /* printf("=== Minesweeper ===\n\n");
    printf("enter nonbre de row:");
    scanf("%d", &maxrow);
    printf("enter numbre de col:");
    scanf("%d", &maxcol);*/
    T = createT(maxrow, maxcol);

   
    print_board(T, maxrow, maxcol);
    printf("\n");
    gen_mine(T, maxrow, maxcol);
    print_board(T, maxrow, maxcol);
    printf("\n");
   action_cell(T, 0, 0, 'o', maxrow, maxcol);
   printf("\n");
    print_board(T, maxrow, maxcol);
}

