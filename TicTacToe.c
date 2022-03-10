#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


struct player {
    int num;
    char player;
} player;

struct matrix {
    int columns;
    int rows;
    char arr[3][3];
} matrix;

bool checkrules(struct matrix *matrixptr, struct player *currplayer) {
    bool finished = false;
    
    if (matrixptr->arr[0][0] == matrixptr->arr[1][1] && matrixptr->arr[1][1] == matrixptr->arr[2][2]) {
        if (matrixptr->arr[1][1] == 'x' || matrixptr->arr[1][1] == 'o') {
            printf("Player %d wins!\n", currplayer->num);
            finished = true;
        }
    }

    if (matrixptr->arr[0][2] == matrixptr->arr[1][1] && matrixptr->arr[1][1] == matrixptr->arr[2][0]) {
        if (matrixptr->arr[1][1] == 'x' || matrixptr->arr[1][1] == 'o') {
            printf("Player %d wins!\n", currplayer->num);
            finished = true;
        }
    }
    else {
       for (int i = 0; i < matrixptr->rows; i++) {
            if (matrixptr->arr[i][0] == matrixptr->arr[i][1] && matrixptr->arr[i][1] == matrixptr->arr[i][2]) {
                if (matrixptr->arr[i][1] == 'x' || matrixptr->arr[i][1] == 'o') {
                    printf("Player %d wins!\n", currplayer->num);
                    finished = true;
                    break;
                }
            }
        }
        for (int j = 0; j < matrixptr->columns; j++) {
            if (matrixptr->arr[0][j] == matrixptr->arr[1][j] && matrixptr->arr[1][j] == matrixptr->arr[2][j]) {
                if (matrixptr->arr[1][j] == 'x' || matrixptr->arr[1][j] == 'o') {
                    printf("Player %d wins!\n", currplayer->num);
                    finished = true;
                    break;
                }
            }
        }
    }
    return finished;
}

struct player *alternateplayers(struct player *currplayer, struct player *player1, struct player *player2) {
    if (currplayer == player1) {
        currplayer = player2;
    }
    else if (currplayer == player2) {
        currplayer = player1;
    }
    printf("It is now Player %d's turn\n", currplayer->num);
    return currplayer;
}

bool update(struct matrix *matrixptr, struct player *currplayer, struct player *player1, struct player *player2) {
    
    for (int i = 0; i < matrixptr->rows; i++) {
        if (i >= 1) {
            printf("--------------\n");
        }
        for (int j = 0; j < matrixptr->columns; j++) {
            if (j == 2) {
                printf("%c\n", matrixptr->arr[i][j]);       
            }
            else {
                printf("%c  |  ", matrixptr->arr[i][j]);
            }
        }
    }

    if (checkrules(matrixptr, currplayer) == false) {
        printf("Next Player's Turn\n");
        return true;
    }
    else {
        printf("Game Over\n");
        return false;
    }
}

void play(struct matrix *matrixptr, struct player *currplayer, struct player *player1, struct player *player2) {
    
    int row;
    int column;

    if (currplayer->player == 'x') {
        printf("Enter row to place an X\n");
        scanf("%d", &row);
        printf("Enter column to place an X\n");
        scanf("%d", &column);
    }
    if (currplayer->player == 'o') {
        printf("Enter row to place an O\n");
        scanf("%d", &row);
        printf("Enter column to place an O\n");
        scanf("%d", &column);
    }

    if (matrixptr->arr[row - 1][column - 1] != '0') {
        printf("This location already has a value, Try again\n");
        play(matrixptr, currplayer, player1, player2);
    }

    else {
        column = column - 1;
        row = row - 1;

        matrixptr->arr[row][column] = currplayer->player;

        if (update(matrixptr, currplayer, player1, player2) == true) {
            play(matrixptr, alternateplayers(currplayer, player1, player2), player1, player2);
        }
    }
}

void createwindow(struct matrix *matrixptr, struct player *currplayer, struct player *player1, struct player *player2) {

    matrixptr->columns = 3;
    matrixptr->rows = 3;

    player1->num = 1;
    player1->player = 'x';
    
    player2->num = 2;
    player2->player = 'o';

    currplayer = player1;

    printf("Player 1 is x\n");
    printf("Player 2 is o\n");

    for (int i = 0; i < matrixptr->rows; i++) {
        if (i >= 1) {
            printf("--------------\n");
        }
        for (int j = 0; j < matrixptr->columns; j++) {
            matrixptr->arr[i][j] = '0';
            if (j == 2) {
                printf("%c\n", matrixptr->arr[i][j]);       
            }
            else {
                printf("%c  |  ", matrixptr->arr[i][j]);
            }
        }
    }
    printf("It is Player %d's turn\n", currplayer->num);

    play(matrixptr, currplayer, player1, player2);

}

void main() {
    printf("Press Enter to play... \nmight have to press it twice bc idk why");
    if (getchar() == 10) {

        struct matrix matrixarr;
        struct matrix *matrixptr = &matrixarr;
        
        struct player playerone;
        struct player *player1 = &playerone;
        
        struct player playertwo;
        struct player *player2 = &playertwo;
        
        struct player currentplayer;
        struct player *currplayer = &currentplayer;
        createwindow(matrixptr, currplayer, player1, player2);
  
        while (checkrules(matrixptr, currplayer) == false) {
            play(matrixptr, currplayer, player1, player2);
        }
        printf("Press any key to terminate program\n");
        if (getchar() != EOF) {
            exit(0);
        }
    }
    else {
        exit(0);
    }
}