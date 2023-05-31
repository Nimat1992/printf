#include "main.h"

/**
 * print_char - Prints a character
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Acquire width
 * @precision: Specifies precision
 * @size: Specifies size
 *
 * Return: Number of printed characters
 */
int print_char(va_list types, char buffer[],
		int fags, int wid, int precision, int size)
{
	char u = va_arg(types, int);

/* This specifies wid and pads the char with spaces to the specified width. */
	if (wid > 0)
	{
		for (int d = 0; d < wid; d++)
			buffer[d] = ' ';
	}

	/* The character is passed to the buffer. */
	buffer[wid - 1];
	/* Returns the number of printed characters. */
	return (wid);
}

/**
 * print_string - Prints a string
 * @types: Arguments list
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Acquire width
 * @precision: Specifies precision
 * @size: Specifies size
 *
 * Return: Number of printed characters
 */
int print_string(va_list types, char buffer[],
		int fags, int wid, int precision, int size)
{
	int length = 0;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(fags);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(null)";
	else if (precision >= 6)
		str = "      ";
	/* Acquire the length of the string */
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (wid > length)
	{
		if (fags & F_MINUS)
		{
			for (int d = 0; d < length; d++)
				buffer[d] = str[d];
			for (int d = length; d < wid; d++)
				buffer[d] = ' ';
		}
		else
		{
			for (int d = 0; d < wid - length; d++)
				buffer[d] = ' ';
			for (int d = wid - length; d < wid; d++)
				buffer[d] = str[d - (wid - length)];
		}
	}
	else
	{
		for (int d = 0; d < length; d++)
			buffer[d] = str[d];
	}
	return (length);
}

/**
 * print_percent - Prints a percent sign
 * @types: Arguments list
 * @buffer: Buffer array to handle print
 * @fags: Calculates flags that are active
 * @wid: Acquire width
 * @precision: Specifies precision
 * @size: Specifies size
 *
 * Return: Number of printed chars
 */
int print_percent(va_list types, char buffer[],
		int fags, int wid, int precision, int size)
{
	/* Remove the unused parameters */
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(fags);
	UNUSED(precision);
	UNUSED(size);

	/* Write the percent sign to the buffer */
	return (write(1, "%%", 1));
}

/**
 * print_int - Prints an integer
 * @types: Arguments list
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Width
 * @precision: Precision specification
 * @size: Specifies size
 *
 * Return: Number of printed characters
 */
int print_int(va_list types, char buffer[],
		int fags, int wid, int precision, int size)
{
	int d = BUFF_SIZE - 2;
	int is_negative = 0;
	long int x = va_arg(types, long int);
	unsigned long int num;

	/* Change integer to the specified size */
	x = convert_size_number(x, size);

	/* Write a zero to the buffer if the integer is indeed zero */
	if (x == 0)
		buffer[d--] = '0';

	/* Write the digits of the integer in reverse order to the buffer */
	num = (unsigned long int)x;
	if (x < 0)
	{
		num = (unsigned long int)((-1) * x);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[d--] = (num % 10) + '0';
		num /= 10;
	}

	/* What if the integer is negative? Write a minus sign to the buffer */
	if (is_negative)
		buffer[d--] = '-';

	/* Indicates an end to the string */
	buffer[BUFF_SIZE - 1] = '\0';

	/* Writes the number of characters written to the buffer */
	return (write_number(is_negative, d + 1,
			buffer, fags, wid, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * @types: Arguments list
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Acquire width
 * @precision: Specifies precision
 * @size: Specifies size
 *
 * Return: Number of printed characters
 */
int print_binary(va_list types, char buffer[],
		int fags, int wid, int precision, int size)
{
	unsigned int v, y, d, sum;
	unsigned int e[32];
	int count;

	/* Variables initialization */
	v = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	e[0] = v / y;
	for (d = 1; d < 32; d++)
	{
		y /= 2;
		e[d] = (v / y) % 2;
	}

	/* Adds the bits and iterate through the array */
	for (d = 0, sum = 0, count = 0; d < 32; d++)
	{
		sum += e[d];
		if (sum || d == 31)
		{
			/* Prints a 0 or a 1 where needed */
			char z = '0' + e[d];

			/* Writes char to stdout */
			write(1, &z, 1);
			count++;
		}
	}
	/* Return the number of printed characters */
	return (count);
}
