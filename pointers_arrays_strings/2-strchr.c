#include "main.h"
#include <stdio.h>
/**
 * _strchr - localise un caractère dans une chaîne
 * @s: la chaîne de caractères à parcourir
 * @c: le caractère à rechercher
 *
 * Return: un pointeur vers la première occurrence de c,
 * ou NULL si le caractère n'est pas trouvé.
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	/* On parcourt la chaîne jusqu'au caractère nul '\0' inclus */
	while (s[i])
	{
		if (s[i] == c)
		{
			/* On retourne l'adresse de l'endroit où on a trouvé c */
			return (s + i);
		}
		/* Si on vient de tester le caractère de fin de chaîne, on s'arrête */
		if (s[i] == '\0')
			break;
		i++;
	}

	return (NULL);
}
