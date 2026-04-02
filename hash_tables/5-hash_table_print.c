#include <stdio.h>
#include "hash_tables.h"

/**
 * hash_table_print - Affiche la table de hachage
 * @ht: La table de hachage à afficher
 *
 * Description: Affiche les paires clé/valeur dans l'ordre du tableau.
 * Ne fait rien si ht est NULL.
 */
void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *node;
	unsigned long int i;
	int first;

	if (ht == NULL)
		return;

	first = 1;
	printf("{");
	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node != NULL)
		{
			if (!first)
				printf(", ");
			printf("'%s': '%s'", node->key, node->value);
			first = 0;
			node = node->next;
		}
	}
	printf("}\n");
}
