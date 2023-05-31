#include "main.h"
#include <string.h>

/**
 * print_pointer - Printing a pointer variable
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_pointer(va_list types, char buffer[],
	int fags, int wid, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2,
	padd_start = 1; /* length = 2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(wid);
	UNUSED(precision);

	if (addrs == NULL)
	{
		buffer[0] = '(';
		buffer[1] = 'n';
		buffer[2] = 'd';
		buffer[3] = 'l';
		buffer[4] = '\0';
		return (5);
	}
	buffer[BUFF_SIZE - 1] = '\0';
	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	if ((fags & F_ZERO) && !(fags & F_MINUS))
		padd = '0';
	if (fags & F_PLUS)
	{
		extra_c = '+';
		length++;
	}
	else if (fags & F_SPACE)
	{
		extra_c = ' ';
		length++;
	}
	ind++;
	return (write_pointer(buffer, ind, length,
		wid, fags, padd, extra_c, padd_start));
}


/**
 * print_non_printable - Prints ASCII codes
 * in hexadecimal of non-printable chars
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int fags, int wid, int precision, int size)
{
	int d = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(wid);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		buffer[0] = '(';
		buffer[1] = 'n';
		buffer[2] = 'i';
		buffer[3] = 'l';
		buffer[4] = 'l';
		buffer[5] = '\0';
		return (6);
	}

	while (str[d] != '\0')
	{
		if (is_printable(str[d]))
			buffer[d + offset] = str[d];
		else
			offset += append_hexa_code(str[d], buffer, d + offset);

		d++;
	}

	buffer[d + offset] = '\0';

	return (write(1, buffer, d + offset));
}


/**
 * print_rot13string - Print a string in ROT13.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int fags, int wid, int precision, int size)
{
	char x;
	char *str;
	unsigned int d, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(fags);
	UNUSED(wid);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (d = 0; str[d]; d++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[d])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[d];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

/**
 * print_reverse - Print a string in reverse.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int print_reverse(va_list types, char *buffer,
	int fags, int wid, int precision, int size)
{
	char *str;
	int d, count = 0;

	/* Unused parameters */
	(void)buffer;
	(void)fags;
	(void)wid;
	(void)size;

	str = va_arg(types, char *);

	if (str == NULL)
	{
		/* If the string is NULL, print ")Null(" */
		str = ")Null(";
	}

	/* Get the length of the string */
	int len = strlen(str);

	/* Reverse the string */
	for (d = 0; d < len / 2; d++)
	{
		char temp = str[d];

		str[d] = str[len - d - 1];

		str[len - d - 1] = temp;

	}

	/* Write the reversed string to stdout */
	for (d = 0; str[d]; d++)
	{
		write(1, &str[d], 1);
		count++;
	}

	return (count);
}
