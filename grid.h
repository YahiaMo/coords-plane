#ifndef GRID_H
#define GRID_H

typedef struct Grid {
    char** arr;
    int resolution_x, resolution_y;
} Grid;


Grid* createGrid(int resolution_x, int resolution_y);

int getXCoord(Grid* grid, int real_coord);

int getYCoord(Grid* grid, int real_coord);

void clearGrid(Grid* grid);

void freeGrid(Grid* grid);

void drawGrid(Grid* grid);

int inBounds(Grid* grid, int x, int y);

void drawPoint(Grid* grid, int x, int y, char draw_char);


#endif // !GRID_H