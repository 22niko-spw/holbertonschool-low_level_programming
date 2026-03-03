#include "main.h"

/**
 * puts2 - imprime un caractère sur deux d'une chaîne.
 * @str: la chaîne de caractères à traiter.
 *
 * Return: void.
 */
void puts2(char *str)
{
	int i = 0;

	/* On parcourt la chaîne jusqu'au caractère nul */
	while (str[i] != '\0')
	{
		/* On affiche le caractère à l'indice actuel */
		_putchar(str[i]);

		/* On avance de 2 pour sauter le caractère suivant */
		i += 2;

		/* Sécurité : si on arrive sur le \0 après l'incrément, on sort */
		if (str[i - 1] == '\0')
			break;
	}

	_putchar('\n');
}
