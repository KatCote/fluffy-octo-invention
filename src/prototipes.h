#ifndef PROTOTIPES_GUARDIAN
#define PROTOTIPES_GUARDIAN

typedef struct {

    int number;

    int x;
    int y;

    int connection[MAX_CONNECT];
    int connections_count;
    
} point;

void print_line(point tmp_p1, point tmp_p2);
void print_points(point tmp_p1, point tmp_p2);

void features();

void set_line(point* tmp_p1, point* tmp_p2);
point set_point(int x0, int y0, int number);

void render_lines(int arr_size, point arr[]);

#endif