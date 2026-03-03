#include "main.h"

/**
 * reverse_array - Inverse le contenu d'un tableau d'entiers.
 * @a: Le tableau d'entiers à inverser.
 * @n: Le nombre d'éléments dans le tableau.
 *
 * Return: void (rien).
 */
void reverse_array(int *a, int n)
{
	int i;
	int temp;

	/* On parcourt seulement jusqu'à la moitié du tableau */
	/* car au-delà, on ré-inverserait ce qu'on vient de faire ! */
	for (i = 0; i < n / 2; i++)
	{
		/* Stockage temporaire de l'élément actuel */
		temp = a[i];

		/* On remplace l'élément actuel par son opposé à la fin */
		a[i] = a[n - 1 - i];

		/* On place la valeur stockée à la fin */
		a[n - 1 - i] = temp;
	}
}
