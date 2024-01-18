#include "includes.h"
#include "defines.h"
#include "prototipes.h"

void push_point(plane* tmp_plane, point* tmp_point, bool reset_chords, bool reset_connections)
{
    tmp_plane->point_array[tmp_plane->points_count] = tmp_point;

    tmp_plane->point_array[tmp_plane->points_count]->number = tmp_plane->points_count;

    tmp_plane->points_count += 1;

    if ( reset_chords == 1 ) { set_chords_point(tmp_point, 0, 0); }
}

void pop_point()
{

}

// void del_point() {} - will be soon
