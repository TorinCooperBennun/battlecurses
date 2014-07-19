/* Copyright 2014 Torin Cooper-Bennun
 *
 * This file is part of battlecurses.
 *
 * battlecurses is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * battlecurses is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with battlecurses. If not, see <http://www.gnu.org/licenses/>.
 */


/* my headers */
#include "check.h"
#include "colours.h"
#include "gui.h"

/* standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* curses */
#ifdef USING_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif

/* windows if relevant */
#if defined __CYGWIN__ || defined _WIN16 || defined _WIN32 || defined __WIN32__ || defined __TOS_WIN__ || defined __WINDOWS__
#define USING_WINDOWS
#include <windows.h>
#endif


int main(int argc, char *argv[])
{
    /* gui structures */
    struct gui_state       gstate;
    struct gui_dialog_info dialog;
    struct gui_dialog_item dialog_msg;

    /* temps */
    int c;
    int yn_selected;
    int res;
    int next_index;

    /* status */
    int      running;
    unsigned tick;

    /* global options */
    /*
    int server;
    */

    /* constants */
    const int check[] = {0x6E, 0x69, 0x67, 0x67, 0x61};

#ifdef USING_WINDOWS
    /* windows-only vars */
    HANDLE console_buffer;
    CONSOLE_SCREEN_BUFFER_INFO old_console_info;
    COORD console_size;
    SMALL_RECT console_window;
    LPTSTR error_string = NULL;
    DWORD error;

    /* get console handle */
    console_buffer = GetStdHandle(STD_OUTPUT_HANDLE);

    /* store old console information */
    res = GetConsoleScreenBufferInfo(console_buffer, &old_console_info);
    if (!res) {
        error = GetLastError();
        res = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, res, 0, error_string, 256, NULL);
        if (!res || error_string == NULL) {
            fprintf(stderr, "Setting console size to maximum of (%d, %d) failed, error code %d\n", console_size.X, console_size.Y, (int) error);
        } else {
            fprintf(stderr, "Setting console size to maximum of (%d, %d) failed:\n%s\n", console_size.X, console_size.Y, error_string);
        }
        return -1;
    }

    /* make console fill the screen */
    console_size = GetLargestConsoleWindowSize(console_buffer);
    console_size.X -= 2;
    console_size.Y -= 2;
    res = SetConsoleScreenBufferSize(console_buffer, console_size);
    if (!res) {
        error = GetLastError();
        res = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, res, 0, error_string, 256, NULL);
        if (!res || error_string == NULL) {
            fprintf(stderr, "Setting console size to maximum of (%d, %d) failed, error code %d\n", console_size.X, console_size.Y, (int) error);
        } else {
            fprintf(stderr, "Setting console size to maximum of (%d, %d) failed:\n%s\n", console_size.X, console_size.Y, error_string);
        }
        return -1;
    }
    console_window.Left = 0;
    console_window.Top = 0;
    console_window.Right = console_size.X - 1;
    console_window.Bottom = console_size.Y - 1;
    res = SetConsoleWindowInfo(console_buffer, TRUE, &console_window);
    if (!res) {
        error = GetLastError();
        res = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, res, 0, error_string, 256, NULL);
        if (!res || error_string == NULL) {
            fprintf(stderr, "Setting console size to maximum of (%d, %d) failed, error code %d\n", console_size.X, console_size.Y, (int) error);
        } else {
            fprintf(stderr, "Setting console size to maximum of (%d, %d) failed:\n%s\n", console_size.X, console_size.Y, error_string);
        }
        return -1;
    }
#endif

    /* process args (none supported currently) */
    if (argc > 1) {
        fprintf(stderr, "unrecognised argument(s)\n");
        return -1;
    }

    /* init curses */
    initscr();

    /* give warning dialog if colours are not supported */
    if (has_colors() == FALSE) {

        /* set up message */
        dialog_msg.type = GUI_DIALOG_ITEM_MESSAGE;
        dialog_msg.str = "Your terminal doesn't support colours. This will look REALLY weird. Continue? (y/n)";

        /* set up dialog info */
        dialog.items = &dialog_msg;
        dialog.num_items = 1;
        dialog.title = "No colours!";
        dialog.centered = 1;
        dialog.autosize = 1;

        /* render dialog */
        gui_render_dialog(&dialog, -1);

        /* ask for y/n */
        yn_selected = 0;
        while (!yn_selected) {
            c = wgetch(stdscr);

            /* continue as normal if 'y' hit */
            if (c == 'y' || c == 'Y') {
                yn_selected = 1;

            /* quit program if 'n' hit */
            } else if (c == 'n' || c == 'N') {
                erase();
                refresh();
                endwin();
                return 0;
            }
        }

    /* if colours are supported, init them */
    } else {
        start_color();
        colours_init();
    }

    /* non-blocking read */
    timeout(0);

    /* F-key support */
    keypad(stdscr, TRUE);

    /* no line buffering */
    raw();

    /* detect return key */
    nonl();

    /* non-echoing getch */
    noecho();

    /* fill GUI state with default attributes */
    gui_default_state(&gstate);

    /* main loop */
    running = 1;
    tick = 0;
    next_index = 0;
    while (running) {

        ++tick;

        /* push GUI to screen */
        res = gui_render(&gstate);
        if (res != 0) {
            endwin();
            fprintf(stderr, "tick %d:\ngui_render failed\n", tick);
            return -1;
        }

        /* receive input (ERR received if none) */
        c = wgetch(stdscr);

        /* none received, back to top */
        if (c == ERR) {
            continue;
        }

        /* key combination check algorithm (no effect yet) */
        if (c == check[next_index]) {
            ++next_index;
            if (next_index == 5) {
                next_index = 0;
            }
        } else {
            next_index = 0;
        }

        switch (c) {

            case 'q':
                /* send to quit confirmation, if already there then quit */
                if (gstate.focus != GUI_FOCUS_QUIT_CONFIRM) {
                    gstate.focus = GUI_FOCUS_QUIT_CONFIRM;
                } else {
                    running = 0;
                }
                break;

            /* curses seems to use \r instead of KEY_ENTER */
            case '\r':
                switch (gstate.focus) {
                    case GUI_FOCUS_MAIN_MENU:
                        if (gstate.selected_item >= gstate.main_menu_dialog.num_items) {
                            endwin();
                            fprintf(stderr, "Index of selected dialog item (%d) out of range (main menu), max is %d\n", gstate.selected_item, gstate.main_menu_dialog.num_items);
                            return -1;
                        }
                        gstate.main_menu_dialog.items[gstate.selected_item].callback(&gstate, NULL);
                        break;

                    case GUI_FOCUS_QUIT_CONFIRM:
                        running = 0;

                    default:
                        break;
                }
                break;

            case KEY_UP:
                switch (gstate.focus) {
                    case GUI_FOCUS_MAIN_MENU:
                        --gstate.selected_item;
                        if (gstate.selected_item < 0) {
                            gstate.selected_item = gstate.main_menu_dialog.num_items - 1;
                        }

                    default:
                        break;
                }
                break;

            case KEY_DOWN:
                switch (gstate.focus) {
                    case GUI_FOCUS_MAIN_MENU:
                        ++gstate.selected_item;
                        if (gstate.selected_item >= gstate.main_menu_dialog.num_items) {
                            gstate.selected_item = 0;
                        }

                    default:
                        break;
                }

            default:
                break;
        }
    }

    /* show end splash, quit curses and stop normally */
    gui_render_endscreen();
    timeout(-1);
    wgetch(stdscr);
    erase();
    refresh();
    endwin();

#ifdef USING_WINDOWS
    /* attempt to restore previous console size + position */
    console_window = old_console_info.srWindow;
    SetConsoleWindowInfo(console_buffer, TRUE, &console_window);
    console_size = old_console_info.dwSize;
    SetConsoleScreenBufferSize(console_buffer, console_size);

    /* clear */
    system("cls");
#endif

    return 0;
}
