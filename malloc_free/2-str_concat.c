#include "main.h"
#include <string.h>
#include <stdlib.h>

char *str_concat(char *s1, char *s2)
{
	unsigned int len;
	char *tab;

	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	len = strlen(s1) + strlen(s2) + 1;

	tab = malloc(sizeof(char) * len);

	if (tab == NULL)
		return (NULL);

	strcpy(tab, s1);
	strcat(tab, s2);

	return (tab);
}
