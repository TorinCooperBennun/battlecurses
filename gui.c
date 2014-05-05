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
#include <string.h>

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
    int win_w, win_h;
    int win_l, win_t;

    /* clear screen */
    erase();

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


int gui_render_endscreen()
{
    /* vars */
    int win_w, win_h;
    int win_l, win_t;
    int num_messages;
    int i;
    int row, col;

    /* constants */
    const char *messages[] = {
        "Thanks for playing battlecurses!",
        "Press any key to quit.",
        "",
        "battlecurses is free software licensed under GNU GPLv3.",
        "Leave feedback at <https://github.com/TorinCooperBennun/battlecurses>."
    };

    /* retrieve number of messages because I can't be bothered to type this as a
     * constant every time I update this thing */
    num_messages = sizeof(messages) / sizeof(const char *);

    /* clear screen */
    erase();

    /* get screen dimensions and top-left coordinates */
    getmaxyx(stdscr, win_h, win_w);
    getbegyx(stdscr, win_t, win_l);

    /* print messages, centered */
    for (i = 0; i < num_messages; ++i) {
        row = win_t + (win_h - 1) / 2 - num_messages / 2 + i;
        col = win_l + (win_w - 1) / 2 - strlen(messages[i]) / 2;
        mvprintw(row, col, messages[i]);
    }

    return 0;
}
