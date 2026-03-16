#include "dog.h"
#include <stdlib.h>
/**
 * free_dog - libère la mémoire allouée pour un chien.
 * @d: pointeur vers la structure dog_t à libérer.
 *
 * Description: Cette fonction libère la mémoire du nom, du propriétaire,
 * puis de la structure elle-même.
 */
void free_dog(dog_t *d)
{
	if (d == NULL)
		return;

	free(d->owner);
	free(d->name);
	free(d);
}
