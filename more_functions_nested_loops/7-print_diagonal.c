#include "main.h"

/**
 * print_diagonal - Draws a diagonal line on the terminal.
 * @n: The number of times the character \ should be printed.
 *
 * Description: Uses _putchar to print spaces and backslashes.
 */
void print_diagonal(int n)
{
	int row, space;

	if (n <= 0)
	{
		_putchar('\n');
	}
	else
	{
		for (row = 0; row < n; row++)
		{
			for (space = 0; space < row; space++)
			{
				_putchar(' ');
			}

			_putchar('\\');
			_putchar('\n');
		}
	}
}
