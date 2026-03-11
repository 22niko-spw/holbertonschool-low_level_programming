#include "main.h"
/**
 * _calloc - allocate memory
 * @nmemb: numéro de membre
 * @size: taille
 *
 * Return: ptr
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{

	char *ptr;
	unsigned int i;

	i = 0;

	if (nmemb == 0)
		return (NULL);

	if (size == 0)
		return (NULL);

	ptr = malloc(nmemb * size);

	if (ptr == NULL)
		return (NULL);

	while (i < nmemb * size)
		{
		ptr[i] = 0;
		i++;
		}

	return (ptr);
}
