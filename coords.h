#include "dynamiclist.h"
#include "grid.h"

#ifndef COORDS_H
#define COORDS_H

#define IN_LINE 1
#define NO_LINE 0


typedef struct Point {
    int x, y, line_state;  // line_state has 2 possible values
} Point;                   // (1 or IN_LINE: point belongs to a line, 0 or NO_LINE: point does not belong to a line)

typedef struct Line
{
    Point* start_point;
    Point* end_point;
    int length;
} Line;


Point* createPoint(int x, int y, int line_state);

Line* createLine(Point* start_point, Point* end_point);

void drawLine(DynamicList* point_list, DynamicList* line_list, int x1, int y1, int x2, int y2);

void removeLine(DynamicList* point_list, DynamicList* line_list, int index);

void renderAllPoints(Grid* grid, DynamicList* point_list, char point_char);



#endif // !COORDS_H