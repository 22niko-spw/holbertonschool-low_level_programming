#include "main.h"
#include <stdio.h>

/**
 * print_array - Prints n elements of an array of integers.
 * @a: Pointer to the first element of the array.
 * @n: Number of elements to be printed.
 *
 * Return: void.
 */
void print_array(int *a, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%d", a[i]);

		/* Only print comma and space if it's not the last element */
		if (i < n - 1)
		{
			printf(", ");
		}
	}
	printf("\n");
}
