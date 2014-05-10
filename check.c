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
#include "check.h"

/* standard headers */
#include <stdio.h>
#include <stdlib.h>

/* curses */
#ifdef USING_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif

/* zlib */
#include <zlib.h>


/* data stored in program */
const unsigned char check_data[] = {0x0};
const int  check_data_len = 0;


char *check_retrieve_data(int *size)
{
    /* vars */
    z_stream stream;
    int res;

    /* init stream */
    stream.next_in = (z_const Bytef *)check_data;
    stream.avail_in = check_data_len;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    res = inflateInit(&stream);
    
    /* if it failed, die immediately */
    if (res != Z_OK) {
        endwin();

        /* appropriate messages */
        switch (res) {
            case Z_MEM_ERROR:
                fprintf(stderr, "zlib inflateInit failed with Z_MEM_ERROR\n");
                break;
            case Z_STREAM_ERROR:
                fprintf(stderr, "zlib inflateInit failed with Z_STREAM_ERROR\n");
                break;
            case Z_VERSION_ERROR:
                fprintf(stderr, "zlib inflateInit failed with Z_VERSION_ERROR\n");
                break;
            default:
                fprintf(stderr, "zlib inflateInit failed with an unknown error %d\n", res);
                break;
        }

        exit(-1);
    }

    /* to be continued */
    *size = 0;
    return NULL;
}
