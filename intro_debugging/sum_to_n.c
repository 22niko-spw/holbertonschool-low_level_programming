#include <stdio.h>
/**
 * sum_to_n - Calcule la somme de 1 à n.
 * @n: Le nombre limite.
 *
 * Return: La somme calculée.
 */
int sum_to_n(int n)
{
	int i;
	int sum = 0;

	for (i = 1; i <= n; i++)
	{
		sum += i;
	}

	return (sum);
}

/* -- DO NOT Modify the code below this line -- */
/**
 * main - Point d'entrée du programme.
 *
 * Return: Toujours 0 (Succès).
 */

int main(void)
{
	printf("%d\n", sum_to_n(10));
	return (0);
}
