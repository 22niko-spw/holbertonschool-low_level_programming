#include <stdlib.h>
#include <string.h>
#include "lists.h"

/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to the pointer of the head of the list
 * @str: string to store in the new node
 *
 * Return: address of the new element, or NULL if it failed
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *node;
	list_t *cur;
	unsigned int i;

	node = malloc(sizeof(list_t));
	if (node == NULL)
		return (NULL);
	node->str = strdup(str);
	if (node->str == NULL)
	{
		free(node);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0')
		i++;
	node->len = i;
	node->next = NULL;
	if (*head == NULL)
	{
		*head = node;
		return (node);
	}
	cur = *head;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node;
	return (node);
}
