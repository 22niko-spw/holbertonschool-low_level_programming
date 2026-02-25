#include "main.h"
/**
 * print_numbers - affiche les chiffres de 0 à 9 suivis d'une nouvelle ligne.
 *
 * Utilise exactement deux appels à _putchar.
 */
void print_numbers(void)
{
	int n;

	for (n = 0; n <= 9; n++)
	{
		_putchar (n + '0');
	}

		_putchar ('\n');
}
