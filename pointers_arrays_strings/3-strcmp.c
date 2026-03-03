#include "main.h"

/**
 * _strcmp - Compare deux chaînes de caractères.
 * @s1: La première chaîne à comparer.
 * @s2: La seconde chaîne à comparer.
 *
 * Return:
 * 0 si les chaînes sont identiques.
 * Un entier négatif si s1 < s2.
 * Un entier positif si s1 > s2.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	/* On parcourt les chaînes tant qu'elles sont identiques */
	/* et qu'on n'a pas atteint la fin de s1 */
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}

	/* On retourne la différence ASCII entre les deux caractères */
	return (s1[i] - s2[i]);
}
