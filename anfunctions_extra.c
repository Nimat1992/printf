#include "main.h"

/**
 * print_pointer - Displays the content stored in a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
                  int fags, int wid, int precision, int size)
{
    char extra_c = 0, padd = ' ';
    int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
    unsigned long num_addrs;
    char map_to[] = "0123456789abcdef";
    void *addrs = va_arg(types, void *);

    UNUSED(wid);
    UNUSED(size);

    if (addrs == NULL)
        return (write(1, "(nil)", 5));

    buffer[BUFF_SIZE - 1] = '\0';
    UNUSED(precision);

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
        extra_c = '+', length++;
    else if (fags & F_SPACE)
        extra_c = ' ', length++;

    ind++;

    /*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
    return (write_pointer(buffer, ind, length,
                          wid, fags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - Outputs hexadecimal representation
 * of ASCII codes for char not printable.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
                        int fags, int wid, int precision, int size)
{
    int d = 0, offset = 0;
    char *str = va_arg(types, char *);

    UNUSED(fags);
    UNUSED(wid);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        return (write(1, "(null)", 6));

    while (str[d] != '\0')
    {
        if (is_printable(str[d]))
            buffer[d + offset] = str[d];
        else
offset += append_hexa_code(buffer, d + offset, &str[d]);

        d++;
    }

    buffer[d + offset] = '\0';

    return (write(1, buffer, d + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int print_reverse(va_list types, char buffer[],
                  int fags, int wid, int precision, int size)
{
    char *str;
    int d, count = 0;

    UNUSED(buffer);
    UNUSED(fags);
    UNUSED(wid);
    UNUSED(size);

    str = va_arg(types, char *);

    if (str == NULL)
    {
        UNUSED(precision);

        str = ")Null(";
    }
    for (d = 0; str[d]; d++)
        ;

    for (d = d - 1; d >= 0; d--)
    {
        char z = str[d];

        write(1, &z, 1);
        count++;
    }
    return (count);
}

/**
 * print_rot13string - Encode a string using ROT13 cipher and display result.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @fags: Calculates active flags
 * @wid: Width specifier
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of chars printed
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
