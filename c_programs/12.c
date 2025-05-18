#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 10
#define COLS 10

void printGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%c ", grid[i][j] ? 'O' : '.');
        printf("\n");
    }
    printf("\n");
}

int countNeighbors(int grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <=1; i++) {
        for (int j = -1; j <=1; j++) {
            if (i == 0 && j == 0) continue;
            int r = x + i;
            int c = y + j;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS)
                count += grid[r][c];
        }
    }
    return count;
}

void nextGeneration(int grid[ROWS][COLS]) {
    int newGrid[ROWS][COLS] = {0};
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(grid, i, j);
            if (grid[i][j] && (neighbors == 2 || neighbors == 3))
                newGrid[i][j] = 1;
            else if (!grid[i][j] && neighbors == 3)
                newGrid[i][j] = 1;
        }
    }
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = newGrid[i][j];
}

int main() {
    int grid[ROWS][COLS] = {0};
    grid[1][2] = grid[2][3] = grid[3][1] = grid[3][2] = grid[3][3] = 1;

    for (int gen = 0; gen < 10; gen++) {
        printGrid(grid);
        nextGeneration(grid);
        usleep(500000);
    }
    return 0;
}
