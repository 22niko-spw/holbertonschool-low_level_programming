#include "lists.h"
#include <stdlib.h>

/**
 * insert_dnodeint_at_index - inserts a new node at a given position
 * @h: pointer to the pointer of the head of the list
 * @idx: index where the new node should be added
 * @n: integer value for the new node
 *
 * Return: address of the new node, or NULL if it failed
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *new;
	dlistint_t *tmp;
	unsigned int i;

	if (idx == 0)
		return (add_dnodeint(h, n));
	tmp = *h;
	i = 0;
	while (tmp != NULL)
	{
		if (i == idx - 1)
		{
			if (tmp->next == NULL)
				return (add_dnodeint_end(h, n));
			new = malloc(sizeof(dlistint_t));
			if (new == NULL)
				return (NULL);
			new->n = n;
			new->next = tmp->next;
			new->prev = tmp;
			tmp->next->prev = new;
			tmp->next = new;
			return (new);
		}
		i++;
		tmp = tmp->next;
	}
	return (NULL);
}
