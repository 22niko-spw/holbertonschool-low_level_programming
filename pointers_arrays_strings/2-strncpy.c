#include "main.h"

/**
 * _strncpy - Copie une chaîne de caractères.
 * @dest: Le tampon de destination.
 * @src: La chaîne source à copier.
 * @n: Le nombre maximal d'octets à copier.
 *
 * Return: Un pointeur vers la chaîne résultante dest.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j = 0;

	/* 1. Copier src vers dest jusqu'à n ou la fin de src */
	while (j < n && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
	}

	/* 2. Si src est plus courte que n, remplir le reste avec des '\0' */
	while (j < n)
	{
		dest[j] = '\0';
		j++;
	}

	return (dest);
}
