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

            /* quit command */
            case 'q':

                /* send to quit confirmation if not already there, or quit */
                if (gstate.focus != GUI_FOCUS_QUIT_CONFIRM) {
                    gstate.focus = GUI_FOCUS_QUIT_CONFIRM;
                } else {
                    running = 0;
                }
                break;

            default:
                break;
        }
    }

    /* quit curses and stop normally */
    endwin();
    return 0;
}
