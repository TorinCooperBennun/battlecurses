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


/* list of all structs */
struct game_map;
struct game_state;


/* list of tile types */
enum game_tile_type {
    GAME_TILE_FLOOR,
    GAME_TILE_WALL,
    GAME_TILE_WATER
};


/* structure containing info for a single tile */
struct game_tile {
    enum game_tile_type type;

    struct game_item *items;
    int num_items;
};


/* structure containing the map itself */
struct game_map {
    struct game_tile *tiles;

    int width, height;
};


/* structure containing info about the current game */
struct game_state {
    struct game_map map;

    int centre_x, centre_y;
};
