#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamiclist.h"
#include "grid.h"

#define IN_LINE 1
#define NO_LINE 0

//gcc coordsptr.c -o coordsptr -Wall -Wextra -Wvla

//wt -p "Ubuntu" `; split-pane -p "Windows Powershell" -V `; split-pane -p "Git Bash" -H -s .6`; mf first

// Character used to display a point on the plane
const char point_char = 'x';

typedef struct Point {
    int x, y, line_state;  // line_state has 2 possible values
} Point;                   // (1: point belongs to a line, 0: point does not belong to a line)

typedef struct Line
{
    Point* start_point;
    Point* end_point;
    int length;
} Line;



// Function Declarations

void doAction(Grid* grid, DynamicList* point_list, DynamicList* line_list, char choice);

Point* createPoint(int x, int y, int line_state);

Line* createLine(Point* start_point, Point* end_point);

void drawLine(DynamicList* point_list, DynamicList* line_list, int x1, int y1, int x2, int y2);

void removeLine(DynamicList* point_list, DynamicList* line_list, int index);

void renderAllPoints(Grid* grid, DynamicList* point_list);

void printPoints(DynamicList* point_list);

void printLines(DynamicList* line_list);

void printPointList(DynamicList* point_list, DynamicList* line_list);

void freeMemory(Grid* grid, DynamicList* point_list, DynamicList* line_list);


int main(){

    DynamicList* point_list_ptr = createDynamicList(sizeof(Point*));   
    DynamicList* line_list_ptr = createDynamicList(sizeof(Line*));

    int ask_user = 0;
    int resolution_x = 50, resolution_y = 50;
    char choice;

    if(ask_user){
        system("cls||clear");;
        printf("\nEnter the resolution of the grid:\nX-Resolution: ");
        scanf("%d", &resolution_x);
        printf("Y-Resolution: ");
        scanf("%d", &resolution_y);
        Grid* grid_ptr = createGrid(resolution_x, resolution_y);

        while (1){
            printf("==========================================================================================================================\n");
            printf("What do you want to do?\n(Add point: 'p', Add line: 'l', Remove point/line: 'r', Display grid: 'g', Clear grid: 'c', Quit 'q')\n");
            printf("==========================================================================================================================\n");
            scanf(" %c", &choice);
            printf("\n");
            if (choice != 'q'){
                doAction(grid_ptr, point_list_ptr, line_list_ptr, choice);
            }       
            else{
                break;
            }
        }
        freeMemory(grid_ptr, point_list_ptr, line_list_ptr);
    }


    printf("hi");
    /*
    createGrid(grid_ptr, resolution_x, resolution_y);

    drawGrid(grid_ptr);

    int x, y;
    for(x = -1 * (grid.resolution_x/2); x < (grid.resolution_x/2); x++){
        y = round(20 * sin(0.2 * x));
        drawPoint(grid_ptr, x, y);
    }

    printf("\n\n%d", point_list.items[0]->y);
    */

    return 0;
}



// Does the correct action based on user choice
void doAction(Grid* grid, DynamicList* point_list, DynamicList* line_list, char choice){
    int x1, y1, x2, y2, temp;
    char message[50];
    char subchoice;

    switch (choice){
    case 'p':
        printf("Enter the coords of the point: \n");
        printf("x-coord: ");
        scanf("%d", &x1);
        printf("y-coord: ");
        scanf("%d", &y1);
        if(inBounds(grid, x1, y1)){
            addItem(point_list, createPoint(x1, y1, NO_LINE));
            strcpy(message, "Point added successfully!");
        }
        else{
            strcpy(message, "Error: Point out of bounds!");
        }
        break;
    
    case 'l':
        printf("Enter the coords of the end points of the line: \n");
        printf("x1-coord: ");
        scanf("%d", &x1);
        printf("y1-coord: ");
        scanf("%d", &y1);
        printf("x2-coord: ");
        scanf("%d", &x2);
        printf("y2-coord: ");
        scanf("%d", &y2);
        if(inBounds(grid, x1, y1) && inBounds(grid, x2, y2)){
            drawLine(point_list, line_list, x1, y1, x2, y2);
            strcpy(message, "Line added successfully!");
        }
        else{
            strcpy(message, "Error: Endpoints out of bounds!");
        }
        break;

    case 'g':
        system("cls||clear");
        clearGrid(grid);
        renderAllPoints(grid, point_list);
        drawGrid(grid);
        if (point_list->size > 0){printPoints(point_list);};
        if (line_list->size > 0){printLines(line_list);};
        strcpy(message, "");
        break;
    
    case 'r':
        printf("What do you want to remove? (Point: 'p', Line: 'l'): ");
        scanf(" %c", &subchoice);
        switch(subchoice){
            case 'p':
                if (point_list->size > 0){
                    printPoints(point_list);
                    printf("Enter the number of the point you want to remove: ");
                    scanf("%d", &temp);
                    if (temp <= point_list->size){
                        removeItems(point_list, temp - 1, 1);
                        strcpy(message, "Point removed succesfully!");
                    }
                    else{
                        strcpy(message, "Error: Invalid index!");
                    }
                }
                else{
                    strcpy(message, "Error: No points to remove!");
                }
                break;
            case 'l':
                if (line_list->size > 0){
                printLines(line_list);
                printf("Enter the number of the line you want to remove: ");
                scanf("%d", &temp);
                    if (temp <= line_list->size){
                        removeLine(point_list, line_list, temp - 1);
                        strcpy(message, "Line removed succesfully!");
                    }
                    else{
                        strcpy(message, "Error: Invalid index!");
                    }
                }
                else{
                    strcpy(message, "Error: No Lines to remove!");
                }
                break;
        }
        break;

    case 'c':
        clearDynamicList(point_list);
        clearDynamicList(line_list);
        strcpy(message, "Cleared all points from the grid!");
        break;

    default:
        strcpy(message, "Invalid option.");
        break;
    }
    printf("\n%s\n\n", message);
}


// Creates a new Point structure and returns a pointer to it
Point* createPoint(int x, int y, int line_state){
    Point* point = malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    point->line_state = line_state;
    return point;
}


// Creates a new Point structure and returns a pointer to it
Line* createLine(Point* start_point, Point* end_point){
    Line* line = malloc(sizeof(Line));
    line->start_point = start_point;
    line->end_point = end_point;
    line->length = 0;
    return line;
}


// Bresenham's line algorithm
void drawLine(DynamicList* point_list, DynamicList* line_list, int x1, int y1, int x2, int y2){

    int rise = y2 - y1;
    int run = x2 - x1;
    float m = (float) rise / run;

    int y = y1;
    int x = x1;

    int adjust = (m < 0) ? -1 : 1;
    int offset = 0;
    int threshold;
    int temp;

    Point* start_point = NULL;
    Point* end_point = NULL;
    Line* line = NULL;

    // Case of  rise / run
    if (m <= 1 && m >= -1){ 
        threshold =  abs(run);  // 0.5 * 2 * abs(run)

        if (x1 > x2){
            temp = x1;
            x1 = x2;
            x2 = temp;
            y = y2;
            y2 = y1;
        }

        start_point = createPoint(x1, y, IN_LINE);
        end_point = createPoint(x2, y2, IN_LINE);
        line = createLine(start_point, end_point);

        addItem(point_list, start_point);
        line->length++;

        for(x = x1 + 1; x < x2; x++){
            offset += abs(rise) * 2;  // abs(rise/run) * abs(run) * 2
            if (offset >= threshold){
                y += adjust;
                offset -= abs(run) * 2;
            }
            addItem(point_list, createPoint(x, y, IN_LINE));
            line->length++;
        }

        addItem(point_list, end_point);
        line->length++;
    }

    // Case of  run / rise
    else{
        threshold =  abs(rise);  // 0.5 * 2 * abs(rise)

        if (y1 > y2){
            temp = y1;
            y1 = y2;
            y2 = temp;
            x = x2;
            x2 = x1;
        }

        start_point = createPoint(x, y1, IN_LINE);
        end_point = createPoint(x2, y2, IN_LINE);
        line = createLine(start_point, end_point);

        addItem(point_list, start_point);
        line->length++;

        for(y = y1 + 1; y < y2; y++){
            offset += abs(run) * 2;  // abs(run/rise) * abs(rise) * 2
            if (offset >= threshold){
                x += adjust;
                offset -= abs(rise) * 2;
            }
            addItem(point_list, createPoint(x, y, IN_LINE));
            line->length++;
        }

        addItem(point_list, end_point);
        line->length++;
    }

    addItem(line_list, line);
}


// Removes all the points that belong to the given line
void removeLine(DynamicList* point_list, DynamicList* line_list, int index){
    removeItems(point_list, getIndex(point_list, ((Line*)line_list->items[index])->start_point), 
                                                ((Line*)line_list->items[index])->length);
    removeItems(line_list, index, 1);
}


// Adds all the items in the given DynamicList to the given Grid
void renderAllPoints(Grid* grid, DynamicList* point_list){
    int i;
    for (i = 0; i < point_list->size; i++){
        drawPoint(grid, ((Point*)point_list->items[i])->x, ((Point*)point_list->items[i])->y, point_char);
    }
}


// Prints independent points in the given list
void printPoints(DynamicList* point_list){
    printf("\nPoints:\n");
    int i;
    for (i = 0; i < point_list->size; i++){
        if (((Point*)point_list->items[i])->line_state == NO_LINE){
            printf("%d: (%d, %d)\t", 
            i + 1, 
            ((Point*)point_list->items[i])->x, 
            ((Point*)point_list->items[i])->y);
        }    
    }
    printf("\n");
}


// Prints the start and end of lines in the given list
void printLines(DynamicList* line_list){
    int i = 0;
    printf("\nLines:\n");
    for (i = 0; i < line_list->size; i++){
        printf("%d: (%d, %d) -> (%d, %d) (%d pts)\t",
        i + 1, 
        ((Line*)line_list->items[i])->start_point->x,
        ((Line*)line_list->items[i])->start_point->y,
        ((Line*)line_list->items[i])->end_point->x,
        ((Line*)line_list->items[i])->end_point->y,
        ((Line*)line_list->items[i])->length);
    }
    printf("\n");
}


// Prints out all the points in the given point list
void printPointList(DynamicList* point_list, DynamicList* line_list){
    printPoints(point_list);
    printLines(line_list);
}


// Frees all dynamically allocated memory
void freeMemory(Grid* grid, DynamicList* point_list, DynamicList* line_list){
    freeGrid(grid);
    freeDynamicList(point_list);
    freeDynamicList(line_list);
}