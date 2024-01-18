#include "includes.h"
#include "defines.h"
#include "prototipes.h"

int main()
{
	initscr();
  curs_set(0);

  // TRIANGLE_PLANE TEST

  plane triangle;

  strcpy(triangle.plane_name, "TEST_TRIANGLE_PLANE");

  triangle.fill_plane = false;

  triangle.origin_x = 0;
  triangle.origin_y = 0;

  point p1 = new_point(35, 5, 0);
  point p2 = new_point(35, 30, 0);
  point p3 = new_point(10, 30, 0);

  push_point(&triangle, &p1, false, false);
  push_point(&triangle, &p2, false, false);
  push_point(&triangle, &p3, false, false);

  add_connection_ptp(triangle.point_array[0], triangle.point_array[1]);
  add_connection_ptp(triangle.point_array[1], triangle.point_array[2]);
  add_connection_ptp(triangle.point_array[2], triangle.point_array[0]);

  render_plane(&triangle, true);

  // ENDLOG

  features();

	refresh();
  getch();
	endwin();

	return 0;
}
