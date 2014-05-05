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
#include "gui.h"

/* standard headers */
#include <stdio.h>

/* curses */
#include <ncurses.h>


int main(int argc, char *argv[])
{
    /* vars */
    struct gui_state gstate;
    int c;
    int running;
    int res;
    int tick;

    /* process args (none supported currently) */
    if (argc > 1) {
        fprintf(stderr, "unrecognised argument(s)\n");
        return -1;
    }

    /* init curses */
    initscr();

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
