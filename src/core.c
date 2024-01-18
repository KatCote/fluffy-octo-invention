#include "includes.h"
#include "defines.h"
#include "prototipes.h"

void base_fill(point* tmp_p1, point* tmp_p2, point* tmp_p3)
{
    if
    (
        tmp_p1->x == tmp_p2->x && tmp_p1->y == tmp_p2->y ||
        tmp_p2->x == tmp_p3->x && tmp_p2->y == tmp_p3->y ||
        tmp_p3->x == tmp_p1->x && tmp_p3->y == tmp_p1->y
    )
    { return; }

    int x0, x1, x2, x3;
    int y0, y1, y2, y3;

    int min_x = 1000000, max_x = -1000000;
    int min_y = 1000000, max_y = -1000000;

    x1 = tmp_p1->x; x2 = tmp_p2->x; x3 = tmp_p3->x;
    y1 = tmp_p1->y; y2 = tmp_p2->y; y3 = tmp_p3->y;

    if (x1 > max_x) {max_x = x1;} if (x1 < min_x) {min_x = x1;}
    if (x2 > max_x) {max_x = x2;} if (x2 < min_x) {min_x = x2;}
    if (x3 > max_x) {max_x = x3;} if (x3 < min_x) {min_x = x3;}

    if (y1 > max_y) {max_y = y1;} if (y1 < min_y) {min_y = y1;}
    if (y2 > max_y) {max_y = y2;} if (y2 < min_y) {min_y = y2;}
    if (y3 > max_y) {max_y = y3;} if (y3 < min_y) {min_y = y3;}

    for (int x_counter = min_x; x_counter <= max_x; x_counter++)
    {
       for (int y_counter = min_y; y_counter <= max_y; y_counter++)
       {
        
        x0 = x_counter;
        y0 = y_counter;

        int sign_1 = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
        int sign_2 = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
        int sign_3 = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);

        if
        (
            (sign_1 > 0 && sign_2 > 0 && sign_3 > 0) ||
            (sign_1 < 0 && sign_2 < 0 && sign_3 < 0)
        )
        { mvaddch(y_counter, x_counter, FILL_CHAR); }
       } 
    }
}