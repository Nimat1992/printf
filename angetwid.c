#include "main.h"
#include <ctype.h>

/**
 * get_width - Calculates the width used for printing
 * @format: Format string to print the arguments
 * @i: Pointer to the current index in the format string
 * @list:  List of arguments
 *
 * Return: Width
 */

int get_width(const char *format, int *i, va_list list)
{
	int cur_i;
	int width = 0;

	for (cur_i = *i + 1; format[cur_i] != '\0' && format[cur_i] != '*'; cur_i++)
	{
		if (isdigit(format[cur_i]))
		{
			width *= 10;
			width += format[cur_i] - '0';
		} else
		{
			break;
		}
	}

	if (format[cur_i] == '*')
	{
		cur_i++;
		width = va_arg(list, int);
	}

	*i = cur_i;

	return (width);
}

