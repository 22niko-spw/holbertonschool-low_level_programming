#include "main.h"
#include <stddef.h>
/**
 * malloc_checked - allocates memory using malloc
 * @b: number of bytes to allocate
 *
 * Return: pointer to the allocated memory, or exit with 98 if malloc fails
 */
void *malloc_checked(unsigned int b)
{
	void *m;

	m = malloc(b);
	if (m == NULL)
	{
		exit(98);
	}
	return (m);
}
