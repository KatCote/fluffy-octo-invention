#ifndef PROTOTIPES_GUARDIAN
#define PROTOTIPES_GUARDIAN

typedef struct {

    int number;

    int x;
    int y;

    int connection[MAX_CONNECT];
    int connections_count;
    
} point;

typedef struct {

    point* first_point;
    point* second_point;

} line; // - will be soon

typedef struct {

    char plane_name[MAX_NAME];

    bool fill_plane;

    int origin_x;
    int origin_y;

    // int layers[MAX_LAYERS]; - will be soon

    point* point_array[MAX_POINTS];
    int points_count;

    // line line_array[MAX_LINES]; - will be soon / or line pairs
    // int lines_count;
    
} plane;

void features();

// Render

void render_single_line(point* input_p1, point* input_p2, int offest_x, int offset_y);
void render_single_point(point* tmp_p1);
void render_connection_lines(int arr_size, point* tmp_point_arr, bool show_points);
void render_connection_points(int arr_size, point* tmp_point_arr, int offset_x, int offset_y); 

void render_plane(plane* tmp_plane, bool show_points);

// Point

point new_point(int x0, int y0, int number);

void set_chords_point(point* tmp_point, int x0, int y0);
void del_all_connections_point(point* tmp_point);
void check_point_info(point* tmp_point);
void add_connection_ptp(point* tmp_point_1, point* tmp_point_2);

// Plane

void push_point(plane* tmp_plane, point* tmp_point, bool reset_chords, bool reset_connections);

point* get_point(plane* tmp_plane, int point_num);

// Core

void base_fill(point* tmp_p1, point* tmp_p2, point* tmp_p3);

#endif