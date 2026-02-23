#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * main - Point d'entrée
 *
 * Description: Affiche l'alphabet en minuscules et majuscules.
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
	char letter;

	for (letter = 'a' ; letter <= 'z' ; letter++)
	{
		putchar (letter);
	}
	for (letter = 'A' ; letter <= 'Z' ; letter++)
	{
		putchar (letter);
	}
	putchar('\n');


	return (0);
}
