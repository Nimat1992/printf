#include "main.h"

/**
 * handle_write_char - Prints a character
 * @c: Character to print.
 * @buffer: Buffer to store the character.
 * @fags: Flags that control how the character is printed.
 * @wid: Width of the character.
 *
 * Return: The number of characters printed.
 */
int handle_write_char(char c, char *buffer, int fags, int wid)
{
	int d = 0;
	char padd = ' ';

	if (fags & F_ZERO)
		padd = '0';

	buffer[d++] = c;

	if (wid > 1)
	{
		for (; d < wid; d++)
			buffer[d] = padd;
	}

	int n = write(1, buffer, wid);

	return (n);
}

/**
 * write_number - Writes a number to a buffer
 * @is_negative: Indicates if the number is negative
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @fags: Flags
 * @wid: Width of the number
 * @precision: Precision of the number
 *
 * Return: The number of characters written to the buffer.
 */
int write_number(int is_negative, int ind, char *buffer,
		int fags, int wid, int num, int precision)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ';

	UNUSED(precision);

	if ((fags & F_ZERO) && !(fags & F_MINUS))
		padd = '0';

	if (is_negative)
	{
		buffer[ind++] = '-';
		length--;
	}
	else if (fags & F_PLUS)
	{
		buffer[ind++] = '+';
		length--;
	}
	else if (fags & F_SPACE)
	{
		buffer[ind++] = ' ';
		length--;
	}

	if (wid > length)
	{
		for (int d = 0; d < wid - length; d++)
			buffer[ind + d] = padd;
	}

	for (int d = length - 1; d >= 0; d--)
	{
		buffer[ind + d] = (char)(num % 10 + '0');
		num /= 10;
	}

	int n = write(1, buffer, ind);

	return (n);
}

/**
 * write_num - Writes a number to a buffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @fags: Flags
 * @wid: Width of the number
 * @precision: Precision of the number
 * @length: Number length
 * @padd: Padding char
 * @extra_c: Extra char
 *
 * Return: The number of printed chars.
 */
int write_num(int ind, char *buffer, int fags, int precision, int wid,
		int length, int num, char padd, char extra_c)
{
	int d;

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && wid == 0)
		return (0);
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if (extra_c != 0)
		length++;
	if (wid > length)
	{
		for (d = 0; d < wid - length; d++)
			buffer[ind++] = padd;
	}
	if (fags & F_MINUS)
	{
		if (extra_c != 0)
			buffer[ind - 1] = extra_c;
		buffer[ind - 2] = '-';
	}
	else if (fags & F_PLUS)
	{
		if (extra_c != 0)
			buffer[ind - 1] = extra_c;
		buffer[ind - 1] = '+';
	}
	else if (fags & F_SPACE)
	{
		if (extra_c != 0)
			buffer[ind - 1] = extra_c;
		buffer[ind - 1] = ' ';
	}
	for (d = 0; d < length; d++)
		buffer[ind - d - 1] = buffer[ind - length + d];
	return (write(1, buffer, ind));
}

/**
 * write_unsigned - Writes an unsigned number to a buffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @fags: Flags
 * @wid: Width of the number
 * @precision: Precision of the number
 *
 * Return: The number of characters written to the buffer.
 */
int write_unsigned(int ind, char *buffer, int fags, int wid, int precision)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ';

	UNUSED(precision);

	if ((fags & F_ZERO) && !(fags & F_MINUS))
		padd = '0';

	if (wid > length)
	{
		for (int d = 0; d < wid - length; d++)
			buffer[ind + d] = padd;
	}

	int n = write(1, buffer + ind, length);

	return (n);
}

/**
 * write_pointer - Writing an address of a memory to a buffer
 * @buffer: Buffer
 * @ind: Index at which the number starts on the buffer
 * @length: Length of the number
 * @wid: Width of the number
 * @fags: Flags
 * @padd: Padding character
 * @extra_c: Extra character
 *
 * Return: The number of characters written to the buffer.
 */
int write_pointer(char *buffer, int ind, int length, int wid,
		int fags, int num, char padd, char extra_c)
{
	int d;

	if (wid > length)
	{
		for (d = 0; d < wid - length; d++)
			buffer[ind + d] = padd;
	}

	buffer[ind++] = 'x';
	buffer[ind++] = '0';

	for (d = 0; d < length; d++)
	{
		buffer[ind++] = (char)(num % 16 + '0');
		num /= 16;
	}

	if (num < 0)
		buffer[ind++] = '-';

	int n = write(1, buffer, ind);

	return (n);
}
