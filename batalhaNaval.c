#include <stdio.h>

#define WATER_INDICATOR '.'
#define SHIP_INDICATOR '#'
#define BOARD_TYPE char

#define SHIP_TYPE_VERTICAL 1
#define SHIP_TYPE_HORIZONTAL 2
#define SHIP_TYPE_DIAGONAL_ASC 3
#define SHIP_TYPE_DIAGONAL_DESC 4

int isInvalidCoordinates(const int initialCoordinates[], const int shipLength, int shipType, char shipName[]) {
    const int y = initialCoordinates[1];
    const int x = initialCoordinates[0];

    if (x < 0 || x > 9 || y < 0 || y > 9) {
        printf("Coordenadas iniciais inválidas para o navio %s! \n", shipName);
        return 1;
    }
    if (
        shipType == SHIP_TYPE_VERTICAL ||
        shipType == SHIP_TYPE_HORIZONTAL ||
        shipType == SHIP_TYPE_DIAGONAL_DESC
    ) {
        if ((x + shipLength - 1) > 9 || (y + shipLength - 1) > 9) {
            printf("Coordenadas do %s são inválidas!\n", shipName);
            return 1;
        }
    } else if (shipType == SHIP_TYPE_DIAGONAL_ASC) {
        if ((x - (shipLength - 1)) < 0 || (y + shipLength - 1) > 9) {
            printf("Coordenadas do %s são inválidas!\n", shipName);
            return 1;
        }
    } else {
        printf("Invalid ship type \n");
        return 1;
    }

    return 0;
}

int isOverlap(const int boardValue) {
    return boardValue != WATER_INDICATOR;
}

int placeShip(
    BOARD_TYPE board[10][10],
    int initialCoordinates[2],
    const int shipLength,
    const unsigned short shipType
) {
    int i = 0;
    while (i++ < shipLength) {

        if (isOverlap(board[initialCoordinates[0]][initialCoordinates[1]])) {
            printf("Os navios se sobrepuseram! \n");
            return 1;
        };

        board[initialCoordinates[0]][initialCoordinates[1]] = SHIP_INDICATOR;
        switch (shipType) {
            case SHIP_TYPE_VERTICAL:
                initialCoordinates[1]++;
                break;
            case SHIP_TYPE_HORIZONTAL:
                initialCoordinates[0]++;
                break;
            case SHIP_TYPE_DIAGONAL_DESC:
                initialCoordinates[0]++;
                initialCoordinates[1]++;
                break;
            case SHIP_TYPE_DIAGONAL_ASC:
                initialCoordinates[0]--;
                initialCoordinates[1]++;
                break;
            default:
                printf("Erro enquanto estava adicionando o navio no tabuleiro: Tipo do navio inválido.\n");
                return 1;
        }
    };
    return 0;
}

int main() {
    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // ##### Declaração e inicialização da matriz do tabuleiro
    BOARD_TYPE board[10][10];
    int i = 100;
    while (i--) board[i / 10][i % 10] = WATER_INDICATOR;

    const int vShipLength = 3;
    int initCoordVShip[2] = {0, 0};

    const int hShipLength = 2;
    int initCoordHShip[2] = {3, 5};

    const int d1ShipLength = 4;
    int initCoordD1Ship[2] = {3, 2};

    const int d2ShipLength = 2;
    int initCoordD2Ship[2] = {2, 7};


    if (isInvalidCoordinates(initCoordVShip, vShipLength, SHIP_TYPE_VERTICAL, "vertical")) return 1;
    if (isInvalidCoordinates(initCoordHShip, hShipLength, SHIP_TYPE_HORIZONTAL, "horizontal")) return 1;
    if (isInvalidCoordinates(initCoordD1Ship, d1ShipLength, SHIP_TYPE_DIAGONAL_ASC, "diagonal 1")) return 1;
    if (isInvalidCoordinates(initCoordD2Ship, d2ShipLength, SHIP_TYPE_DIAGONAL_DESC, "diagonal 2")) return 1;


    // ##### Definindo os navios na matriz do tabuleiro
    const int placeErrorVShip = placeShip(board, initCoordVShip, vShipLength, SHIP_TYPE_VERTICAL);
    const int placeErrorHShip = placeShip(board, initCoordHShip, hShipLength, SHIP_TYPE_HORIZONTAL);
    const int placeErrorD1Ship = placeShip(board, initCoordD1Ship, d1ShipLength, SHIP_TYPE_DIAGONAL_ASC);
    const int placeErrorD2Ship = placeShip(board, initCoordD2Ship, d2ShipLength, SHIP_TYPE_DIAGONAL_DESC);

    if (placeErrorVShip || placeErrorHShip || placeErrorD1Ship || placeErrorD2Ship) return 1;

    // ##### Exibindo a matriz do tabuleiro
    printf("+ x 0 1 2 3 4 5 6 7 8 9\ny\n");
    for (int y = 0; y < 10; y++) {
        printf("%d   ", y);
        for (int x = 0; x < 10; x++) {
            printf("%c ", board[x][y]);
        }
        printf("\n");
    }

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
