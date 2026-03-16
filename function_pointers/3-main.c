#include "3-calc.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * main - Effectue des opérations simples.
 * @argc: Nombre d'arguments.
 * @argv: Tableau des arguments.
 *
 * Return: 0 en cas de succès.
 */
int main(int argc, char *argv[])
{
	int num1;
	int num2;
	int (*f)(int, int);

	if (argc != 4)
	{
		printf("Error\n");
		exit(98);
	}

	f = get_op_func(argv[2]);
	if (f == NULL)
	{
		printf("Error\n");
		exit(99);
	}

	num1 = atoi(argv[1]);
	num2 = atoi(argv[3]);
	if ((argv[2][0] == '/' || argv[2][0] == '%') && num2 == 0)
	{
		printf("Error\n");
		exit(100);
	}
	printf("%d\n", f(num1, num2));
	return (0);
}
