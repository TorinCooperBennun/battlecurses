/* my headers */
#include "gui.h"

/* curses */
#include <ncurses.h>


int gui_default_state(struct gui_state *gstate)
{
    gstate->focus = GUI_FOCUS_MAIN_MENU;
    gstate->error = GUI_ERR_OK;
    return 0;
}


int gui_render(struct gui_state *gstate)
{
    /* vars */
    int res;
    int win_w, win_h;
    int win_l, win_t;

    /* clear screen */
    res = erase();
    if (res != OK) {
        endwin();
        perror("erase failed");
        return -1;
    }

    /* get screen dimensions and top-left coordinates */
    getmaxyx(stdscr, win_h, win_w);
    getbegyx(stdscr, win_t, win_l);

    switch (gstate->focus) {

        /* main menu */
        case GUI_FOCUS_MAIN_MENU:
            mvprintw(win_t, win_l, "main menu");
            break;

        /* options menu */
        case GUI_FOCUS_OPTIONS_MENU:
            mvprintw(win_t, win_l, "options menu");
            break;

        /* game */
        case GUI_FOCUS_GAME:
            mvprintw(win_t, win_l, "game");
            break;

        /* quit confirmation */
        case GUI_FOCUS_QUIT_CONFIRM:
            mvprintw(win_t, win_l, "quit confirmation");
            break;

        default:
            break;
    }

    return 0;
}
