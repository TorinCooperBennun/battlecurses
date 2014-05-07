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
#include "gui.h"

/* standard headers */
#include <stdio.h>
#include <string.h>

/* curses */
#include <ncurses.h>


int main(int argc, char *argv[])
{
    /* vars */
    struct gui_state gstate;
    struct gui_dialog_info dialog;
    struct gui_dialog_item dialog_msg;
    int c;
    int yn_selected;
    int running;
    int res;
    int tick;
    int next_index;

    /* constants */
    const int check[] = {0x6E, 0x69, 0x67, 0x67, 0x61};

    /* process args (none supported currently) */
    if (argc > 1) {
        fprintf(stderr, "unrecognised argument(s)\n");
        return -1;
    }

    /* init curses */
    initscr();

    /* give warning dialog if colors are not supported */
    if (has_colors() == FALSE) {

        /* set up message */
        dialog_msg.type = GUI_DIALOG_ITEM_MESSAGE;
        dialog_msg.str =
            "Your terminal doesn't seem to support colours! The game will run,"
            "but everything will look pretty weird. Continue? (y/n)";

        /* set up dialog info */
        dialog.items = &dialog_msg;
        dialog.num_items = 1;
        dialog.title = "No colours!";
        dialog.centered = 1;
        dialog.autosize = 1;

        /* render dialog */
        gui_render_dialog(&dialog);

        /* ask for y/n */
        yn_selected = 0;
        while (!yn_selected) {
            c = getch();

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

    /* if colors are supported, init them */
    } else {
        start_color();
    }

    /* non-blocking read */
    timeout(0);

    /* F-key support */
    keypad(stdscr, TRUE);

    /* no line buffering */
    raw();

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
        c = getch();

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

                /* send to quit confirmation */
                if (gstate.focus != GUI_FOCUS_QUIT_CONFIRM) {
                    gstate.focus = GUI_FOCUS_QUIT_CONFIRM;

                /* already at quit confirmation, quit */
                } else {
                    running = 0;
                }
                break;

            default:
                break;
        }
    }

    /* show end splash, quit curses and stop normally */
    gui_render_endscreen();
    timeout(-1);
    getch();
    erase();
    refresh();
    endwin();
    return 0;
}
