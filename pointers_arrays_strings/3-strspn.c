#include "main.h"

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: The string to be searched.
 * @accept: The string containing the list of allowed characters.
 *
 * Return: The number of bytes in the initial segment of s
 * which consist only of bytes from accept.
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i, j;
	unsigned int count = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				count++;
				break;
			}
		}

		if (accept[j] == '\0')
		{
			return (count);
		}
	}

	return (count);
}
