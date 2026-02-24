#include "main.h"
/**
 * print_last_digit - Affiche le dernier chiffre d'un nombre.
 * @n: Le nombre en question.
 *
 * Return: La valeur du dernier chiffre.
 */

int print_last_digit(int n)
{
	int last;

	last = n % 10;
	if (last < 0)
	{
		last = -last;
	}

	_putchar(last + '0');
	return (last);

}
