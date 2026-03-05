#include "main.h"

/**
 * print_rev - imprime une chaîne à l'envers, suivie d'une nouvelle ligne.
 * @s: la chaîne à imprimer.
 *
 * Return: void.
 */
void print_rev(char *s)
{
	int i;
	int longueur = 0;

	while (s[longueur] != '\0')
	{
		longueur++;
	}

	i = longueur - 1;
	while (i >= 0)
	{
		_putchar(s[i]);
		i--;
	}

	_putchar('\n');
}
