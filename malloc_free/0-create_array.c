#include "main.h"
#include <stdlib.h>
/**
 * create_array - créer un tableau de caractères
 * @size: la taille du tableau
 * @c: caractère
 *
 * Return: tab
 */
char *create_array(unsigned int size, char c)
{
	char *tab;
	unsigned int i;

	i = 0;

	if (size == 0)
		return (NULL);

	tab = malloc(sizeof(char) * size);

	if (tab == NULL)
		return (NULL);

	while (i < size)
	{
		tab[i] = c;
		i++;
	}


	return (tab);
}
