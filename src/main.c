#include "includes.h"
#include "defines.h"
#include "prototipes.h"

int main()
{
	initscr();

  struct point p1;
  struct point p2;
  float distance;

  p1.x = 5;
  p1.y = 5;
  p1.connect[0] = 1;
  p1.connections_count = 1;

  p2.x = 10;
  p2.y = 10;
  p2.connect[0] = 1;
  p2.connections_count = 2;

  int cur_point_x = p1.x;
  int cur_point_y = p1.y;

  print_line(p1, p2);

	refresh();
  getch();
	endwin();

	return 0;
}

void print_line(struct point tmp_p1, struct point tmp_p2)
{
  int x0 = tmp_p1.x;
  int y0 = tmp_p1.y;

  int x1 = tmp_p2.x;
  int y1 = tmp_p2.y;

  // Delta

  int deltax = abs(x1 - x0);
  int deltay = abs(y1 - y0);

  // Error

  int error = 0;
  int deltaerr = deltay + 1;

  // Calc

  int y = y0;
  int diry = y1 - y0;

  if (diry > 0) diry = 1;
  if (diry < 0) diry = -1;

  for (int tmp_x = x0; tmp_x <= x1; tmp_x++)
  {
    // plot(x, y)
    error = error + deltaerr;
    if (error >= (deltax + 1))
    {
      mvprintw(tmp_x, y, ".");
      y = y + diry;
      error = error - (deltax + 1);
    }
  }

  mvprintw(tmp_p1.x, tmp_p1.y, "*");
  mvprintw(tmp_p2.x, tmp_p2.y, "*");
}

