#include <stdio.h>
/**
 * main - Point d'entrée
 *
 * Description : Affiche la taille de divers types de données
 * (char, int, long int, long long int, float) sur la machine locale.
 *
 * Return: Toujours 0 (Succès)
 */
int main(void)

{
	printf("Size of a char: %lu byte(s)\n", sizeof(char));
	printf("Size of an int: %lu byte(s)\n", sizeof(int));
	printf("Size of a long int: %lu byte(s)\n", sizeof(long int));
	printf("Size of a long long int: %lu byte(s)\n", sizeof(long long int));
	printf("Size of a float: %lu byte(s)\n", sizeof(float));


	return (0);
}
