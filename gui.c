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
#include "colours.h"
#include "gui.h"

/* standard headers */
#include <stdlib.h>
#include <string.h>

/* curses */
#ifdef USING_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif


static int main_menu_newgame_callback(struct gui_state *gstate, void *data)
{
    gstate->focus = GUI_FOCUS_GAME;
    return 0;
}


static int main_menu_options_callback(struct gui_state *gstate, void *data)
{
    gstate->focus = GUI_FOCUS_OPTIONS_MENU;
    return 0;
}


static int main_menu_quit_callback(struct gui_state *gstate, void *data)
{
    gstate->focus = GUI_FOCUS_QUIT_CONFIRM;
    return 0;
}


int gui_default_state(struct gui_state *gstate)
{
    /* vars */
    struct gui_dialog_item item;
    struct gui_dialog_item *item_ptr;

    /* constants */
    const int main_menu_items = 3;

    /* default options */
    gstate->focus = GUI_FOCUS_MAIN_MENU;
    gstate->error = GUI_ERR_OK;
    gstate->in_game = 0;
    gstate->selected_item = 0;

    /* allocate for main menu items */
    item_ptr = (struct gui_dialog_item *) malloc(main_menu_items * sizeof(struct gui_dialog_item));
    gstate->main_menu_dialog.items = item_ptr;
    gstate->main_menu_dialog.num_items = main_menu_items;

    /* New Game */
    item.str = "New Game";
    item.type = GUI_DIALOG_ITEM_BUTTON;
    item.callback = main_menu_newgame_callback;
    memcpy(item_ptr, &item, sizeof(item));

    /* Options */
    item.str = "Options";
    item.callback = main_menu_options_callback;
    memcpy(++item_ptr, &item, sizeof(item));

    /* Quit */
    item.str = "Quit";
    item.callback = main_menu_quit_callback;
    memcpy(++item_ptr, &item, sizeof(item));

    /* set up main menu dialog */
    gstate->main_menu_dialog.title = "Main Menu";
    gstate->main_menu_dialog.centered = 1;
    gstate->main_menu_dialog.autosize = 1;
    gstate->main_menu_dialog.h_margin = 20;

    /*
    gstate->main_menu_dialog.x = 7;
    gstate->main_menu_dialog.y = 7;
    gstate->main_menu_dialog.w = 80;
    gstate->main_menu_dialog.h = 25;
    */

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

    mvprintw(2, 4, "%d", gstate->main_menu_dialog.num_items);
    mvprintw(3, 4, "%d", gstate->selected_item);

    switch (gstate->focus) {

        /* main menu */
        case GUI_FOCUS_MAIN_MENU:
            mvprintw(win_t, win_l, "main menu");
            gui_render_dialog(&gstate->main_menu_dialog, gstate->selected_item);
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


int gui_render_dialog(struct gui_dialog_info *dinfo, int selected_item)
{
    /* vars */
    int win_h, win_w;
    int win_t, win_l;
    int x, y;
    int i, len;
    int tl_x, tl_y;
    int br_x, br_y;
    int w, h;

    /* get screen dimensions and top-left coordinates */
    getmaxyx(stdscr, win_h, win_w);
    getbegyx(stdscr, win_t, win_l);

    /* no autosize */
    if (!dinfo->autosize) {
        w = dinfo->w;
        h = dinfo->h;

    /* autosize using lengths of contained items */
    } else {
        if (!dinfo->num_items) {
            w = 32;
            h = 10;
        } else {
            h = 5 + dinfo->num_items * 2;
            w = strlen(dinfo->title);
            for (i = 0; i < dinfo->num_items; ++i) {
                len = strlen(dinfo->items[i].str);
                if (len > w) {
                    w = len;
                }
            }
            w += dinfo->h_margin * 2;
        }
    }

    /* centered */
    if (dinfo->centered) {
        tl_x = win_l + win_w / 2 - w / 2;
        br_x = tl_x + w - 1;
        tl_y = win_t + win_h / 2 - h / 2;
        br_y = tl_y + h - 1;

    /* not centered */
    } else {
        tl_x = dinfo->x;
        br_x = tl_x + w - 1;
        tl_y = dinfo->y;
        br_y = tl_y + h - 1;
    }

    attron(COLOR_PAIR(COLOUR_DIALOG_BORDER));

    /* render corners */
    mvaddch(tl_y, tl_x, ACS_ULCORNER);
    mvaddch(tl_y, br_x, ACS_URCORNER);
    mvaddch(br_y, tl_x, ACS_LLCORNER);
    mvaddch(br_y, br_x, ACS_LRCORNER);

    /* render horizontal sides */
    for (x = tl_x + 1; x < br_x; ++x) {
        mvaddch(tl_y, x, ACS_HLINE);
        mvaddch(br_y, x, ACS_HLINE);
    }

    /* render vertical sides */
    for (y = tl_y + 1; y < br_y; ++y) {
        mvaddch(y, tl_x, ACS_VLINE);
        mvaddch(y, br_x, ACS_VLINE);
    }

    attroff(COLOR_PAIR(COLOUR_DIALOG_BORDER));

    attron(COLOR_PAIR(COLOUR_DIALOG_TITLE));

    /* render title */
    y = tl_y;
    x = (tl_x + br_x) / 2 - strlen(dinfo->title) / 2;
    mvprintw(y, x, dinfo->title);

    attroff(COLOR_PAIR(COLOUR_DIALOG_TITLE));

    attron(COLOR_PAIR(COLOUR_DIALOG_TEXT));

    /* render items */
    y = tl_y + 3;
    for (i = 0; i < dinfo->num_items; ++i) {
        x = (tl_x + br_x) / 2 - strlen(dinfo->items[i].str) / 2;

        if (i == selected_item) {
            attroff(COLOR_PAIR(COLOUR_DIALOG_TEXT));
            attron(COLOR_PAIR(COLOUR_DIALOG_SELECTED));
        }

        mvprintw(y, x, dinfo->items[i].str);

        if (i == selected_item) {
            attroff(COLOR_PAIR(COLOUR_DIALOG_SELECTED));
            attron(COLOR_PAIR(COLOUR_DIALOG_TEXT));
        }

        y += 2;
    }

    attroff(COLOR_PAIR(COLOUR_DIALOG_TEXT));

    return 0;
}
