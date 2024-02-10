#include "includes.h"
#include "defines.h"
#include "prototipes.h"
#include "extern.h"
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
    mvprintw(14, 3, "New Session");
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
    clear();

    curs_set(2);
    echo();

    for (;;)
    {
        /* Set window size */

        struct winsize size;
        if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");

        /* Render new Command Line */

        char input_str[32];
        char command_parts[16] = " ";
        char *istr;

        for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
        { mvaddch(size.ws_row - 2, tmp_col, '-'); mvaddch(size.ws_row - 1, tmp_col, ' '); }

        mvprintw(size.ws_row - 1, 1, ">>> ");
        refresh();

        /* Command Parsing */

        getstr(input_str);

        istr = strtok(input_str, command_parts);

        if (istr == NULL) { continue; }
        else if (!strcmp(istr, "exit")) { return 0; }

        else if (!strcmp(istr, "help"))
        {
            istr = strtok (NULL, command_parts);
            if(istr == NULL) { goto default_help; }

            char * istr_arg = strtok (NULL, command_parts);

            if(!strcmp(istr, "plane")) { help(istr_arg, 1); }
            else if(!strcmp(istr, "system-info")) { help(istr_arg, 2); }
            else if(!strcmp(istr, "dev-mode")) { help(istr_arg, 3); }

            else
            {
                default_help:

                help(NULL, 0);
            }
        }

        else if (!strcmp(istr, "plane"))
        {
            istr = strtok (NULL, command_parts);

            if (istr == NULL)
            { goto default_cli_plane; }

            if (!strcmp(istr, "list"))
            {
                for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
                { mvaddch(size.ws_row - 1, tmp_col, ' '); }

                //mvprintw(size.ws_row - 1, 1, "COUNT: %d\tACTIVE: %d", planes_count, planes_active);

                if (planes_count > 0)
                {
                    for (int p_id = 0; p_id < planes_count; p_id++)
                    {
                        mvprintw(size.ws_row - 1, p_id * (MAX_PLANE_NAME + 20) + 11,
                        "[%d: %s | %d | %d]",
                        planes_id[p_id], planes_arr[p_id].plane_name, planes_arr[p_id].origin_x, planes_arr[p_id].origin_y);
                    }
                    mvprintw(size.ws_row - 1, 1, "C:%d F:%d", planes_count, planes_current_free_id);
                }
                else
                {
                    mvprintw(size.ws_row - 2, 1, "error");
                    mvprintw(size.ws_row - 1, 1, "\tthere is not a single plane. try \"plane add [name]\" or \"help\"");
                }

                wait_press_any_key continue;
            }

            else if (!strcmp(istr, "add")) // TODO
            {
                istr = strtok (NULL, command_parts);
                int arg_x, arg_y;

                char * tmp_arg_1 = strtok (NULL, command_parts);
                if (tmp_arg_1 != NULL) { arg_x = atoi(tmp_arg_1); } else { arg_x = 0; }

                char * tmp_arg_2 = strtok (NULL, command_parts);
                if (tmp_arg_2 != NULL) { arg_y = atoi(tmp_arg_2); } else { arg_y = 0; }

                add_plane(istr, arg_x, arg_y);
            }

            else if (!strcmp(istr, "delete"))
            {
                goto default_cli_plane;
            }

            else if (!strcmp(istr, "select"))
            {
                goto default_cli_plane;
            }

            else
            {
                default_cli_plane:
                
                help(NULL, 1);
            }
        }

        else if (!strcmp(istr, "system-info"))
        {
            istr = strtok (NULL, command_parts);
            if (istr == NULL)
            { goto default_cli_system_info; }

            else if (!strcmp(istr, "enable"))
            { goto default_cli_system_info; }

            else if (!strcmp(istr, "disable"))
            { goto default_cli_system_info; }

            else if (!strcmp(istr, "export"))
            { goto default_cli_system_info; }

            else
            {
                default_cli_system_info:

                help(NULL, 2);
            }
        }

        else if (!strcmp(istr, "dev-mode"))
        {
            istr = strtok (NULL, command_parts);
            if (istr == NULL)
            {
                for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
                { mvaddch(size.ws_row - 1, tmp_col, ' '); }
                mvprintw(size.ws_row - 1, 1, "TDB");
                wait_press_any_key continue;
            }
            
            else if (!strcmp(istr, "enable"))
            {}

            else if (!strcmp(istr, "disable"))
            {}

            else
            {}
        }
    }

    return 0;
}

void help(char * command_d, int type_d) // _d only for developers
{
    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
    printf("TIOCGWINSZ error");

    for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
    { mvaddch(size.ws_row - 1, tmp_col, ' '); }

    switch (type_d)
    {
        case 0: // DEFAULT HELP
            mvprintw(size.ws_row - 1, 1, "TBD");

            break;

        case 1: // PLANE
            
            if (command_d == NULL)
            { goto help_plane_default; }

            else if (!strcmp(command_d, "add"))
            { goto help_plane_default; }

            else if (!strcmp(command_d, "delete"))
            { goto help_plane_default; }

            else if (!strcmp(command_d, "select"))
            { goto help_plane_default; }

            else if (!strcmp(command_d, "config"))
            { goto help_plane_default; }

            else if (!strcmp(command_d, "list"))
            { goto help_plane_default; }

            else if (!strcmp(command_d, "info"))
            { goto help_plane_default; }

            else
            {
                help_plane_default:

                mvprintw(size.ws_row - 2, 1, "plane");
                mvprintw(size.ws_row - 1, 1, "\tadd [NAME] [X] [Y]\t| delete [ID]\t| select [ID]\t| config [ID]\t| info [ID]\t| list");
            }

            break;

        case 2: // SYSTEM-INFO

            if (command_d == NULL)
            { goto help_system_info_default; }

            else if (!strcmp(command_d, "enable"))
            { goto help_system_info_default; }

            else if (!strcmp(command_d, "disable"))
            { goto help_system_info_default; }

            else if (!strcmp(command_d, "export"))
            { goto help_system_info_default; }

            else
            {
                help_system_info_default:

                mvprintw(size.ws_row - 2, 1, "system-info");
                mvprintw(size.ws_row - 1, 1, "\tTBD");
            }

            break;

        case 3: // DEV-MODE

            if (command_d == NULL)
            { goto help_dev_mode_default; }

            else if (!strcmp(command_d, "enable"))
            { goto help_dev_mode_default; }

            else if (!strcmp(command_d, "disable"))
            { goto help_dev_mode_default; }

            else
            {
                help_dev_mode_default:

                mvprintw(size.ws_row - 2, 1, "dev-mode");
                mvprintw(size.ws_row - 1, 1, "\tTBD");
            }

            break;
        
        default:
            break;
    }

    wait_press_any_key return;
}

void list(int type_d) // _d only for developers
{
    /*
    TYPE:
    0 - planes
    1 - points
    */
}

void info(int id, int type_d) // _d only for developers
{
    /*
    TYPE:
    0 - planes
    1 - points
    */
}

void add_plane(char * name, int x, int y)
{
    
    /* Planes Array */

    planes_count += 1;

    /* Plane ID */

    int tmp_id = planes_current_free_id;

    planes_id[tmp_id] = tmp_id;
    planes_arr[tmp_id].plane_number = tmp_id;

    for (int check_free_id = 0; check_free_id <= planes_count; check_free_id++)
    { if (planes_id[check_free_id] == -1) { planes_current_free_id = check_free_id; } }

    /* Plane Name */

    if (name == NULL) { strcpy(planes_arr[tmp_id].plane_name, "NO_NAME"); }

    else { strcpy(planes_arr[tmp_id].plane_name, name); }

    /* Plane X Chord */

    planes_arr[tmp_id].origin_x = x;

    /* Plane Y Chord */

    planes_arr[tmp_id].origin_y = y;
}

int del_plane(int id)
{
    return 0;
}

int select_plane(int id)
{
    return 0;
}

int config_plane(int id)
{
    return 0;
}

int exit_cli(void)
{
    endwin();

    return 0;
}