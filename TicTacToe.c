#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct matrix {
    int columns;
    int rows;
    int arr[3][3];
} matrix;

bool checkrules(struct matrix *matrixptr) {
    int playernum;

    if (matrixptr->arr[0][0] == matrixptr->arr[1][1] && matrixptr->arr[1][1] == matrixptr->arr[2][2]) {
        playernum = matrixptr->arr[1][1];
        if (playernum == 1 || playernum == 2) {
            printf("Player %d wins!\n", playernum);
            return true;
        }
    }

    if (matrixptr->arr[0][2] == matrixptr->arr[1][1] && matrixptr->arr[1][1] == matrixptr->arr[2][0]) {
        playernum = matrixptr->arr[1][1];
        if (playernum == 1 || playernum == 2) {
            printf("Player %d wins!\n", playernum);
            return true;
        }
    }
    for (int i = 0; i < matrixptr->rows; i++) {
        if (matrixptr->arr[i][0] == matrixptr->arr[i][1] && matrixptr->arr[i][1] == matrixptr->arr[i][2]) {
            playernum = matrixptr->arr[i][1];
            if (playernum == 1 || playernum == 2) {
                printf("Player %d wins!\n", playernum);
                return true;
                break;
            }
        }
    }
    for (int j = 0; j < matrixptr->columns; j++) {
        if (matrixptr->arr[0][j] == matrixptr->arr[1][j] && matrixptr->arr[1][j] == matrixptr->arr[2][j]) {
            playernum = matrixptr->arr[1][j];
            if (playernum == 1 || playernum == 2) {
                printf("Player %d wins!\n", playernum);
                return true;
                break;
            }
        }
    }
}

void update(struct matrix *matrixptr) {
    for (int i = 0; i < matrixptr->rows; i++) {
        if (i >= 1) {
            printf("--------------\n");
        }
        for (int j = 0; j < matrixptr->columns; j++) {
            if (j == 2) {
                printf("%d\n", matrixptr->arr[i][j]);       
            }
            else {
                printf("%d  |  ", matrixptr->arr[i][j]);
            }
        }
    }

    if (checkrules(matrixptr) == false) {
        printf("Next Player's turn\n");
    }
    else {
        printf("Game Over\n");
        printf("Press any key to terminate the program\n");
        if (getchar() != EOF) {
            exit(0);
        }
    }
}

void play(struct matrix *matrixptr) {
    
    int row;
    int column;

    printf("Enter row to place an X or O as a 1 or 2 respectively\n");
    scanf("%d", &row);
    printf("Enter column to place an X or O as a 1 or 2 respectively\n");
    scanf("%d", &column);


    if (matrixptr->arr[row - 1][column - 1] != 0) {
        printf("This location already has a value, Try again\n");
        play(matrixptr);
    }
    else {
        int placement;
        column = column - 1;
        row = row - 1;

        printf("Enter 1 or 2 to place at the given location: \n");
        scanf("%d", &placement);
        
        if (placement == 1 || placement == 2) {
            matrixptr->arr[row][column] = placement;
        }     
        else {
            printf("Invalid Input, Try Again\n");
            play(matrixptr);
        }
        update(matrixptr);   
    }
}

void createwindow(struct matrix *matrixptr) {

    matrixptr->columns = 3;
    matrixptr->rows = 3;

    for (int i = 0; i < matrixptr->rows; i++) {
        if (i >= 1) {
            printf("--------------\n");
        }
        for (int j = 0; j < matrixptr->columns; j++) {
            matrixptr->arr[i][j] = 0;
            if (j == 2) {
                printf("%d\n", matrixptr->arr[i][j]);       
            }
            else {
                printf("%d  |  ", matrixptr->arr[i][j]);
            }
        }
    }
    play(matrixptr);
}

void main() {
    printf("Press Enter to play... \nmight have to press it twice bc idk why");
    if (getchar() == 10) {
        struct matrix matrixarr;
        struct matrix *matrixptr = &matrixarr;
        createwindow(matrixptr);
        while (checkrules(matrixptr) == false) {
            play(matrixptr);
        }
    }
    else {
        exit(0);
    }
}