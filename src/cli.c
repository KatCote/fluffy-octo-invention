#include "includes.h"
#include "defines.h"
#include "prototipes.h"
#include "cli.h"
#include <sys/ioctl.h>

int init_cli(void)
{
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);

    return 0;
}

int enter_cli(void)
{

    {
        int welcome_x = 1, welcome_y = 1;
        mvprintw(welcome_y + 0, welcome_x, "W e l c o m e   t o");
        mvprintw(welcome_y + 2, welcome_x, " /$$$$$$$$ /$$$$$$  /$$$$$$");
        mvprintw(welcome_y + 3, welcome_x, "| $$_____//$$__  $$|_  $$_/");
        mvprintw(welcome_y + 4, welcome_x, "| $$     | $$  \\ $$  | $$  ");
        mvprintw(welcome_y + 5, welcome_x, "| $$$$$  | $$  | $$  | $$  ");
        mvprintw(welcome_y + 6, welcome_x, "| $$__/  | $$  | $$  | $$  ");
        mvprintw(welcome_y + 7, welcome_x, "| $$     | $$  | $$  | $$  ");
        mvprintw(welcome_y + 8, welcome_x, "| $$     |  $$$$$$/ /$$$$$$");
        mvprintw(welcome_y + 9, welcome_x, "|__/      \\______/ |______/");
    }

    mvprintw(12, 1, "Choose action:");
    mvprintw(14, 3, "New Guest Session");
    mvprintw(15, 3, "Exit");

    short int choose = 0;
    mvaddch(14, 1, '>');

    for(;;)
    {
        char key = getch();
        bool enter_flag = 0;

        #define MIN_CHOOSE 0
        #define MAX_CHOOSE 1

        switch (key)
        {
        case 2: // ARROW DOWN
            if (choose >= MIN_CHOOSE && choose < MAX_CHOOSE) { ++choose; }
            break;

        case 3: // ARROW UP
            if (choose > MIN_CHOOSE && choose <= MAX_CHOOSE) { --choose; }
            break;

        case 10: // ENTER
            enter_flag = 1;
            break;
        
        default:
            break;
        }

        refresh();

        switch (choose)
        {
        case 0: // NEW GUEST SESSION
            mvaddch(14, 1, '>');
            mvaddch(15, 1, ' ');

            if (enter_flag == 1) { return session_cli(); }

            break;

        case 1: // EXIT
            mvaddch(14, 1, ' ');
            mvaddch(15, 1, '>');

            if (enter_flag == 1) { return 0; }

            break;
        
        default:
            break;
        }

        refresh();

        //break;
    }

    return 0;
}

int session_cli(void)
{
    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");

    clear();

    curs_set(2);
    echo();

    for (;;)
    {
        /* Render new Command Line */

        char input_str[32];
        char command_parts[16] = " ";
        char *istr;

        for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
        { mvaddch(size.ws_row - 2, tmp_col, '_'); mvaddch(size.ws_row - 1, tmp_col, ' '); }

        mvprintw(size.ws_row - 1, 1, ">>> ");
        refresh();

        /* Command Parsing */

        getstr(input_str);

        istr = strtok(input_str, command_parts);

        if (istr == NULL) { continue; }
        if (!strcmp(istr, "exit")) { return 0; }

        mvprintw(30, 30, "%s", istr);

        //while (istr != NULL)
        //{ istr = strtok (NULL, command_parts); }

    }

    return 0;
}

int exit_cli(void)
{
    endwin();

    return 0;
}