/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ph_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rhorbach <rhorbach@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/30 17:17:13 by rhorbach      #+#    #+#                 */
/*   Updated: 2023/12/01 15:26:08 by rhorbach      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

/**
 * Fills a memory block with a value
 * @param ptr A pointer to the memory block to be filled
 * @param c The byte-value to fill with
 * @param n Amount of bytes to fill
 */
static void	*ph_memset(void *ptr, int c, size_t n)
{
	unsigned long	counter;
	unsigned char	*str;

	str = ptr;
	counter = 0;
	while (counter != n)
	{
		str[counter] = c;
		counter++;
	}
	return (str);
}

/**
 * Fills a memory block with zeroes
 * @param ptr A pointer to the memory block to be filled
 * @param n Amount of bytes to fill
 */
static void	ph_bzero(void *ptr, size_t n)
{
	ph_memset(ptr, '\0', n);
}

/**
 * Allocates memory and fills it with zeroes
 * @param count Number of elements to allocate
 * @param size The size in bytes of a single element
 * @returns A pointer to the allocated memory, NULL on error
 */
void	*ph_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && SIZE_MAX / count < size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr != NULL)
		ph_bzero(ptr, count * size);
	return (ptr);
}
