#include "main.h"

/**
 * _strncat - Concatène deux chaînes avec une limite de n octets.
 * @dest: La chaîne de destination.
 * @src: La chaîne source à ajouter.
 * @n: Le nombre maximum d'octets à copier depuis src.
 *
 * Return: Un pointeur vers la chaîne résultante dest.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	/* 1. Aller à la fin de la chaîne dest */
	while (dest[i] != '\0')
	{
		i++;
	}

	/* 2. Copier au plus n octets de src vers dest */
	/* La boucle s'arrête si on atteint '\0' OU si j atteint n */
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/* 3. Ajouter TOUJOURS un caractère nul de fin de chaîne */
	dest[i] = '\0';

	return (dest);
}
