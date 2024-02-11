#ifndef PROTOTIPES_GUARDIAN
#define PROTOTIPES_GUARDIAN

typedef struct {

    int number;

    int x;
    int y;

    int connection[MAX_CONNECT];
    int connections_count;

    int current_array;
    
} point;

typedef struct {

    char plane_name[MAX_PLANE_NAME];
    int plane_number;

    bool fill_plane;

    int origin_x;
    int origin_y;

    // int layers[MAX_LAYERS]; - will be soon

    point* point_array[MAX_POINTS];
    int points_count;
    
} plane;

// CLI

int init_cli(void);
int enter_cli(void);
int exit_cli(void);

int session_cli(void);

void help(char * command_d, int type_d);
void list(int type_d);
void info(int id, int type_d);
void add_plane(char * name, int x, int y);
int del_plane(int id);
int config_plane(int id);

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