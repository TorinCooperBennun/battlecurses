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
