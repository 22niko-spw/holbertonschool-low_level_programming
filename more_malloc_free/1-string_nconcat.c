#include "main.h"

/**
 * string_nconcat - concatenates two strings
 * @s1: string 1
 * @s2: string 2
 * @n: variable
 *
 * Return: result
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{

char *result;
unsigned int len_s1;
unsigned int len_s2;
unsigned int i;
unsigned int j;

len_s1 = 0;
len_s2 = 0;
i = 0;
j = 0;

if (s1 == NULL)
	s1 = "";

if (s2 == NULL)
	s2 = "";

while (s1[len_s1] != '\0')
	len_s1++;

while (s2[len_s2] != '\0')
	len_s2++;

if (n >= len_s2)
	n = len_s2;

result = malloc(len_s1 + n + 1);
if (result == NULL)
	return (NULL);

while (i < len_s1)
{
	result[i] = s1[i];
	i++;
}

while (j < n)
{
	result[len_s1 + j] = s2[j];
	j++;
}

result[len_s1 + n] = '\0';

return (result);

}

