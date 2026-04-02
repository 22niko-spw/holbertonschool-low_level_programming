#include "hash_tables.h"

/**
 * key_index - Donne l'index d'une clé dans le tableau de la table de hachage
 * @key: La clé dont on veut l'index
 * @size: La taille du tableau de la table de hachage
 *
 * Return: L'index où la paire clé/valeur doit être stockée
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
