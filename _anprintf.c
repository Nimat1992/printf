#include <stdarg.h>
#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - This fxn acts like the standard printf fxn
 * @format: format.
 * Return: The printed chars.
 */

int _printf(const char *format, ...)
{
	int d, printed = 0, prin_chars = 0;
	int fags, wid, precision, size, buff_ind = 0;
	va_list niad;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	return (-1);

	va_start(niad, format);

	for (d = 0; format && format[d] != '\0'; d++)
	{
		if (format[d] != '%')
		buffer[buff_ind++] = format[d];
		if (buff_ind == BUFF_SIZE)
			print_buffer(buffer, &buff_ind);
		/* write(1, &format[i], 1);*/
		prin_chars++;
	}
	
	print_buffer(buffer, &buff_ind);
	fags = get_flags(format, &d);
	wid = get_width(format, &d, niad);
	precision = get_precision(format, &d, niad);
	size = get_size(format, &d);
	++d;
	printed = handle_print(format, &d, niad, buffer, fags, wid, precision, size);
	if (printed == -1)
	{
		return (-1);
	}
	prin_chars += printed;
	print_buffer(buffer, &buff_ind);
	va_end(niad);
	return (prin_chars);
}

/**
 * print_buffer - This will prints the contents of the buffer
 * @buffer: Array of chars
 * @buff_ind: Index of location of next char, reps the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}

