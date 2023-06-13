#include "main.h"

/**
 * is_printable - Evaluates if a char is printable.
 * @c: The char to be evaluated.
 *
 * Return: 1 if 'c' is printable, 0 otherwise.
 */

int is_printable(char c)
{
	/* ASCII printable characters are those with values between 32 and 126 */
	return (c >= 32 && c <= 126);
}

/**
 * append_hexa_code - Appends the hexadecimal code of a character to a buffer.
 * @buffer: The array of chars.
 * @i: The index at which to start appending.
 * @ascii_code: The ASCII code.
 *
 * Return: Always 3.
 */
int append_hexa_code(char buffer[], int i, char ascii_code)
{
	int m;

	/* The hexadecimal format code is always 2 digits long */
	if (ascii_code < 0)
	{
		ascii_code *= -1;
	}

	/* Convert the ASCII code to hexadecimal */
	char hex_code[2];

	sprintf(hex_code, "%02x", ascii_code);

	/* Append the hexadecimal code to the buffer */
	buffer[i++] = '\\';
	buffer[i++] = 'x';
	for (m = 0; m < 2; m++)
	{
		buffer[i++] = append_hexa_code[m];
	}

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit.
 * @c: Character to be evaluated.
 *
 * Return: 1 if 'c' is a digit, 0 otherwise.
 */
int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * convert_size_number - Casts a number to the specified size.
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: The casted value of 'num'.
 */
long int convert_size_number(long int num, int size)
{
	switch (size)
	{
		case S_LONG:
			return (num);
		case S_SHORT:
			return ((short) num);
		default:
			return ((int) num);
	}
}

/**
 * convert_size_unsgnd - Casts an unsigned number to the specified size.
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: The casted value of 'num'.
 */
unsigned long int convert_size_unsgnd(unsigned long int num, int size)
{
	switch (size)
	{
		case S_LONG:
			return (num);
		case S_SHORT:
			return ((unsigned short) num);
		default:
			return ((unsigned int) num);
	}
}

