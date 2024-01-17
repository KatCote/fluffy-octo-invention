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

  render_connection_lines(5, plane);

  //check_point_info(&plane[0]);

  features();

	refresh();
  getch();
	endwin();

	return 0;
}
