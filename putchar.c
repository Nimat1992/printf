#include <unistd.h>

/**
 * _putchur - accepts a char and returns it to the stdout
 * @u: char to be returned
 * Return: 0(Success)
 */
int _putchur(char u)
{
        return (write(1, &u, 1));
}
