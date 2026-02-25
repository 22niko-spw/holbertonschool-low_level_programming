#include "main.h"

/**
 * print_triangle - prints a triangle followed by a new line
 * @size: the size of the triangle
 */
void print_triangle(int size)
{
	int row, col;

	if (size <= 0)
	{
		_putchar('\n');
	}
	else
	{
		for (row = 1; row <= size; row++)
		{
			for (col = 1; col <= row; col++)
			{
				_putchar('#');
			}
			_putchar('\n');
		}
	}
}
