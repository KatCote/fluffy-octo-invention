#include "includes.h"
#include "defines.h"
#include "prototipes.h"

struct point {
    int x;
    int y;

    int connect[MAX_CONNECT];
    int connections_count;
};

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


  while (cur_point_x != p2.x && cur_point_y != p2.y)
  {
    mvprintw(cur_point_x, cur_point_y, POINT_CHAR);
    cur_point_x++;
    cur_point_y++;
    refresh();
  }

  mvprintw(p1.x, p1.y, "O");
  mvprintw(p2.x, p2.y, "O");

	refresh();
  getch();
	endwin();

	return 0;
}
