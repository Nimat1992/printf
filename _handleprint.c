#include "main.h"

/**
 * handle_print - This will handle prints based on the given specified format.
 * @fmt: The format string.
 * @ind: The index of the current format specifier.
 * @list: The va_list of arguments.
 * @buffer: The buffer to store the printed characters.
 * @flags: The printing flags.
 * @width: The width.
 * @precision: The precision.
 * @size: The size modifier.
 *
 * Return: 1 or 2.
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{
	int m, printd_chars = -1;
	fmt_t fmt_types[] = {
	{'c', print_char}, {'s', print_string}, {'%', print_percent},
	{'i', print_int}, {'d', print_int}, {'b', print_binary},
	{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
	{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
	{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	/* Checking if the format character is valid. */
	if (fmt[*ind] == '\0')
		return (-1);

	/* Find the corresponding function to print the argument. */
	for (m = 0; fmt_types[m].fmt != '\0'; m++)
	{
		if (fmt[*ind] == fmt_types[m].fmt)
		{
			printd_chars = fmt_types[m].fn(list, buffer,
			flags, width, precision, size);
			break;
		}
	}

	/* If the format character is not valid, print a '%' character. */
	if (fmt_types[m].fmt == '\0')
		printd_chars = write(1, "%%", 1);

	return (printd_chars);
}

