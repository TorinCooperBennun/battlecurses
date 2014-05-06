/* my headers */
#include "check.h"

/* standard headers */
#include <stdio.h>
#include <stdlib.h>

/* curses */
#include <ncurses.h>

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
