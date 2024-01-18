#include "includes.h"
#include "defines.h"
#include "prototipes.h"

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
  {
    mvprintw
    ( 8, 5 + tmp_check_counter * 5, "%d[%d]\t", tmp_check_counter, tmp_point->connection[tmp_check_counter] );
  }
}