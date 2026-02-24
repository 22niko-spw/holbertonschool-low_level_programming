#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - Affiche tous les chiffres de 0 à 9
 * Description : Utilise uniquement putchar, sans variable de type char.
 * Return: Toujours 0
 */
int main(void)
{
		int n;

	for (n = 0; n <= 9; n++)
	{
		putchar(n + '0');

		if (n < 9)
		{
			putchar (',');
			putchar (' ');
		}
	}
	putchar('\n');
	return (0);
}
