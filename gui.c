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
    struct gui_dialog_info main_menu_dialog;

    /* clear screen */
    erase();

    /* get screen dimensions and top-left coordinates */
    getmaxyx(stdscr, win_h, win_w);
    getbegyx(stdscr, win_t, win_l);

    /* set up main menu dialog */
    main_menu_dialog.items = NULL;
    main_menu_dialog.num_items = 0;
    main_menu_dialog.title = "Main Menu";
    main_menu_dialog.x = 7;
    main_menu_dialog.y = 7;
    main_menu_dialog.w = 80;
    main_menu_dialog.h = 25;

    switch (gstate->focus) {

        /* main menu */
        case GUI_FOCUS_MAIN_MENU:
            mvprintw(win_t, win_l, "main menu");
            gui_render_dialog(&main_menu_dialog);
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

    /* set cursor to bottom-right */
    move(win_t + win_h - 1, win_l + win_w - 1);
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


int gui_render_dialog(struct gui_dialog_info *dinfo)
{
    /* vars */
    int x, y;

    /* render corners */
    mvaddch(dinfo->y,                dinfo->x,                ACS_ULCORNER);
    mvaddch(dinfo->y,                dinfo->x + dinfo->w - 1, ACS_URCORNER);
    mvaddch(dinfo->y + dinfo->h - 1, dinfo->x,                ACS_LLCORNER);
    mvaddch(dinfo->y + dinfo->h - 1, dinfo->x + dinfo->w - 1, ACS_LRCORNER);

    /* render horizontal sides */
    for (x = dinfo->x + 1; x < dinfo->x + dinfo->w - 1; ++x) {
        mvaddch(dinfo->y,                x, ACS_HLINE);
        mvaddch(dinfo->y + dinfo->h - 1, x, ACS_HLINE);
    }

    /* render vertical sides */
    for (y = dinfo->y + 1; y < dinfo->y + dinfo->h - 1; ++y) {
        mvaddch(y, dinfo->x,                ACS_VLINE);
        mvaddch(y, dinfo->x + dinfo->w - 1, ACS_VLINE);
    }

    /* render title */
    y = dinfo->y;
    x = dinfo->x + dinfo->w / 2 - strlen(dinfo->title) / 2;
    mvprintw(y, x, dinfo->title);

    return 0;
}
