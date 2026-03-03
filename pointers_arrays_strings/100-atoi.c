#include "main.h"

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The integer value of the converted string.
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	unsigned int res = 0;

	/* Étape 1 : Ignorer tout ce qui n'est pas un chiffre et gérer le signe */
	while (s[i] != '\0' && (s[i] < '0' || s[i] > '9'))
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}

	/* Étape 2 : Convertir les chiffres consécutifs */
	while (s[i] >= '0' && s[i] <= '9')
	{
		/* Utilisation de unsigned int pour éviter l'overflow pendant le calcul */
		res = (res * 10) + (s[i] - '0');
		i++;
	}

	return (res * sign);
}
