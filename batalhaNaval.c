#include <stdio.h>

#define WATER_INDICATOR '.'
#define SHIP_INDICATOR '#'
#define BOARD_TYPE char

int isInvalidCoordinates(const int initialCoordinates[], const int shipLength, char shipName[]) {

    const int x = initialCoordinates[0];
    if (x < 0 || x > 9 || (x + shipLength - 1) > 9) {
        printf("Coordenada x do %s é inválida!\n", shipName);
        return 1;
    }
    const int y = initialCoordinates[1];
    if (y < 0 || y > 9 || (y + shipLength - 1) > 9) {
        printf("Coordenada y do %s é inválida!\n", shipName);
        return 1;
    }

    return 0;
}

int isOverlap(const int boardValue) {
    return boardValue == 3;
}

int placeShip(BOARD_TYPE board[10][10], int initialCoordinates[2], int shipLength, unsigned short isVertical) {
    int i = 0;
    while (i++ < shipLength) {
        if (isOverlap(board[initialCoordinates[0]][initialCoordinates[1]])) {
            printf("Os navios se sobrepuseram! \n");
            return 1;
        };
        board[initialCoordinates[0]][initialCoordinates[1]] = SHIP_INDICATOR;
        if (isVertical) initialCoordinates[1]++;
        else initialCoordinates[0]++;
    };
    return 0;
}

int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // ##### Declaração e inicialização da matriz do tabuleiro
    BOARD_TYPE board[10][10];
    int i = 100;
    while (i--) board[i / 10][i % 10] = WATER_INDICATOR;


    const int vShipLength = 3;
    int initCoordVShip[2] = { 0, 0 };
    const int hShipLength = 2;
    int initCoordHShip[2] = { 4, 7 };


    if (isInvalidCoordinates(initCoordVShip, vShipLength, "Navio vertical")) return 1;
    if (isInvalidCoordinates(initCoordHShip, hShipLength, "Navio horizontal")) return 1;


    // ##### Definindo os navios na matriz do tabuleiro
    const int placeErrorVShip = placeShip(board, initCoordVShip, vShipLength, 1);
    const int placeErrorHShip = placeShip(board, initCoordHShip, hShipLength, 0);

    if (placeErrorVShip || placeErrorHShip) return 1;

    // ##### Exibindo a matriz do tabuleiro
    for (i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", board[j][i]);
        }
        printf("\n");
    }

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}
