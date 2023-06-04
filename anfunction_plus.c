#include "main.h"
#include <string.h>

/**
 * print_unsigned -This prints an unsigned number
 * @num: unsigned number to print
 * @buffer: buffer to print the number to
 * @fags: flags to control the printing
 * @wid: width of the number to print
 * @precision: The precision of the number to print
 * @size: The size of the number to print
 * Return: Number of printed characters.
 */
int print_unsigned(unsigned long int num, char *buffer,
		int fags, int wid, int precision, int size)
{
	if (num == 0)
	{
		buffer[0] = '0';
		return (1);
	}

	char str[32];
	sprintf(str, "%lu", num);

	if (precision > 0)
	{
		str[precision] = '\0';
	}
	int d, pad;
	int pad = wid - strlen(str);

	if (pad > 0)
	{
		for (int d = 0; d < pad; d++)
		{
			buffer[d] = ' ';
		}
	}

	strcpy(buffer + pad, str);

	return (strlen(buffer));
}

/**
 * print_octal - Prints an unsigned number in octal form
 * @num: unsigned number to print
 * @buffer: buffer to print the number to
 * @flags: flags to control the printing
 * @width: width of the number to print
 * @precision: The precision of the number to print
 * @size: The size of the number to print
 * Return: Number of printed characters.
 */

int print_octal(unsigned long int num, char *buffer,
		int fags, int wid, int precision, int size)
{
	if (num == 0)
	{
		buffer[0] = '0';
		return (1);
	}

	char str[32];
	sprintf(str, "%lo", num);

	if (precision > 0)
	{
		str[precision] = '\0';
	}

	int d, pad;
	int pad = wid - strlen(str);

	if (pad > 0)
	{
		for (int d = 0; d < pad; d++)
		{
			buffer[d] = ' ';
		}
	}

	strcpy(buffer + pad, str);

	return (strlen(buffer));
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal form
 * @num: unsigned number to print
 * @buffer: buffer to print the number to
 * @fags: flags to control the printing
 * @wid: width of the number to print
 * @precision: The precision of the number to print
 * @size: The size of the number to print
 * Return: Number of characters printed.
 */
int print_hexadecimal(unsigned long int num, char *buffer, int fags,
		int wid, int precision, int size)
{
	if (num == 0)
	{
		buffer[0] = '0';
		return (1);
	}

	char str[32];
	sprintf(str, "%lx", num);

	if (precision > 0)
	{
		str[precision] = '\0';
	}

	int d, pad;
	int pad = wid - strlen(str);

	if (pad > 0)
	{
		for (int d = 0; d < pad; d++)
		{
			buffer[d] = ' ';
		}
	}

	strcpy(buffer + pad, str);

	return (strlen(buffer));
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal form
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: acquire width
 * @precision: Precision specification
 * @size: Specifies size
 * Return: Number of printed characters
 */

int print_hexa_upper(va_list types, char buffer[],
	int fags, int wid, int precision, int size)
{
	char *hexie_digits = "0123456789ABCDEF";

	return (print_hexa(types, hexie_digits, buffer,
		fags, 'X', wid, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @flag_ch: Calculates active flags
 * @wid: Acquires width
 * @precision: Specifies precision
 * @size: Specifies size
 * Return: Number of printed characters
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int fags, char flag_ch, int wid, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[d--] = '0';
	}

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[d--] = map_to[num % 16];
		num /= 16;
	}

	if (fags & F_HASH && init_num != 0)
	{
		buffer[d--] = flag_ch;
		buffer[d--] = '0';
	}

	d++;

	return (write_unsgnd(0, d, buffer, fags, wid, precision, size));
}

