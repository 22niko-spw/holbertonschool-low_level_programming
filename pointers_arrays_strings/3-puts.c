#include "main.h"

/**
 * _puts - imprime une chaîne de caractères suivie d'une nouvelle ligne.
 * @str: le pointeur vers la chaîne à afficher.
 *
 * Return: void (rien).
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}

	_putchar('\n');
}
