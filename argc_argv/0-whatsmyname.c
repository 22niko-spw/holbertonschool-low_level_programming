#include <stdio.h>

/**
 * main - Prints the name of the program.
 * @argc: The number of arguments (unused).
 * @argv: An array of strings containing the arguments.
 *
 * Return: Always 0 (Success).
 */
int main(int argc, char **argv)
{
	(void)argc;

	printf("%s\n", argv[0]);

	return (0);
}
