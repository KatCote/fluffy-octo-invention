#ifndef PROTOTIPES_GUARDIAN
#define PROTOTIPES_GUARDIAN

typedef struct {

    int number;

    int x;
    int y;

    int connection[MAX_CONNECT];
    int connections_count;
    
} point;

void features();

// Render

void render_single_line(point* input_p1, point* input_p2);
void render_single_point(point* tmp_p1);
void render_connection_lines(int arr_size, point* tmp_point_arr, bool show_points);
void render_connection_points(int arr_size, point* tmp_point_arr); 

// Point

point new_point(int x0, int y0, int number);

void set_chords_point(point* tmp_point, int x0, int y0);
void del_all_connections_point(point* tmp_point);
void check_point_info(point* tmp_point);
void add_connection_ptp(point* tmp_point_1, point* tmp_point_2);

#endif