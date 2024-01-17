#ifndef PROTOTIPES_GUARDIAN
#define PROTOTIPES_GUARDIAN

typedef struct {

    int number;

    int x;
    int y;

    int connection[MAX_CONNECT];
    int connections_count;
    
} point;

void print_line(point* input_p1, point* input_p2);
void print_points(point tmp_p1, point tmp_p2);

void features();

point new_point(int x0, int y0, int number);
void set_chords_point(point* tmp_point, int x0, int y0);
void del_all_connections_point(point* tmp_point);
void add_connection_ptp(point* tmp_point_1, point* tmp_point_2);
void check_point_info(point* tmp_point);
void render_connections(int arr_size, point tmp_point_arr[]);
int get_connection(point* tmp_point, int connection_number);

#endif