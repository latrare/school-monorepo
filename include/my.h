/*-
 * Trevor Miranda
 * 
 * Project Description:
 * An implementation of stdlibc functions.
 */

#ifndef _MY_H_
#define _MY_H_
#ifndef NULL
#define NULL ((void *)0)
#endif

#include <stdlib.h>
#include <unistd.h>

/* The following functions all print their types to stdout using my_char */
void my_char(char);

/* No variable declarations inside this method */
void my_str(char *);

/* 
 * Prints integer on screen. Done in less than 10 lines, without recursion, no
 * pointers are allowed. (HINT: Can be done with two variables.)
 */
void my_int(int);

/*
 * Takes integer and string that has numbers that make up base 
 * Example outputs:
 * my_num_base(-123, "0123456789") => -123
 * my_num_base(9, "01") => 1001
 * my_num_base(7, "!?#") => #?
 * my_num_base(-7, "!?#") => -#?
 * my_num_base(3, "!") => !!!
 * my_num_base(5, "") => "Base not valid"
 * my_num_base(5, NULL) => "Base not valid"
 * my_num_base(-8, "-----") => ---
 */
void my_num_base(int, char *);

/* Print every letter of the alphabet. Can't use anything larger than 1 byte. */
void my_alpha();

/* Print every digit 0-9. Can't use anything larger than 1 byte. */
void my_digits();

/* Return -1 as result for NULL (for all functions with this return type) */
int my_strlen(char *);

/* Reverse the string in place then return length of string */
int my_revstr(char *);

/*
 * Return position of first instance of char in string.
 * String is only parsed once (with calls to other functions counted).
 */
int my_strpos(char *, char);

/*
 * Return position of the last instance of char in string.
 * String is only parsed once (with calls to other functions counted).
 */
int my_strrpos(char *, char);

/* Duplicate the string and return a pointer to the copy */
char *my_strdup(char *);

/*
 * Compare two given strings are return the following:
 * (< 0) if the second string is alphabetically less than the first string
 * (> 0) if the second string is alphabetically more than the first string
 * (= 0) if the second string and first string are alphabetically identical
 */
int my_strcmp(char *, char *);

/* Same as my_strcmp, but only compare int bytes of the second string */
int my_strncmp(char *, char *, unsigned int);

/* Copy source string to destination string, then return destination pointer */
char *my_strcpy(char *, char *);

/* Same as my_strcpy, but only copy int bytes from source string */
char *my_strncpy(char *, char *, unsigned int);

/*
 * Create new string, concatenate the second string onto the source string in
 * new string
 */
char *my_strcat(char *, char *);

/* Concatenate the second string on to the first string if there's enough space */
char *my_strconcat(char *, char *);

/* Same as my_strcat, but only concatenate int bytes from the second string */
char *my_strnconcat(char *, char *, unsigned int);

/*
 * Return pointer to the first occurence of the given character in the given
 * string
 */
char *my_strfind(char *, char);

/* Same as my_strfind, but return a pointer to the last occurence instead */
char *my_strrfind(char *, char);

/* Wrapped malloc */
void *xmalloc(unsigned int);

/* Convert vector to string */
char *my_vect2str(char **);

#endif
