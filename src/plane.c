#include "includes.h"
#include "defines.h"
#include "prototipes.h"
#include "extern.h"

int planes_count = 0;
int planes_active = 0;
int planes_id[MAX_PLANES] = { [0 ... MAX_PLANES-1] = -1 };
int planes_current_free_id = 0;
plane planes_arr[MAX_PLANES];

void push_point(plane* tmp_plane, point* tmp_point, bool reset_chords, bool reset_connections)
{
    tmp_plane->point_array[tmp_plane->points_count] = tmp_point;

    tmp_plane->point_array[tmp_plane->points_count]->number = tmp_plane->points_count;

    tmp_plane->points_count += 1;

    tmp_point->current_array = tmp_plane->plane_number;

    if ( reset_chords == 1 ) { set_chords_point(tmp_point, 0, 0); }
}

void pop_point()
{

}

// void del_point() {} - will be soon

void init_planes(void)
{
    for (int counter = 0; counter < MAX_PLANES; counter++)
    {}
}
