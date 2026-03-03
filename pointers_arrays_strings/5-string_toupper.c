#include "main.h"

/**
 * string_toupper - Change toutes les minuscules d'une chaîne en majuscules.
 * @str: La chaîne de caractères à modifier.
 *
 * Return: Un pointeur vers la chaîne modifiée.
 */
char *string_toupper(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		/* Vérifie si le caractère est une minuscule (entre 'a' et 'z') */
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			/* On soustrait 32 pour obtenir la majuscule correspondante */
			str[i] = str[i] - 32;
		}
		i++;
	}

	return (str);
}
