#ifndef PROTOTIPES_GUARDIAN
#define PROTOTIPES_GUARDIAN

struct point {
    int x;
    int y;

    int connect[MAX_CONNECT];
    int connections_count;
};

void print_line(struct point tmp_p1, struct point tmp_p2);

#endif