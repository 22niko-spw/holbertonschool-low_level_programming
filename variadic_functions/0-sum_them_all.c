#include <stdarg.h>
#include "variadic_functions.h"
/**
 * sum_them_all - returns the sum of all its parameters
 * @n: number of parameters
 * @...: variable list of integers to sum
 *
 * Return: sum of all parameters, or 0 if n is 0
 */

int sum_them_all(const unsigned int n, ...)
{
	va_list ap;
	int total;
	unsigned int i;

	if (n == 0)
		return (0);

	va_start(ap, n);
	total = 0;
	for (i = 0; i < n; i++)
		total += va_arg(ap, int);
	va_end(ap);
	return (total);
}
