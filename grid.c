#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

// Creates a new Grid structure and returns a pointer to it
Grid* createGrid(int resolution_x, int resolution_y){

    Grid* grid = malloc(sizeof(Grid));
    grid->arr = malloc(resolution_y * sizeof(char*));
    int i;
    for (i = 0; i < resolution_y; i++){
        grid->arr[i] = malloc(resolution_x * sizeof(char));
    }

    grid -> resolution_x = resolution_x;
    grid -> resolution_y = resolution_y;

    clearGrid(grid);

    return grid;
}


// Converts "real" (visible) X coordinate to a row index in the grid array
int getXCoord(Grid* grid, int real_coord){
    return ((grid->resolution_x/2) + real_coord);
}


// Converts "real" (visible) Y coordinate to a column index in the grid array
int getYCoord(Grid* grid, int real_coord){
    return ((grid->resolution_y/2) - real_coord - 1);
}


// Clears all points from the grid (Fills it with empty cells)
void clearGrid(Grid* grid){
    int y, x;
    for(y = 0; y < grid->resolution_y; y++){
        for(x = 0; x < grid->resolution_x; x++){
            if (y == getYCoord(grid, 0)){          // x-axis
                grid->arr[y][x] = '-';
            }
            else if (x == getXCoord(grid, 0)) {    // y-axis
                grid->arr[y][x] = '|';
            }
            else {
                grid->arr[y][x] = ' ';             // empty space
            }
        }
    }
}


// Prints out the contents of the grid + the axis numbers
void drawGrid(Grid* grid){
    int y, x;
    for(y = 0; y < grid->resolution_y; y++){

        (abs(grid->resolution_y/2 - y - 1) < 10) ?  // Fixes the spaces after the y-axis numbers
            printf("%d  ", abs(grid->resolution_y/2 - y - 1)) : printf("%d ", abs(grid->resolution_y/2 - y - 1));

        for(x = 0; x < grid->resolution_x; x++){
            printf("%c ", grid->arr[y][x]);
        }
        printf("\n");
    }

    // Row of x-axis numbers
    printf("   ");
    for(x = -1 * (grid->resolution_x/2); x < (grid->resolution_x/2); x++){
        if (abs(x) > 9){
            printf("%d ", (abs(x)-(abs(x)%10)) / 10);
        }
        else{
            printf("%d ", abs(x));
        }
    }
    printf("\n   ");
    for(x = -1 * (grid->resolution_x/2); x < (grid->resolution_x/2); x++){
        if (abs(x) > 9){
            printf("%d ", abs(x) % 10);
        }
        else{
            printf("  ");
        }
    }
    printf("\n");
}


// Checks if the given coords are inside the grid
int inBounds(Grid* grid, int x, int y){
    return abs(y) < (grid->resolution_y / 2) && abs(x) < (grid->resolution_x / 2);
}


// Adds a point to the grid if the given coords are inside the grid
void drawPoint(Grid* grid, int x, int y, char draw_char){
    if(inBounds(grid, x, y)){
        grid->arr[getYCoord(grid, y)][getXCoord(grid, x)] = draw_char;
    }
}


// Frees memory of the points array and grid structure
void freeGrid(Grid* grid){
    int i;
    for (i = 0; i < grid->resolution_y; i++){
        free(grid->arr[i]);
    }
    free(grid->arr);
    free(grid);
}
