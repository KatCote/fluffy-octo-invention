#include "includes.h"
#include "defines.h"
#include "prototipes.h"

void render_connection_lines(int arr_size, point* tmp_point_arr, bool show_points)
{
  for (int first_counter = 0; first_counter < arr_size; first_counter++)
  {
    point tmp_p1 = tmp_point_arr[first_counter];

    for (int second_counter = 0; second_counter < tmp_p1.connections_count; second_counter++)
    {
      point tmp_p2 = tmp_point_arr[tmp_p1.connection[second_counter]];

      if (tmp_p1.number < tmp_p2.number)
      { render_single_line(&tmp_p1, &tmp_p2, 0, 0); }
    }
  }

  if (show_points == true)
  { render_connection_points(arr_size, tmp_point_arr, 0, 0); }
}

void render_plane(plane* tmp_plane, bool show_points)
{
  for (int first_counter = 0; first_counter < tmp_plane->points_count; first_counter++)
  {
    point* tmp_p1 = tmp_plane->point_array[first_counter];

    for (int second_counter = 0; second_counter < tmp_p1->connections_count; second_counter++)
    {
        point* tmp_p2 = tmp_plane->point_array[tmp_p1->connection[second_counter]];

        if (tmp_p1->number < tmp_p2->number)
        { render_single_line(tmp_p1, tmp_p2, tmp_plane->origin_x, tmp_plane->origin_y); }
    }
  }

  if (show_points == true)
  { 
    for (int counter = 0; counter < tmp_plane->points_count; counter++)
    {
        #ifdef DEV_MODE
        mvprintw(tmp_plane->point_array[counter]->y + tmp_plane->origin_y, tmp_plane->point_array[counter]->x + tmp_plane->origin_x,
        "(%d)",
        tmp_plane->point_array[counter]->number);
        #else
        mvprintw(
            tmp_plane->point_array[counter]->y + tmp_plane->origin_y, tmp_plane->point_array[counter]->x + tmp_plane->origin_x, POINT_CHAR);
        #endif
    }
  }
}

void render_connection_points(int arr_size, point* tmp_point_arr, int offest_x, int offset_y)
{
  for (int counter = 0; counter < arr_size; counter++)
  {
    #ifdef DEV_MODE
    mvprintw(tmp_point_arr[counter].y + offset_y, tmp_point_arr[counter].x + offest_x, "(%d)", tmp_point_arr[counter].number);
     #else
    mvprintw(tmp_point_arr[counter].y + offset_y, tmp_point_arr[counter].x + offest_x, POINT_CHAR);
    #endif
  }
}

void render_single_point(point* tmp_p1)
{
  #ifdef DEV_MODE
  mvprintw(tmp_p1->y, tmp_p1->x, "(%d)", tmp_p1->number);
  #else
  mvprintw(tmp_p1->y, tmp_p1->x, POINT_CHAR);
  #endif
}

void render_single_line(point* input_p1, point* input_p2, int offest_x, int offset_y)
{
  point tmp_p1 = *input_p1;
  point tmp_p2 = *input_p2;

  int x0 = tmp_p1.x + offest_x; int tmp_x0 = x0;
  int y0 = tmp_p1.y + offset_y; int tmp_y0 = y0;

  int x1 = tmp_p2.x + offest_x; int tmp_x1 = x1;
  int y1 = tmp_p2.y + offset_y; int tmp_y1 = y1;

  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;)
  {
    if (tmp_x0 > tmp_x1)
    {
      if (tmp_y0 > tmp_y1) mvprintw(y0, x0, ULDR_LINE_CHAR);
      else if (tmp_y0 < tmp_y1) mvprintw(y0, x0, URDL_LINE_CHAR);
      else if (tmp_y0 == tmp_y1) mvprintw(y0, x0, LR_LINE_CHAR);
    }
    else if (tmp_x1 > tmp_x0)
    {
      if (tmp_y0 > tmp_y1) mvprintw(y0, x0, URDL_LINE_CHAR);
      else if (tmp_y0 < tmp_y1) mvprintw(y0, x0, ULDR_LINE_CHAR);
      else if (tmp_y0 == tmp_y1) mvprintw(y0, x0, LR_LINE_CHAR);
    }
    else if (tmp_x0 == tmp_x1)
    {
      if (tmp_y0 != tmp_y1)  mvprintw(y0, x0, UD_LINE_CHAR);
      if (tmp_y0 == tmp_y1)  break;
    }

    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void features()
{
  short int info_num = 0;

  mvprintw(info_num, 0, "OS: ");

  #ifdef _WIN32
  mvprintw(info_num, 4, "_WIN32"); info_num++;
  #elif __APPLE__
  mvprintw(info_num, 4, "__APPLE__"); info_num++;
  #elif __linux__
  mvprintw(info_num, 4, "__linux__"); info_num++;
  #else
  mvprintw(info_num, 4, "UNSUPPORTED"); info_num++;
  #endif

  mvprintw(info_num, 0, "Build: %s", BUILD_VER); info_num++;
  mvprintw(info_num, 0, "Color support: %s", has_colors() ? "true" : "false"); info_num++;
  
  #ifdef DEV_MODE // Last
  mvprintw(info_num, 0, "DEV_MODE_ENABLED"); info_num++;
  #endif
}