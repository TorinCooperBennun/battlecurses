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


#ifndef CHECK_H
#define CHECK_H


/* check_retrieve_data(int *size)
 *
 * Description:
 * Inflates the compressed check data held in program memory and
 * stores it in a newly-allocated buffer. The size, in bytes, of the inflated
 * data will be stored in size.
 *
 * Returns:
 * A pointer to the first byte of the inflated data, or NULL upon failure (this
 * failure should be treated as fatal, probably).
 */
char *check_retrieve_data(int *size);


#endif
