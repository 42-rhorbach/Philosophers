/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_basic.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:41:11 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/11/14 16:12:25 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

/**
 * Calculates the length of a string
 * @param ptr The string to measure
 * @returns The number characters in the string
 */
static size_t	ph_strlen(const char *ptr)
{
	size_t	counter;

	counter = 0;
	while (ptr[counter] != '\0')
		counter++;
	return (counter);
}

/**
 * Writes a string to a filedescriptor
 * @param s String to write
 * @param fd Filedescriptor to write to
 * @returns Number of bytes written, -1 on error
 */
static ssize_t	ph_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ph_strlen(s)));
}

/**
 * Writes a char to a filedescriptor
 * @param c Char to write
 * @param fd Filedescriptor to write to
 * @returns Number of bytes written, -1 on error
 */
static ssize_t	ph_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
 * Writes a string and a newline to a filedescriptor
 * @param s String to write
 * @param fd Filedescriptor to write to
 * @returns Number of bytes written, -1 on error
 */
ssize_t	ph_putendl_fd(char *s, int fd)
{
	ssize_t	count;

	count = ph_putstr_fd(s, fd);
	if (count < 0)
		return (-1);
	if (ph_putchar_fd('\n', fd) < 0)
		return (-1);
	return (count + 1);
}

/**
 * Checks whether the arg is a digit
 * @param arg Char to be evaluated
 * @returns 1 if character was a digit, 0 if not
 */
int	ph_isdigit(int arg)
{
	return (arg >= '0' && arg <= '9');
}
