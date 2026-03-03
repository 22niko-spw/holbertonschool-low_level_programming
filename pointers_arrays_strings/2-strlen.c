#include "main.h"

/**
 * _strlen - renvoie la longueur d'une chaîne de caractères.
 * @s: le pointeur vers la chaîne à analyser.
 *
 * Return: la longueur de la chaîne sous forme d'entier.
 */
int _strlen(char *s)
{
	int longueur = 0;

	while (s[longueur] != '\0')
	{
		longueur++;
	}

	return (longueur);
}

