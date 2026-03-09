#include "main.h"
#include <string.h>
#include <stdlib.h>
/**
 * _strdup - Dupliquer une string
 * @str: string
 *
 * Return: return new
 */
char *_strdup(char *str)
{
	unsigned int len;
	char *new;

	if (str == NULL)
		return (NULL);

	len = strlen(str);

	new = malloc(sizeof(char) * (len + 1));

	if (new == NULL)
		return (NULL);

	strcpy(new, str);

	return (new);


}
