#include "main.h"
/**
 * _isdigit - vérifie si un caractère est un chiffre (0 à 9)
 * @c: le caractère à vérifier (sous forme d'entier)
 *
 * Return: 1 si c est un chiffre, 0 sinon
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
