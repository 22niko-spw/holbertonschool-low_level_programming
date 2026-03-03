#include "main.h"

/**
 * cap_string - Met en majuscule la première lettre de chaque mot.
 * @str: La chaîne de caractères à modifier.
 *
 * Return: Un pointeur vers la chaîne modifiée.
 */
char *cap_string(char *str)
{
	int i = 0;
	int j;
	char sep[] = " \t\n,;.!?\"(){}";

	while (str[i] != '\0')
	{
		/* Cas particulier : le tout premier caractère de la chaîne */
		if (i == 0 && (str[i] >= 'a' && str[i] <= 'z'))
		{
			str[i] -= 32;
		}

		/* Parcourir la liste des séparateurs */
		for (j = 0; sep[j] != '\0'; j++)
		{
			/* Si le caractère précédent est un séparateur */
			if (str[i] == sep[j])
			{
				/* Et si le caractère actuel est une minuscule */
				if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
				{
					str[i + 1] -= 32;
				}
			}
		}
		i++;
	}

	return (str);
}
