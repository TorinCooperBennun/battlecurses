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

/* curses */
#ifdef USING_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif


int colours_init()
{
    init_pair(COLOUR_DIALOG_BORDER,     COLOR_RED,     COLOR_WHITE);
    init_pair(COLOUR_DIALOG_TITLE,      COLOR_BLACK,   COLOR_WHITE);
    init_pair(COLOUR_DIALOG_BACKGROUND, COLOR_BLACK,   COLOR_RED);
    init_pair(COLOUR_DIALOG_TEXT,       COLOR_BLACK,   COLOR_WHITE);
    init_pair(COLOUR_DIALOG_SELECTED,   COLOR_WHITE,   COLOR_BLACK);

    init_pair(COLOUR_MENU_BACKGROUND,   COLOR_BLACK,   COLOR_BLUE);

    init_pair(COLOUR_BULLET,            COLOR_CYAN,    COLOR_WHITE);
    init_pair(COLOUR_MISSILE,           COLOR_MAGENTA, COLOR_WHITE);

    return 0;
}
