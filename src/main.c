#include "includes.h"
#include "defines.h"
#include "prototipes.h"

int main()
{
	initscr();
  curs_set(0);

  // STAR TEST

  point star[5];
  int star_offset_x = 10;
  int star_offset_y = 2;
   
  star[0] = new_point(12 + star_offset_x, 2 + star_offset_y, 0);
  star[1] = new_point(4 + star_offset_x, 12 + star_offset_y, 1);
  star[2] = new_point(20 + star_offset_x, 18 + star_offset_y, 2);
  star[3] = new_point(36 + star_offset_x, 12 + star_offset_y, 3);
  star[4] = new_point(28 + star_offset_x, 2 + star_offset_y, 4);

  add_connection_ptp(&star[0], &star[2]); // 1 - 3
  add_connection_ptp(&star[2], &star[4]); // 3 - 5
  add_connection_ptp(&star[4], &star[1]); // 5 - 2
  add_connection_ptp(&star[1], &star[3]); // 2 - 4
  add_connection_ptp(&star[3], &star[0]); // 4 - 1

  render_connection_lines(5, star, true);

  // PLANE TEST

  point sqaure[4];
  int sqaure_offset_x = 50;
  int sqaure_offset_y = 2;

  sqaure[0] = new_point(sqaure_offset_x, sqaure_offset_y, 0);
  sqaure[1] = new_point(sqaure_offset_x, sqaure_offset_y + 10, 1);
  sqaure[2] = new_point(sqaure_offset_x + 10, sqaure_offset_y + 10, 2);
  sqaure[3] = new_point(sqaure_offset_x + 10, sqaure_offset_y, 3);

  add_connection_ptp(&sqaure[0], &sqaure[1]);
  add_connection_ptp(&sqaure[1], &sqaure[2]);
  add_connection_ptp(&sqaure[2], &sqaure[3]);
  add_connection_ptp(&sqaure[3], &sqaure[0]);

  render_connection_lines(4, sqaure, true);

  // TRIANGLE_PLANE TEST

  plane triangle;

  strcpy(triangle.plane_name, "TEST_TRIANGLE_PLANE");

  triangle.fill_plane = false;

  triangle.origin_x = 0;
  triangle.origin_y = 0;

  point p1 = new_point(10, 10, 0);
  point p2 = new_point(10, 6, 0);
  point p3 = new_point(5, 10, 0);

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
