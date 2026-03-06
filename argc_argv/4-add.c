#include <stdio.h>
#include <stdlib.h>

/**
 * main - Programme qui additionne des nombres positifs.
 * @argc: Le nombre de mots tapés dans le terminal.
 * @argv: La liste des mots tapés.
 *
 * Return: 0 si tout est bon, 1 s'il y a une erreur.
 */
int main(int argc, char *argv[])
{
	int i, j;
	int somme = 0;

	if (argc == 1)
	{
		printf("0\n");
		return (0);
	}
	for (i = 1; i < argc; i++)
	{
		for (j = 0; argv[i][j] != '\0'; j++)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\n");
				return (1);
			}
		}
		somme = somme + atoi(argv[i]);
	}
	printf("%d\n", somme);

	return (0);
}
