#include "includes.h"
#include "defines.h"
#include "prototipes.h"

int main()
{
	initscr();
  curs_set(0);

  features();

  point plane[4];
   
  plane[0] = set_point(10, 25, 1);
  plane[1] = set_point(35, 45, 2);
  plane[2] = set_point(60, 25, 3);
  plane[3] = set_point(35, 5, 4);

  set_line(&plane[0], &plane[1]);
  set_line(&plane[1], &plane[2]);
  set_line(&plane[2], &plane[3]);
  set_line(&plane[3], &plane[0]);

  set_line(&plane[0], &plane[2]);
  set_line(&plane[3], &plane[1]);

  render_lines(4, plane);

	refresh();
  getch();
	endwin();

	return 0;
}

void render_lines(int arr_size, point arr[])
{
  for (int current_point_number = 0; current_point_number < arr_size; current_point_number++)
  {
    point current_point = arr[current_point_number];
    
    for (int current_connection_number = 0; current_connection_number < current_point.connections_count; current_connection_number++)
    {
      if ( current_point.number >= arr[current_point.connection[current_connection_number]].number )
      { print_line(current_point, arr[current_connection_number]); }
    }
  }
}

point set_point(int x0, int y0, int number)
{
  point tmp_point;

  tmp_point.number = number;
  tmp_point.x = x0;
  tmp_point.y = y0;

  tmp_point.connections_count = 0;

  for (int tmp_con = 0; tmp_con < MAX_CONNECT; tmp_con++)
  { tmp_point.connection[tmp_con] = 0; }

  return tmp_point;
}

void set_line(point* tmp_p1, point* tmp_p2)
{
  if (tmp_p1->connections_count + 1 >= MAX_CONNECT) { return; }
  else { tmp_p1->connections_count += 1; }

  if (tmp_p2->connections_count + 1 >= MAX_CONNECT) { return; }
  else { tmp_p2->connections_count += 1; }

  tmp_p1->connection[tmp_p1->connections_count - 1] = tmp_p2->number;
  tmp_p2->connection[tmp_p2->connections_count - 1] = tmp_p1->number;
}

void print_line(point tmp_p1, point tmp_p2)
{
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

