#include "function_pointers.h"
/**
 * int_index - searches for an integer
 * @array: tableau d'entier
 * @size: taille du tableau
 * @cmp: pointeur vers la fonction pour comparer les valeurs
 * Return: index first element for cmp return 0, or -1 if not found
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i = 0;

	if (size <= 0)
		return (-1);

	while (i < size)
	{
		if (cmp(array[i]) != 0)
			return (i);
		i++;
	}

	return (-1);

}
