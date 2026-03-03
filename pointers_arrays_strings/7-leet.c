#include "main.h"

/**
 * leet - Encode une chaîne de caractères en 1337.
 * @str: La chaîne à encoder.
 *
 * Return: Un pointeur vers la chaîne modifiée.
 */
char *leet(char *str)
{
	int i = 0;
	int j;
	char letters[] = "aAeEoOtTlL";
	char numbers[] = "4433007711";

	/* Première boucle : parcourt la chaîne de caractères */
	while (str[i] != '\0')
	{
		/* Deuxième boucle : parcourt le dictionnaire de mapping */
		for (j = 0; j < 10; j++)
		{
			/* Le seul IF autorisé : vérifie la correspondance */
			if (str[i] == letters[j])
			{
				str[i] = numbers[j];
			}
		}
		i++;
	}

	return (str);
}
