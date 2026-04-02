#include "hash_tables.h"

/**
 * hash_djb2 - Fonction de hachage implémentant l'algorithme djb2
 * @str: La chaîne de caractères à hacher
 *
 * Return: La valeur de hachage calculée
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return (hash);
}
