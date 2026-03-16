#include "dog.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * new_dog - crée un nouveau chien (allocation dynamique).
 * @name: nom du chien.
 * @age: âge du chien.
 * @owner: propriétaire du chien.
 *
 * Return: pointeur vers la nouvelle structure dog_t, ou NULL si échec.
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	int i = 0;
	unsigned int size = 0;
	char *namecp;
	char *ownercp;
	dog_t *d = malloc(sizeof(dog_t));

	if (d == NULL)
		return (NULL);
	while (name[size] != '\0')
		size++;
	namecp = malloc((size + 1) * sizeof(char));
	if (namecp == NULL)
		return (NULL);
	while (name[i] != '\0')
	{
		namecp[i] = name[i];
		i++;
	}
	namecp[i] = '\0';
	d->name = namecp;
	size = 0;
	i = 0;
	while (owner[size] != '\0')
		size++;
	ownercp = malloc((size + 1) * sizeof(char));
	if (ownercp == NULL)
	{
		free(namecp);
		free(d);
		return (NULL);
	}
	while (owner[i] != '\0')
	{
		ownercp[i] = owner[i];
		i++;
	}
	ownercp[i] = '\0';
	d->owner = ownercp;
	d->age = age;
	return (d);
}
