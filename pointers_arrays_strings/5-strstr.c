#include <stddef.h>
#include "main.h"

/**
 * _strstr - Locates a substring.
 * @haystack: The string to be searched.
 * @needle: The substring to locate.
 *
 * Return: A pointer to the beginning of the located substring,
 * or NULL if the substring is not found.
 */
char *_strstr(char *haystack, char *needle)
{
	int i, j;

	if (*needle == '\0')
		return (haystack);

	for (i = 0; haystack[i] != '\0'; i++)
	{
		/* If first characters match, start the nested check */
		for (j = 0; needle[j] != '\0'; j++)
		{
			/* If haystack ends prematurely or characters don't match */
			if (haystack[i + j] != needle[j])
				break;

			/* If we've reached the end of needle successfully */
			if (needle[j + 1] == '\0')
				return (haystack + i);
		}
	}

	return (NULL);
}
