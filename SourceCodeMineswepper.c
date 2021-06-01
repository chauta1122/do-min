/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdlib.h>
#pragma warning(disable : 4996)
#include<stdio.h>
#include<time.h>
#define clear() printf("\033[H\033[J")
#define MINE 64
#define EMPTY 0
#define OFFLAG 223
#define ONOPEN 128
#define MAX 100000

int end_of_game = 0;

#define F_GRAY          "\033[1;30m"
#define B_GRAY          "\033[1;30;47m"
#define BLUE          "\033[0;34m"
#define F_GREEN         "\033[0;32m"
#define C_PINK          "\033[0;35m"
#define B_RED           "\033[0;30;41m"
#define B_YELL         	"\033[7;49;33m"
#define SET           "\033[0m"

/*
++Attendus  du mini projet:
*La grille est de taille variable choisie par l’utilisateur
*2 modes a choisir( normal et special)
a) mode special:Le nombre de bombe est calculé comme un pourcentage de la taille de la grille
b) mode normal: Le nombre de bombe est calculé comme sizerow*sizecol/5;
*encouragement : quand il n ya mois de 3 fois de choisir avant de victoire
*Le temps de jeu est affiché à la fin

++Programme contenue fonction required comme:
*void Init_Grille(void)
*void Aff_Grille(void)
*Demasque_case(int i, int j)( inclusive dans fonction action_cell )
++Description le grille:
case N : n'est pas encore ouvert
cas -F-: pour mettre drapeau
case X :est un bom
case _ : Demasque_case(
*/




//verifier si le case est ouvert ou pas by using bitwise 8 bits b7b6b5b4b3b2b1b0 . Donc, verifier b7 par hex: 0x080
int getIsOpenStatus(unsigned char cell) {
    if ((cell & 0x080) != 0)
        return 1;
    else return 0;

}
//verifier si la case est bom ou pas by using bitwise 8 bits b7b6b5b4b3b2b1b0 . Donc, verifier b6 par hex : 0x040
int getIsBomStatus(unsigned char cell)
{
    if ((cell & 0x040) != 0)
        return 1;
    else return 0;

}
//verifier si la case est flag ou pas by using bitwise 8 bits b7b6b5b4b3b2b1b0 . Donc, verifier b6 par hex : 0x020
int getIsFlagStatus(unsigned char cell)
{
    if ((cell & 0x020) != 0)
        return 1;
    else return 0;

}
//savoir combien le bom autour de la case ou pas by using bitwise 8 bits b7b6b5b4b3b2b1b0 . Donc, verifier b6 par hex :0x0F
int getNeigBomStatus(unsigned char cell)
{
    return cell & 0x0F;
}
// colorer les cases
void print_cell(unsigned char cell)
{
    // si la case est drapeau ,  imprimer lettre -F- colore par gris 
    if (getIsFlagStatus(cell) == 1)
    {

        printf(B_GRAY"-F-" SET);
        return;
    }


    else if (getIsOpenStatus(cell) == 1)
    { // si la case est ouvert et le bom ,  afficher  lettre 0 colore par  rouge
        if (getIsBomStatus(cell) == 1)
        {
            printf(B_RED " X " SET);
            return;
        }
        // si la case est ouvert et il n ya pas de bom autour ,  afficher  lettre _colore par  cydan
        else if (getNeigBomStatus(cell) == 0)
        {
            printf(F_GRAY " _ " SET);
            return;
        }
        // si la case est ouvert et il y a de bom autour ,  afficher  nombre de bom autour
        else if (getNeigBomStatus(cell) != 0)
        {

            printf(C_PINK" %d " SET, getNeigBomStatus(cell));
            return;
        }

        return;
    }
    //si la case est ferme ,afficher  la lettre N colore jaune 
    printf(B_YELL " N " SET);
}
//afficher grille colore 
void Aff_Grille(unsigned char** T, int maxrow, int maxcol)
{
    printf("      ");
    for (int j = 0; j < maxcol; j++)
    {
        if (j < 10)
        {
            printf("%d  ", j);
        }
       
        else if (j >= 10)
        {
            printf("%d ", j);
        }
    }
    printf("\n");

    for (int i = 0; i < maxrow; i++)
    {
        if (i < 10) {
            printf("%d  | ", i);
        }
        else if(i>=10)
        {
            printf("%d | ", i);
        }
        

        for (int j = 0; j < maxcol; j++)
        {
            /* printf("%d", T[i][j]);*/
            print_cell(T[i][j]);
        }
        printf("\n");
    }

}
//compter les boms autour de la casse
void mi_count(unsigned char** T, int row, int col, int maxrow, int maxcol)
{
    int i, j;

    for (i = -1; i <=1; i++)
    {
        for (j = -1; j <=1; j++)
        {//check si la position de la case est dedans le grille ou pas .il fault etre plus 0 et mois que size .
            if (row + i >= 0 && row + i < maxrow && col + j >= 0 && col + j < maxcol == 1 && T[row][col] != 64)
            {
                {// verifier si cell autour est boms si il est boms, le nombre de bom augument 1
                    if (T[row + i][col + j] == 64)

                        T[row][col] += 1;

                }
            }
        }
    }

}
// creer la grille par pointer et allocate les memories
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
//initialiser le grille avec 2 mode(1 pour normal 2 pour special)
void Init_Grille(unsigned char** T, int maxrow, int maxcol,int mode) {
    srand((unsigned)time(NULL));
    int i = 0;
    int j = 0;
    
    int countbom = 0;
    int bonum = 0;
    if (mode == 1)
    {
        bonum = maxrow * maxcol / 5;
        // creer un table pour verifer si random est deja tire ou pas . Si il est deja tire, marquer 1 et sinon marquer 0
        int mark[MAX] = { 0 };
        while (countbom < bonum)
        {
            int random = rand() % (maxrow * maxcol);
            if (mark[random] == 0)
            {
                int row = random / maxrow;
                int col = random % maxcol;

                // verifier si random est valide size de grille ou pas
                if (row >= 0 && row < maxrow && col >= 0 && col < maxcol == 1)
                {
                    // si random deja tire ,marquer 1
                    T[row][col] = 64;
                    mark[random] = 1;
                    countbom++;
                }
            }
        }
    }
    else if (mode == 2)
    {   // probabilite de mode special est decide par le size du grille
        int probab;
        if (maxrow * maxcol < 40)
            probab = 20;
        else if (maxrow * maxcol < 100)
            probab = 25;
        else
        {
            probab = 30;
        }
       
        for (int i = 0; i < maxrow;i++)
        {
            for (int j = 0; j < maxcol; j++)
            {
                int is_mine = (rand() % 100) < probab;
                if(is_mine==1)
                {
                    T[i][j] = T[i][j] | 64;
                    
                }
                
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

    end_of_game = 0;



    Aff_Grille(T, maxrow, maxcol);
}
//utiliser recursive pour la case n’a pas de bombe dans son voisinage
void open_all_zero(unsigned char** T, int x, int y, int maxrow, int maxcol)
{

    int i, j;
    // marquer la case est ouvert
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
                        test = getIsOpenStatus(T[x + i][y + j]);

                        if (test == 0)
                        {  //propage récursivementl’opération de démasquage sur les cases voisines

                            open_all_zero(T, x + i, y + j, maxrow, maxcol);

                        }

                    }
                }
            }
        }
    }

}
// afficher la grille avec tous la case ouvert si le joureur reussi 
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
    Aff_Grille(T, maxrow, maxcol);
}
// afficher tous les boms si le joureur est decu
void end_game_lose(unsigned char** T, int maxrow, int maxcol)
{
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            if (getIsBomStatus(T[i][j]) == 1)
            {

                if (getIsFlagStatus(T[i][j]) == 1)
                {
                    T[i][j] = T[i][j] & OFFLAG;
                }
                
                T[i][j] = T[i][j] | ONOPEN;

            }

        }
    }
    Aff_Grille(T, maxrow, maxcol);
}
// compter le nombre des cases fermets pour decider si joueur gagne ou pas
int count_close_cell(unsigned char** T, int maxrow, int maxcol)
{
    int count = 0;
    
    for (int i = 0; i < maxrow; i++)
    {
        for (int j = 0; j < maxcol; j++)
        {
            
            
            
                if (getIsOpenStatus(T[i][j]) == 0)
                    count++;
            
        }
    }
    return count;
}
// verifier si quand joueur a ouvert, il va gagner ou pas 
void check_win(unsigned char** T, int x, int y, int maxrow, int maxcol)
{
    int bonum = (maxrow * maxcol) / 5;
    
    if (getIsBomStatus(T[x][y]) == 1)
        end_of_game = -1;
    
    else
    {
        for (int i = 0; i < maxrow; i++)
        {
            for (int j = 0; j < maxcol; j++)
            {
                if (getIsOpenStatus(T[i][j]) == 0 && getIsBomStatus(T[i][j]) == 0)
                {
                    end_of_game = 0;
                    
                }
               
            }
        }
        
        if (count_close_cell(T, maxrow, maxcol) == bonum)
        {
            end_of_game = 1;
        }
     

    }
}
//Demasque la case
void Demasque_case(unsigned char** T, int x, int y, int maxrow, int maxcol)
{
    //démasque la case et si la case n’a pas de bombe dans son voisinage
    if (T[x][y] == 0)
    {
        open_all_zero(T, x, y, maxrow, maxcol);
    }
    //marquer la case est deja ouvert
    if (getIsOpenStatus(T[x][y]) == 0)
    {
        T[x][y] = T[x][y] | ONOPEN;

    }
    
    //Termine le jeu sur un échec si la case (i,j) masquait une bombe by check_win fonction
    check_win(T, x, y, maxrow, maxcol);
}
// metter chapeau a la case
void flag_cell(unsigned char** T, int x, int y)
{
    if (getIsOpenStatus(T[x][y]) == 0)
    {
        // metter chapeau a la case by using bitwise
        if (getIsFlagStatus(T[x][y]) == 0)
            T[x][y] = T[x][y] | 32;
        // si la case est deja chapeau, eteindre de chapeau
        else if (getIsFlagStatus(T[x][y]) == 1)
            T[x][y] = T[x][y] & OFFLAG;

    }

}
//interagir avec l’utilisateur comme vu en cours
void action_cell(unsigned char** T, int x, int y, int action, int maxrow, int maxcol)
{
    // si le joueur a ouvert la case , demasque la case
    if (action == 1)
    {
        Demasque_case(T, x, y, maxrow, maxcol);
    }

    // si le jouer a met chapeau
    else if (action == 2)
    {
        flag_cell(T, x, y);
    }

}
//void encouragement(unsigned char** T, int maxrow, int maxcol)
//{
//    int bom_count = 0;
//    for (int i = 0; i < maxrow; i++)
//    {
//        for (int j = 0; j < maxcol; j++)
//        {
//            if (getIsBomStatus(T[i][j]) == 1)
//            {
//                bom_count++;
//            }
//        }
//    }
//    printf("%d", bom_count);
//    int count_unopen = count_close_cell(T,maxrow,maxcol);
//    
//    printf("\n%d", count_unopen);
//    if (count_unopen <bom_count + 3 && count_unopen>bom_count)
//    {
//        printf("\nBon chance !!Vous avez seulement mois de 3 fois de choix avant ton victoire ");
//    }
//
//}
   
int main()
{
    unsigned char** T;
    int maxrow;
    int maxcol;
    clear();
    int p_row, p_col;
    int action;
    int again;
    int mode;
    do
    {
        printf(BLUE  "======= MINESWEEPER=======\n" SET);
        printf(BLUE  "Il Y A DEUX MODES DE GAME :\n" SET);
        printf(BLUE  "1. Normal (le nom de bom est sizerow*sizecol/5) \n" SET);
        printf(BLUE  "2. Special( le nom de bom est probability par size )\n" SET);

        printf("\n\n");
        printf("Entrer nonbre de row mois que 100:");
        scanf("%d", &maxrow);
        printf("Entrer numbre de col mois que 100:");
        scanf("%d", &maxcol);
        printf("Entrer le mode 1.Normal 2.Special:");
        scanf("%d", &mode);
        T = createT(maxrow, maxcol);
        Init_Grille(T, maxrow, maxcol, mode);
        Aff_Grille(T, maxrow, maxcol);

        printf("\n");

        printf("\n");
        clock_t before = clock();
        do {
            printf("Entrer 1 pour ouvrir et 2 pour flag:");
            scanf(" %d", &action);
            do {
                printf("Entrer nombre de position x :");
                scanf("%d", &p_row);
                printf("Entrer nombre de position y :");
                scanf("%d", &p_col);
                if (p_row >= maxrow || p_row < 0 || p_col >= maxcol || p_col < 0)
                {
                    printf("invalide value. x,y  est plus ou egal 0 et mois que size\n");
                }

            } while (p_row >= maxrow || p_row < 0 || p_col >= maxcol || p_col < 0);
            action_cell(T, p_row, p_col, action, maxrow, maxcol);
            printf("\n");
            //for (int i = 0; i < maxrow; i++)
            //{
            //    for (int j = 0; j < maxcol; j++)
            //    {
            //        printf("%d", T[i][j]);
            //        /* print_cell(T[i][j]);*/
            //    }
            //    printf("\n");
            //}
            //printf("\n");

            Aff_Grille(T, maxrow, maxcol);

            /* if (end_of_game != 0) {
                 encouragement(T, maxrow, maxcol);
            }*/



        } while (end_of_game == 0);
        clock_t difference = (clock() - before) / CLOCKS_PER_SEC;
        if (end_of_game == -1)
        {
            printf(" \nVOUS AVEZ PERDU ET VOUS ALLEZ VOIR TOUS LES BOMS\n");
            end_game_lose(T, maxrow, maxcol);

        }
        else {
            end_of_game = 1;
            if (end_of_game == 1)
            {
                printf(BLUE" -------------------FELICITATION------------------\n");
                end_game_win(T, maxrow, maxcol);
                end_of_game = 1;
            }
        }
        printf(BLUE"TEMPS : %d seconds", difference);
        printf(SET);
        printf(" \nVoulez vous jouer game encore 1 fois( 0 pour terminer et 1 pour accepter):");
        scanf("%d", &again);

    } while (again == 1);

    for (int i = 0; i < maxrow; i++)
    {
    
        free(T[i]);
    }
free(T);
	return 0;
}
