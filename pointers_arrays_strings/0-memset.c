/**
 * _memset - remplit la mémoire avec un octet constant
 * @s: pointeur vers la zone mémoire à remplir
 * @b: l'octet constant à utiliser
 * @n: le nombre d'octets à remplir
 *
 * Return: un pointeur vers la zone mémoire s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}

	return (s);
}
