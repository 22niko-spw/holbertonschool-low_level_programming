#include "main.h"

/**
 * times_table - Affiche la table de 9 avec un alignement propre.
 */
void times_table(void)
{
	int i, j, res;

	for (i = 0; i <= 9; i++)
	{
		for (j = 0; j <= 9; j++)
		{
			res = i * j;

			if (j == 0)
			{
				_putchar('0');
			}
			else
			{
				_putchar(',');
				_putchar(' ');
				if (res < 10)
					_putchar(' ');
				if (res >= 10)
					_putchar((res / 10) + '0');
				_putchar((res % 10) + '0');
			}
		}
		_putchar('\n');
	}
}
