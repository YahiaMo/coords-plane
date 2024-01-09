#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamiclist.h"
#include "grid.h"
#include "coords.h"



// Character used to display a point on the plane
const char point_char = 'x';


// Function Declarations

void doAction(Grid* grid, DynamicList* point_list, DynamicList* line_list, char choice);

void printPoints(DynamicList* point_list);

void printLines(DynamicList* line_list);

void freeMemory(Grid* grid, DynamicList* point_list, DynamicList* line_list);


int main(){

    DynamicList* point_list_ptr = createDynamicList(sizeof(Point*));   
    DynamicList* line_list_ptr = createDynamicList(sizeof(Line*));

    int ask_user = 1; // Toggles the UI
    int resolution_x, resolution_y;
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
            addItemDynamicList(point_list, createPoint(x1, y1, NO_LINE));
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
        renderAllPoints(grid, point_list, point_char);
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
                        removeItemsDynamicList(point_list, temp - 1, 1);
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


// Prints the coordinates of the points in the given list
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


// Frees all dynamically allocated memory
void freeMemory(Grid* grid, DynamicList* point_list, DynamicList* line_list){
    freeGrid(grid);
    freeDynamicList(point_list);
    freeDynamicList(line_list);
}
