#include "coords.h"
#include "dynamiclist.h"
#include "grid.h"
#include <stdlib.h>


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

        addItemDynamicList(point_list, start_point);
        line->length++;

        for(x = x1 + 1; x < x2; x++){
            offset += abs(rise) * 2;  // abs(rise/run) * abs(run) * 2
            if (offset >= threshold){
                y += adjust;
                offset -= abs(run) * 2;
            }
            addItemDynamicList(point_list, createPoint(x, y, IN_LINE));
            line->length++;
        }

        addItemDynamicList(point_list, end_point);
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

        addItemDynamicList(point_list, start_point);
        line->length++;

        for(y = y1 + 1; y < y2; y++){
            offset += abs(run) * 2;  // abs(run/rise) * abs(rise) * 2
            if (offset >= threshold){
                x += adjust;
                offset -= abs(rise) * 2;
            }
            addItemDynamicList(point_list, createPoint(x, y, IN_LINE));
            line->length++;
        }

        addItemDynamicList(point_list, end_point);
        line->length++;
    }

    addItemDynamicList(line_list, line);
}


// Removes all the points that belong to the given line
void removeLine(DynamicList* point_list, DynamicList* line_list, int index){
    removeItemsDynamicList(point_list, getIndexDynamicList(point_list, ((Line*)line_list->items[index])->start_point), 
                                                ((Line*)line_list->items[index])->length);
    removeItemsDynamicList(line_list, index, 1);
}


// Adds all the Points in the given DynamicList to the given Grid
void renderAllPoints(Grid* grid, DynamicList* point_list, char point_char){
    int i;
    for (i = 0; i < point_list->size; i++){
        drawPoint(grid, ((Point*)point_list->items[i])->x, ((Point*)point_list->items[i])->y, point_char);
    }
}