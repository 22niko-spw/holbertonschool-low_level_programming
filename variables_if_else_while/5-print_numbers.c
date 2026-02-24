#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - Point d'entrée
 *
 * Description: Affiche tous les chiffre de la base 10.
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
	int number;

	for (number = 0 ; number <= 9 ; number++)
{
	putchar(number + '0');
}

	putchar('\n');

return (0);

}
