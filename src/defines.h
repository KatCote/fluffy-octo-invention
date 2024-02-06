#ifndef DEFINES_GUARIAN
#define DEFINES_GUARIAN

#define MAX_CONNECT 16
#define MAX_POINTS 8
#define MAX_PLANES 4
#define MAX_PLANE_NAME 8 // RECOMENDATION, NOT RULE (Just now)

#define POINT_CHAR "X"
#define FILL_CHAR '#'
#define UD_LINE_CHAR "|"
#define LR_LINE_CHAR "="
#define ULDR_LINE_CHAR "\\"
#define URDL_LINE_CHAR "/"

#define BUILD_VER "0.0.0.1 Alpha"

//#define DEV_MODE

#define check_ret(try_func) \
{ \
    int ret; \
    if((ret = try_func)) \
    { return ret; } \
}

#define wait_press_any_key \
    curs_set(0); \
    noecho(); \
    getch(); \
    curs_set(2); \
    echo();

#endif