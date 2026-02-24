#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - Point d'entrée
 *
 * Description: Affiche tous nombres de la base 16.
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
	int n;
	char l;

	for (n = '0'; n <= '9'; n++)
	{
		putchar(n);
	}
	for (l = 'a'; l <= 'f'; l++)
	{
		putchar(l);
	}
	putchar('\n');

	return (0);
}