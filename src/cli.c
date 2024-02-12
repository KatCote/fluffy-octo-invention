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

        char input_str[MAX_COMMAND_LEN];
        char command_parts[MAX_COMMAND_LEN] = " ";
        char *istr;

        for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
        { mvaddch(size.ws_row - 2, tmp_col, '-'); mvaddch(size.ws_row - 1, tmp_col, ' '); }

        mvprintw(size.ws_row - 1, 1, ">>> ");
        refresh();

        /* Command Parsing */

        char first_key = getch();

        if (first_key == 3) { /*  ungetstr() TODO */ }

        input_str[0] = first_key;
        getstr(input_str + 1);

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
            { default_help: help(NULL, 0); }

            wait_press_any_key continue;
        }

        else if (!strcmp(istr, "plane"))
        {
            istr = strtok (NULL, command_parts);

            if (istr == NULL)
            { goto default_cli_plane; }

            if (!strcmp(istr, "list"))
            { list(0); continue; }

            else if (!strcmp(istr, "add")) // TODO
            {
                istr = strtok (NULL, command_parts);
                int arg_x, arg_y;

                char * tmp_arg_1 = strtok (NULL, command_parts);
                if (tmp_arg_1 != NULL) { arg_x = atoi(tmp_arg_1); } else { arg_x = 0; }

                char * tmp_arg_2 = strtok (NULL, command_parts);
                if (tmp_arg_2 != NULL) { arg_y = atoi(tmp_arg_2); } else { arg_y = 0; }

                add_plane(istr, arg_x, arg_y);
                
                continue;
            }

            else if (!strcmp(istr, "delete"))
            { goto default_cli_plane; }

            else if (!strcmp(istr, "select"))
            { goto default_cli_plane; }

            else
            {
                default_cli_plane: help(NULL, 1);
                wait_press_any_key continue;
            }
            
            continue;
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

            continue;
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

            continue;
        }

        else { continue; }
    }

    return 0;
}

void help(char * command_d, int type_d) // _d set by code, not user
{
    /* Current Screen Size */

    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
    printf("TIOCGWINSZ error");

    for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
    { mvaddch(size.ws_row - 1, tmp_col, ' '); }

    switch (type_d)
    {
    case 0: // DEFAULT HELP
        mvprintw(size.ws_row - 1, 1, "TBD");

        return;

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

            mvprintw(size.ws_row - 2, 1, "help:plane");
            mvprintw(size.ws_row - 1, 1, "\tadd [NAME] [X] [Y]\t| delete [ID]\t| select [ID]\t| config [ID]\t| info [ID]\t| list");
        }

        return;

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

        return;

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

        return;
    
    default: return;
    }
}

void list(/*int optional_id,*/int type_d) // _d set by code, not user
{
    /*
    TYPE:
    0 - planes
    1 - points
    */

   struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
    printf("TIOCGWINSZ error");

   switch (type_d)
   {
        case 0: // PLANES
        
            for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
            { mvaddch(size.ws_row - 1, tmp_col, ' '); }

            //mvprintw(size.ws_row - 1, 1, "COUNT: %d\tACTIVE: %d", planes_count, planes_active);

            if (planes_count > 0)
            {
                int p_id = 0;
                char key = '0';

                curs_set(0); 
                noecho(); 

                while (key != 'q')
                {
                    /* Choose next p_id */

                    switch (key)
                    {
                    case 2: // ARROW UP
                        if (p_id - 1 >= 0 && planes_id[p_id - 1] != -1)
                            p_id -= 1;
                        break;

                    case 3: // ARROW DOWN
                        if (p_id + 1 < MAX_PLANES && planes_id[p_id + 1] != -1)
                            p_id += 1;
                        break;
                    
                    default: break;
                    }
                    
                    /* Clear output */

                    for (int tmp_col = 0; tmp_col < size.ws_col; tmp_col++)
                    { mvaddch(size.ws_row - 1, tmp_col, ' '); }

                    mvprintw(size.ws_row - 2, 1, "plane-list");

                    /* Base Info */

                    mvprintw(size.ws_row - 1, 1, "COUNT: %d FREE_ID: %d", planes_count, planes_current_free_id);

                    /* Current Plane Info */

                    mvprintw(size.ws_row - 1, 25,
                    "| ID: %d,  NAME: \"%s\", ORIGIN_X: %d, ORIGIN_Y: %d, POINTS: %d |",
                    planes_id[p_id],
                    planes_arr[p_id].plane_name,
                    planes_arr[p_id].origin_x,
                    planes_arr[p_id].origin_y,
                    planes_arr[p_id].points_count);

                    key = getch();
                }

                curs_set(2); 
                echo();
            }
            else
            {
                mvprintw(size.ws_row - 2, 1, "error");
                mvprintw(size.ws_row - 1, 1, "\tthere is not a single plane. try \"plane add [name]\" or \"help\"");

                wait_press_any_key
            }

            return;
        
        default: return;
   }
}

void info(int id, int type_d) // _d set by code, not user
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

int config_plane(int id)
{
    return 0;
}

int exit_cli(void)
{
    endwin();

    return 0;
}

int ungetstr(char * str)
{
    if (str == NULL) { return 1; }

    // TODO

    return 0;
}