#include <stdio.h>
#include "main.h"

/**
 * print_chessboard - Prints the chessboard.
 * @a: Pointer to an array of 8 characters (the board).
 *
 * Return: void
 */
void print_chessboard(char (*a)[8])
{
	int row, col;

	for (row = 0; row < 8; row++)
	{
		for (col = 0; col < 8; col++)
		{
			/* Accessing the element at [row][col] */
			putchar(a[row][col]);
		}
		/* Print a newline after each row */
		putchar('\n');
	}
}
