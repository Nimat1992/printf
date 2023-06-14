#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 * This struct represents a format string and the function associated with it.
 * @fmt: The format string.
 * @fn: The function associated with the format string.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - defines a struct that represents a format string
 * and the function associated
 *@fmt: is the format specifier.
 *@fn: is the function associated with the format specifier.
 */

typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int fags, int wid, int precision, int size);

/* Functions that prints chars and strings */
int print_char(va_list types, char buffer[],
		int fags, int wid, int precision, int size);
int print_string(va_list types, char buffer[],
		int fags, int wid, int precision, int size);
int print_percent(va_list types, char buffer[],
		int fags, int wid, int precision, int size);

/* printing numbers */
int print_int(va_list types, char buffer[],
		int fags, int wid, int precision, int size);
int print_binary(va_list types, char buffer[],
		int fags, int wid, int precision, int size);
int print_unsigned(va_list types, char buff[],
		int fags, int wid, int precision, int size);
int print_octal(va_list types, char buffer[],
		int fags, int wid, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
		int fags, int wid, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
		int fags, int wid, int precision, int size);
int print_hexa(va_list types, char map_to[], char buffer[],
		int fags, char flag_ch, int wid, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list types, char buffer[],
		int flags, int wid, int precision, int size);

/* printing memory address */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* Functions that will handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/* Function that will print string in reverse */
int print_reverse(va_list types, char buffer[],
		int fags, int wid, int precision, int size);

/* printing a string in rot 13 */
int print_rot13string(va_list types, char buffer[],
		int fags, int wid, int precision, int size);

/* Width handling */
int handle_write_char(char c, char *buffer, int fags, int wid);
int write_number(int is_negative, int ind, char *buffer,
		int fags, int wid, int num, int precision);
int write_num(int ind, char *buffer, int fags, int precision,int wid,
		int length, int num, char padd, char extra_c);
int write_pointer(char *buffer, int ind, int length, int wid,
		int fags, int num, char padd, char extra_c);


/*************Support Functions **************************/

int is_printable(char c);
int append_hexa_code(char buffer[], int i, char ascii_code);
int is_digit(char c);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif
