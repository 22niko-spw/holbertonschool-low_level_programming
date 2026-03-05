#include "main.h"
/**
 * swap_int - inverse la valeur de deux entiers.
 * @a: pointeur vers le premier entier.
 * @b: pointeur vers le second entier.
 *
 * Return: void (ne retourne rien).
 */
void swap_int(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
