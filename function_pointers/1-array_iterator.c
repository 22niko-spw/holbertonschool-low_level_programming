#include "function_pointers.h"
#include <stddef.h>
/**
 * array_iterator - execute a fonction given
 * @array: tableau d'entiers
 * @size: taille du tableau
 * @action: un pointeur vers la fonction à appliquer
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
size_t i = 0;

while (i < size)
{
	action(array[i]);
	i++;
}
}
