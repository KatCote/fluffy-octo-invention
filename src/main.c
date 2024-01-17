#include "includes.h"
#include "defines.h"
#include "prototipes.h"

int main()
{
	initscr();
  curs_set(0);

  point plane[5];
  int plane_offset_x = 10;
  int plane_offset_y = 2;
   
  plane[0] = new_point(12 + plane_offset_x, 2 + plane_offset_y, 0);
  plane[1] = new_point(4 + plane_offset_x, 12 + plane_offset_y, 1);
  plane[2] = new_point(20 + plane_offset_x, 18 + plane_offset_y, 2);
  plane[3] = new_point(36 + plane_offset_x, 12 + plane_offset_y, 3);
  plane[4] = new_point(28 + plane_offset_x, 2 + plane_offset_y, 4);

  add_connection_ptp(&plane[0], &plane[2]); // 1 - 3
  add_connection_ptp(&plane[2], &plane[4]); // 3 - 5
  add_connection_ptp(&plane[4], &plane[1]); // 5 - 2
  add_connection_ptp(&plane[1], &plane[3]); // 2 - 4
  add_connection_ptp(&plane[3], &plane[0]); // 4 - 1

  render_connections(5, plane);

  //check_point_info(&plane[0]);

  features();

	refresh();
  getch();
	endwin();

	return 0;
}

void render_connections(int arr_size, point tmp_point_arr[])
{
  for (int first_counter = 0; first_counter < arr_size; first_counter++)
  {
    point tmp_p1 = tmp_point_arr[first_counter];
    for (int second_counter = 0; second_counter < tmp_p1.connections_count; second_counter++)
    {
      point tmp_p2 = tmp_point_arr[tmp_p1.connection[second_counter]];
      print_line(&tmp_p1, &tmp_p2);
    }
  }
}

point new_point(int x0, int y0, int number)
{
  point tmp_point;

  tmp_point.number = number;
  tmp_point.x = x0;
  tmp_point.y = y0;

  tmp_point.connections_count = 0;

  for (int tmp_com = 0; tmp_com < MAX_CONNECT; tmp_com++)
  { tmp_point.connection[tmp_com] = -1; }

  return tmp_point;
}

void set_chords_point(point* tmp_point, int x0, int y0)
{ tmp_point->x = x0; tmp_point->y = y0; }

void del_all_connections_point(point* tmp_point)
{
  tmp_point->connections_count = 0;

  for (int tmp_con = 0; tmp_con < MAX_CONNECT; tmp_con++)
  { tmp_point->connection[tmp_con] = 0; }
}

void add_connection_ptp(point* tmp_point_1, point* tmp_point_2) // Point To Point
{
  if (tmp_point_1->number == tmp_point_2->number) { return; }

  for (int tmp_con = 0; tmp_con < tmp_point_1->connections_count; tmp_con++)
  { if ( tmp_point_1->number == tmp_point_2->connection[tmp_con] ) { return; } }

  tmp_point_1->connection[tmp_point_1->connections_count] = tmp_point_2->number;
  tmp_point_2->connection[tmp_point_2->connections_count] = tmp_point_1->number;
  tmp_point_1->connections_count = tmp_point_1->connections_count + 1;
  tmp_point_2->connections_count = tmp_point_2->connections_count + 1;
}

void check_point_info(point* tmp_point)
{
  mvprintw(5, 5, "X: %d\tY: %d", tmp_point->x, tmp_point->y);
  mvprintw(6, 5, "NUMBER: %d", tmp_point->number);
  mvprintw(7, 5, "TOTAL CONNECTIONS: %d", tmp_point->connections_count);
  for (int tmp_check_counter = 0; tmp_check_counter < tmp_point->connections_count; tmp_check_counter++)
  { mvprintw(8, 5 + tmp_check_counter * 5, "%d[%d]\t", tmp_check_counter, tmp_point->connection[tmp_check_counter]); }
}

int get_connection(point* tmp_point, int connection_number)
{ return tmp_point->connection[connection_number]; }

void print_line(point* input_p1, point* input_p2)
{
  point tmp_p1 = *input_p1;
  point tmp_p2 = *input_p2;

  int x0 = tmp_p1.x; int tmp_x0 = x0;
  int y0 = tmp_p1.y; int tmp_y0 = y0;

  int x1 = tmp_p2.x; int tmp_x1 = x1;
  int y1 = tmp_p2.y; int tmp_y1 = y1;

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

  print_points(tmp_p1, tmp_p2);
}

void print_points(point tmp_p1, point tmp_p2)
{
  #ifdef DEV_MODE
  mvprintw(tmp_p1.y, tmp_p1.x, "(%d)", tmp_p1.number);
  mvprintw(tmp_p2.y, tmp_p2.x, "(%d)", tmp_p2.number);
  #else
  mvprintw(tmp_p1.y, tmp_p1.x, POINT_CHAR);
  mvprintw(tmp_p2.y, tmp_p2.x, POINT_CHAR);
  #endif
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

