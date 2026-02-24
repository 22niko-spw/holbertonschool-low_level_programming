#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - Point d'entrée
 *
 * Description: Affiche l'alphabet en minuscules.
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
	char letter;

	for (letter = 'z' ; letter >= 'a' ; letter--)
	{
		putchar (letter);
	}
	putchar('\n');

	return (0);
}
