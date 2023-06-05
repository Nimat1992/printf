#include "main.h"

/**
 * get_size - Determines the size of the argument to be converted
 * @format: Format string to print the arguments
 * @d: Pointer to the current index in the format string
 *
 * Return: Size of the argument
 */

int get_size(const char *format, int *d)
{
	int curren_i = *d + 1;
	int size = 0;

	/* Check if the next character is 'l' or 'h' */
	if (format[curren_i] == 'l')
	{
		size = S_LONG;
	}
	else if (format[curren_i] == 'h')
	{
		size = S_SHORT;
	}

	/* If no size was specified, return 0 */
	if (size == 0)
	{
		*d = curren_i - 1;
		return (0);
	}

	/* Otherwise, update the index and return the size */
	*d = curren_i;
	return (size);
}

