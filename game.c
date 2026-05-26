#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8
#define MINES 10



// Tahta Hücre Yapıları

#define UNOPENED '-'
#define MINE '*'
#define FLAG 'P'


// Fonksiyon prototiplerini derleyiciye önceden bildiriyoruz

void printBoard(char board[SIZE][SIZE]);
int isValid(int r, int c);
int countMines(int row, int col, char realBoard[SIZE][SIZE]);
void placeMines(char realBoard[SIZE][SIZE], int startRow, int startCol);
void revealBoard(int r, int c, char realBoard[SIZE][SIZE], char playerBoard[SIZE][SIZE], int *openedCount);
void clearInputBuffer();


void printBoard(char board[SIZE][SIZE]) {

    printf("\n     ");

    for (int i = 0; i < SIZE; i++) printf("%d ", i);

    printf("\n    ");

    for (int i = 0; i < SIZE * 2 + 1; i++) printf("-");

    printf("\n");



    for (int i = 0; i < SIZE; i++) {

        printf("%d |  ", i);

        for (int j = 0; j < SIZE; j++) {

            printf("%c ", board[i][j]);

        }

        printf("\n");

    }

}



int isValid(int r, int c) {

    return (r >= 0 && r < SIZE && c >= 0 && c < SIZE);

}



int countMines(int row, int col, char realBoard[SIZE][SIZE]) {

    int count = 0;

    for (int i = -1; i <= 1; i++) {

        for (int j = -1; j <= 1; j++) {

            if (isValid(row + i, col + j) && realBoard[row + i][col + j] == MINE) {

                count++;

            }

        }

    }

    return count;

}



void placeMines(char realBoard[SIZE][SIZE], int startRow, int startCol) {

    int count = 0;

    while (count < MINES) {

        int r = rand() % SIZE;

        int c = rand() % SIZE;



        int isSafeZone = 0;

        for (int i = -1; i <= 1; i++) {

            for (int j = -1; j <= 1; j++) {

                if (r == startRow + i && c == startCol + j) {

                    isSafeZone = 1;

                }

            }

        }



        if (!isSafeZone && realBoard[r][c] != MINE) {

            realBoard[r][c] = MINE;

            count++;

        }

    }

}



void revealBoard(int r, int c, char realBoard[SIZE][SIZE], char playerBoard[SIZE][SIZE], int *openedCount) {

    if (!isValid(r, c) || playerBoard[r][c] != UNOPENED) return;



    int minesAround = countMines(r, c, realBoard);

    playerBoard[r][c] = minesAround + '0';

    (*openedCount)++;



    if (minesAround == 0) {

        for (int i = -1; i <= 1; i++) {

            for (int j = -1; j <= 1; j++) {

                if (i != 0 || j != 0) {

                    revealBoard(r + i, c + j, realBoard, playerBoard, openedCount);

                }

            }

        }

    }

}



void clearInputBuffer() {

    int c;

    while ((c = getchar()) != '\n' && c != EOF);

}



int main() {

    char realBoard[SIZE][SIZE];
    char playerBoard[SIZE][SIZE];

    int row, col;
    char action;
    int gameOver = 0;
    int firstMove = 1;
    int safeCellsOpened = 0;
    int totalSafeCells = (SIZE * SIZE) - MINES;



    srand(time(NULL));



    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            realBoard[i][j] = '.';

            playerBoard[i][j] = UNOPENED;

        }

    }



    printf("--- MAYİN TARLASİ ---\n");



    while (!gameOver) {

        printBoard(playerBoard);

        printf("\nHamle Secin -> Acmak icin [O], Bayrak icin [F] girin (Orn: O 2 3): ");

       

        if (scanf(" %c %d %d", &action, &row, &col) != 3) {

            printf("\n HATA: Gecersiz format! Lutfen 'O satir sutun' veya 'F satir sutun' yazin.\n");

            clearInputBuffer();

            continue;

        }



        if (action != 'O' && action != 'o' && action != 'F' && action != 'f') {

            printf("\n HATA: Yanlis islem sembolu! Sadece O veya F kullanabilirsiniz.\n");

            continue;

        }



        if (!isValid(row, col)) {

            printf("\n HATA: Girdiginiz koordinatlar sinirlarin disinda (0-%d arasi olmali)!\n", SIZE - 1);

            continue;

        }



        if (action == 'F' || action == 'f') {

            if (playerBoard[row][col] == UNOPENED) {

                playerBoard[row][col] = FLAG;

                printf("\n Bayrak yerlestirildi.\n");

            } else if (playerBoard[row][col] == FLAG) {

                playerBoard[row][col] = UNOPENED;

                printf("\n Bayrak kaldirildi.\n");

            } else {

                printf("\n HATA: Acilmis bir hucreye bayrak koyamazsiniz!\n");

            }

            continue;

        }



        if (playerBoard[row][col] == FLAG) {

            printf("\n HATA: Bu hucrede bayrak var! Önce bayragi kaldirmalisiniz.\n");

            continue;

        }

        if (playerBoard[row][col] != UNOPENED) {

            printf("\n HATA: Bu hucreyi zaten actiniz!\n");

            continue;

        }



        if (firstMove) {

            placeMines(realBoard, row, col);

            firstMove = 0;

        }



        if (realBoard[row][col] == MINE) {

            printf("\n *** GUM! Mayina bastin. Oyun Bitti! ***\n");

            for (int i = 0; i < SIZE; i++) {

                for (int j = 0; j < SIZE; j++) {

                    if (realBoard[i][j] == MINE) playerBoard[i][j] = MINE;

                }

            }

            printBoard(playerBoard);

            gameOver = 1;

        } else {

            revealBoard(row, col, realBoard, playerBoard, &safeCellsOpened);



            if (safeCellsOpened == totalSafeCells) {

                printf("\n+++ TEBRİKLER! Kusursuz bir zafer! +++\n");

                printBoard(realBoard);

                gameOver = 1;

            }

        }

    }



    return 0;

}

