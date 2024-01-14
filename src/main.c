#include "includes.h"
#include "defines.h"
#include "prototipes.h"

int main()
{
	initscr();

  features();

  struct point p1;

  p1.number = 1;
  p1.x = 10;
  p1.y = 10;
  p1.connect[0] = 2;
  p1.connect[1] = 4;
  p1.connections_count = 2;

  struct point p2;

  p2.number = 2;
  p2.x = 50;
  p2.y = 20;
  p2.connect[0] = 1;
  p2.connect[1] = 3;
  p2.connections_count = 2;

  struct point p3;

  p3.number = 3;
  p3.x = 80;
  p3.y = 10;
  p3.connect[0] = 2;
  p3.connect[1] = 4;
  p3.connections_count = 2;

  struct point p4;

  p4.number = 4;
  p4.x = 30;
  p4.y = 5;
  p4.connect[0] = 3;
  p4.connect[1] = 1;
  p4.connections_count = 2;

  print_line(p1, p2);
  print_line(p2, p3);
  print_line(p3, p4);
  print_line(p4, p1);

	refresh();
  getch();
	endwin();

	return 0;
}

void print_line(struct point tmp_p1, struct point tmp_p2)
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
      else if (tmp_y0 == tmp_y1)  mvprintw(y0, x0, LR_LINE_CHAR);
    }
    else if (tmp_x1 > tmp_x0)
    {
      if (tmp_y0 > tmp_y1) mvprintw(y0, x0, URDL_LINE_CHAR);
      else if (tmp_y0 < tmp_y1) mvprintw(y0, x0, ULDR_LINE_CHAR);
      else if (tmp_y0 == tmp_y1)  mvprintw(y0, x0, LR_LINE_CHAR);
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

void print_points(struct point tmp_p1, struct point tmp_p2)
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

