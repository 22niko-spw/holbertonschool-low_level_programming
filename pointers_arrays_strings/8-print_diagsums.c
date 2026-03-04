#include <stdio.h>
#include "main.h"

/**
 * print_diagsums - Prints the sum of the two diagonals of a square matrix.
 * @a: Pointer to the first element of the matrix (treated as 1D).
 * @size: The width/height of the square matrix.
 */
void print_diagsums(int *a, int size)
{
	int i;
	int sum1 = 0;
	int sum2 = 0;

	for (i = 0; i < size; i++)
	{
		/* Main diagonal: top-left to bottom-right */
		/* Index logic: (row * size) + column */
		/* For main diag, row == column, so (i * size) + i */
		sum1 += a[(i * size) + i];

		/* Anti-diagonal: top-right to bottom-left */
		/* Index logic: (row * size) + (size - 1 - row) */
		sum2 += a[(i * size) + (size - 1 - i)];
	}

	printf("%d, %d\n", sum1, sum2);
}
