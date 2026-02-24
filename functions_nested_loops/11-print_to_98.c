#include <stdio.h>
#include "main.h"

/**
 * print_to_98 - Affiche tous les nombres de n à 98.
 * @n: Le nombre de départ.
 */
void print_to_98(int n)
{

	if (n <= 98)
	{
		for (; n <= 98; n++)
		{
			if (n == 98)
				printf("%d", n);
			else
				printf("%d, ", n);
		}
	}

	else
	{
		for (; n >= 98; n--)
		{
			if (n == 98)
				printf("%d", n);
			else
				printf("%d, ", n);
		}
	}
	printf("\n");
}
