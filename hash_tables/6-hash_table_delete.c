#include <stdlib.h>
#include "hash_tables.h"

/**
 * hash_table_delete - Supprime une table de hachage
 * @ht: La table de hachage à supprimer
 *
 * Description: Libère tous les nœuds, leurs clés et valeurs,
 * le tableau interne, puis la structure principale.
 */
void hash_table_delete(hash_table_t *ht)
{
	hash_node_t *node;
	hash_node_t *tmp;
	unsigned long int i;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node != NULL)
		{
			tmp = node->next;
			free(node->key);
			free(node->value);
			free(node);
			node = tmp;
		}
	}

	free(ht->array);
	free(ht);
}
