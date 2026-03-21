#include "main.h"

/**
 * check_divisor - checks if n has a divisor between divisor and sqrt(n)
 * @n: the number to check
 * @divisor: current divisor candidate
 *
 * Return: 1 if n is prime, 0 if not
 */
int check_divisor(int n, int divisor)
{
	if (divisor * divisor > n)
		return (1);
	if (n % divisor == 0)
		return (0);
	return (check_divisor(n, divisor + 1));
}

/**
 * is_prime_number - returns 1 if n is prime, otherwise 0
 * @n: the integer to check
 *
 * Return: 1 if prime, 0 otherwise
 */
int is_prime_number(int n)
{
	if (n <= 1)
		return (0);
	return (check_divisor(n, 2));
}
