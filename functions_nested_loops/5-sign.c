#include "main.h"
/**
 * print_sign - Imprime le signe d'un nombre.
 * @n: Le nombre à vérifier.
 *
 * Return: 1 si n > 0, 0 si n == 0, -1 si n < 0.
 */

int print_sign(int n)
{
	if (n > 0)
	{
		_putchar('+');
		return (1);
	}
	else if (n == 0)
	{
		_putchar('0');
		return (0);
	}
	else
	{
		_putchar('-');
		return (-1);
	}
}
