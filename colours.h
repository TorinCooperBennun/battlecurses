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


#ifndef COLOURS_H
#define COLOURS_H


enum colours {
    COLOUR_DIALOG_BORDER = 0,
    COLOUR_DIALOG_TITLE,
    COLOUR_DIALOG_BACKGROUND,
    COLOUR_DIALOG_TEXT,
    COLOUR_DIALOG_SELECTED,

    COLOUR_MENU_BACKGROUND,

    COLOUR_BULLET,
    COLOUR_MISSILE
};


/* colours_init()
 *
 * Description:
 * Sets up all the colour pairs for the game (enum containing all pair indexes
 * is above).
 *
 * Returns:
 * 0, always.
 */
int colours_init();


#endif
