#include "main.h"

/**
 * rev_string - inverse une chaîne de caractères en mémoire.
 * @s: le pointeur vers la chaîne à modifier.
 *
 * Return: void.
 */
void rev_string(char *s)
{
	int i = 0;
	int j = 0;
	char temp;

	/* 1. Trouver la longueur de la chaîne */
	while (s[j] != '\0')
	{
		j++;
	}
	j--; /* On se place sur le dernier caractère (avant le '\0') */

	/* 2. Échanger les caractères des extrémités vers le milieu */
	while (i < j)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
}
