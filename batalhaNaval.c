#include <stdio.h>

#define WATER_INDICATOR '.'
#define SHIP_INDICATOR '#'
#define SKILL_INDICATOR 'O'
#define BOARD_TYPE char

#define SHIP_TYPE_VERTICAL 1
#define SHIP_TYPE_HORIZONTAL 2
#define SHIP_TYPE_DIAGONAL_ASC 3
#define SHIP_TYPE_DIAGONAL_DESC 4
#define SKILL_TYPE 5

int isInvalidCoordinates(const int initialCoordinates[], const int shipLength, int entityType, char shipName[]) {
    const int y = initialCoordinates[1];
    const int x = initialCoordinates[0];

    if (x < 0 || x > 9 || y < 0 || y > 9) {
        printf("Coordenadas iniciais inválidas para %s! \n", shipName);
        return 1;
    }
    if (entityType == SKILL_TYPE) return 0;

    if (entityType == SHIP_TYPE_VERTICAL && (y + shipLength - 1) > 9) {
        printf("Coordenadas do %s são inválidas!\n", shipName);
        return 1;
    }
    if (entityType == SHIP_TYPE_HORIZONTAL && (x + shipLength - 1) > 9) {
        printf("Coordenadas do %s são inválidas!\n", shipName);
        return 1;
    }
    if (entityType == SHIP_TYPE_DIAGONAL_DESC && (x + shipLength - 1) > 9 || (y + shipLength - 1) > 9) {
        printf("Coordenadas do %s são inválidas!\n", shipName);
        return 1;
    }
    if (entityType == SHIP_TYPE_DIAGONAL_ASC && (x - shipLength - 1) < 0 || (y + shipLength - 1) > 9) {
        printf("Coordenadas do %s são inválidas!\n", shipName);
        return 1;
    }
    if (entityType < 1 || entityType > 5) {
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
    const unsigned short shipType,
    char shipName[]
) {
    if (isInvalidCoordinates(initialCoordinates, shipLength, shipType, shipName)) return 1;

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

int placeSkill(
    BOARD_TYPE board[10][10],
    char skill[5][5],
    int skillCenterCoordinates[2],
    const unsigned short skillType,
    char skillName[]
) {
    if (isInvalidCoordinates(skillCenterCoordinates, 0, skillType, skillName)) return 1;

    for (int skillY = 0; skillY < 5; skillY++) {
        for (int skillX = 0; skillX < 5; skillX++) {
            const int x = skillCenterCoordinates[0] - 2 + skillX;
            const int y = skillCenterCoordinates[1] - 2 + skillY;
            if (skill[skillX][skillY] == WATER_INDICATOR || x > 9 || x < 0 || y > 9 || y < 0) continue;

            if (board[x][y] == SHIP_INDICATOR) {
                printf("Navio atingido pela habilidade %s!", skillName);
                return 1;
            }

            board[x][y] = skill[skillX][skillY];
        }
    }

    return 0;
}

void showBoard(BOARD_TYPE board[10][10]) {
    printf("+  x  0  1  2  3  4  5  6  7  8  9\ny\n");
    for (int y = 0; y < 10; y++) {
        printf("%d     ", y);
        for (int x = 0; x < 10; x++) {
            printf("%c  ", board[x][y]);
        }
        printf("\n");
    }
}

void initCone(char cone[5][5], const int rows, const int columns) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (x == 2 && y == 1 || (y == 2 && x > 0 && x < 4) || y == 3) cone[x][y] = SKILL_INDICATOR;
            else cone[x][y] = WATER_INDICATOR;
        };
    }
}

void initCross(char cross[5][5], const int rows, const int columns) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (y == 2 || x == 2) cross[x][y] = SKILL_INDICATOR;
            else cross[x][y] = WATER_INDICATOR;
        };
    }
}

void initOctahedron(char octahedron[5][5], const int rows, const int columns) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (x == 2 && y == 1 || (y == 2 && x > 0 && x < 4) || x == 2 && y == 3) octahedron[x][y] = SKILL_INDICATOR;
            else octahedron[x][y] = WATER_INDICATOR;
        };
    }
}


int main() {
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

    // ##### Declaração e inicialização da matriz do tabuleiro
    BOARD_TYPE board[10][10];
    int i = 100;
    while (i--) board[i / 10][i % 10] = WATER_INDICATOR;


    // ##### Definindo os navios na matriz do tabuleiro
    const int vShipLength = 3;
    int initCoordVShip[2] = {6, 1};
    const int placeErrorVShip = placeShip(board, initCoordVShip, vShipLength, SHIP_TYPE_VERTICAL, "vertical");

    const int hShipLength = 2;
    int initCoordHShip[2] = {1, 8};
    const int placeErrorHShip = placeShip(board, initCoordHShip, hShipLength, SHIP_TYPE_HORIZONTAL, "horizontal");

    const int d1ShipLength = 4;
    int initCoordD1Ship[2] = {6, 6};
    const int placeErrorD1Ship = placeShip(board, initCoordD1Ship, d1ShipLength, SHIP_TYPE_DIAGONAL_ASC, "diagonal 1");

    const int d2ShipLength = 2;
    int initCoordD2Ship[2] = {1, 0};
    const int placeErrorD2Ship = placeShip(board, initCoordD2Ship, d2ShipLength, SHIP_TYPE_DIAGONAL_DESC, "diagonal 2");


    if (placeErrorVShip || placeErrorHShip || placeErrorD1Ship || placeErrorD2Ship) return 1;


    // ##### Declarando e definindo as habilidades
    const unsigned short skillColumns = 5;
    const unsigned short skillRows = 5;


    // cone
    char cone[skillColumns][skillRows];
    initCone(cone, skillRows, skillColumns);

    // cross
    char cross[skillColumns][skillRows];
    initCross(cross, skillRows, skillColumns);

    // octahedron
    char octahedron[skillColumns][skillRows];
    initOctahedron(octahedron, skillRows, skillColumns);


    int crossInitCoordinates[2] = {8, 4};
    if (placeSkill(board, cross, crossInitCoordinates, SKILL_TYPE, "cruz")) return 1;

    int coneInitCoordinates[2] = {2, 4};
    if (placeSkill(board, cone, coneInitCoordinates, SKILL_TYPE, "cone")) return 1;

    int octahedronInitCoordinates[2] = {8, 8};
    if (placeSkill(board, octahedron, octahedronInitCoordinates, SKILL_TYPE, "octaedro")) return 1;


    // ##### Exibindo a matriz do tabuleiro
    showBoard(board);

    return 0;
}
