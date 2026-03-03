#include "main.h"

/**
 * _strcat - Concatène deux chaînes de caractères.
 * @dest: La chaîne de destination (doit avoir assez d'espace).
 * @src: La chaîne source à ajouter à la fin de dest.
 *
 * Description : Cette fonction ajoute src à la fin de dest en écrasant
 * l'octet nul (\0) à la fin de dest, puis ajoute un nouvel octet nul.
 *
 * Return: Un pointeur vers la chaîne résultante dest.
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	/* 1. Trouver la fin de la chaîne dest (l'index de '\0') */
	while (dest[i] != '\0')
	{
		i++;
	}

	/* 2. Copier src dans dest à partir de cet index */
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/* 3. Ajouter le caractère de fin de chaîne final */
	dest[i] = '\0';

	return (dest);
}
