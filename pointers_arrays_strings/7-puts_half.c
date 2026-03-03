#include "main.h"

/**
 * puts_half - imprime la seconde moitié d'une chaîne.
 * @str: la chaîne de caractères à traiter.
 */
void puts_half(char *str)
{
	int len = 0;
	int n, i;

	/* 1. Calculer la longueur totale */
	while (str[len] != '\0')
	{
		len++;
	}

	/* 2. Calculer le point de départ selon la règle de l'énoncé */
	if (len % 2 == 0)
	{
		n = len / 2;
	}
	else
	{
		/* Pour les impairs, on calcule n = (len + 1) / 2 */
		/* Le point de départ est : len - n */
		n = (len - 1) / 2;
		n++;
	}

	/* 3. Imprimer à partir de l'indice n jusqu'à la fin */
	for (i = n; i < len; i++)
	{
		_putchar(str[i]);
	}

	_putchar('\n');
}
