#include <stdio.h>
/**
 * print_table - Affiche une table de multiplication carrée.
 * @size: La taille de la table (nombre de lignes et de colonnes).
 *
 * Description: Utilise deux boucles imbriquées pour calculer
 * et afficher le produit de chaque cellule.
 */
void print_table(int size)
{
	int row, col;

	for (row = 1; row <= size; row++)
	{
		for (col = 1; col <= size; col++)
		{
			printf("%d ", row * col);
		}
		printf("\n");
	}
}

/* -- DO NOT Modify the code below this line -- */
/**
 * main - Point d'entrée du programme.
 * * Return: Toujours 0 (Succès).
 */
int main(void)
{
	print_table(4);
	return (0);
}
