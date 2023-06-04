#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Format string
 * @d: Pointer to the current index in the format string
 *
 * Return: Flags
 */
int get_flags(const char *format, int *d)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int m, current_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' '};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE};

	current_i = *d + 1;
	for (m = 0; FLAGS_CH[m] != '\0'; m++)
	{
		if (format[current_i] == FLAGS_CH[m])
		{
			flags |= FLAGS_ARR[m];
			break;
		}
	}

	*d = current_i;

	return (flags);
}

