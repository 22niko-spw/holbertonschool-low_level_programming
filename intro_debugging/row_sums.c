#include <stdio.h>
/**
 * row_sum - Calcule la somme d'une seule ligne de la table.
 * @row: Le numéro de la ligne actuelle.
 * @cols: Le nombre total de colonnes.
 *
 * Return: La somme des produits pour cette ligne.
 */
int row_sum(int row, int cols)
{
	int c;
	int sum = 0;

	for (c = 1; c <= cols; c++)
		sum += row * c;

	return (sum);
}
/**
 * total_sum - Calcule la somme totale de toute la table.
 * @rows: Nombre total de lignes.
 * @cols: Nombre total de colonnes.
 *
 * Return: La somme cumulée de toutes les lignes.
 */
int total_sum(int rows, int cols)
{
	int r;
	int total = 0;

	for (r = 1; r <= rows; r++)
	{
		total += row_sum(r, cols);
	}

	return (total);
}

/* -- DO NOT Modify the code below this line -- */
/**
 * main - Point d'entrée du programme
 *
 * Description: Appelle la fonction total_sum pour calculer la somme
 * d'une table de multiplication de 3x3 et affiche le résultat.
 *
 * Return: Toujours 0 (indique que le programme s'est terminé avec succès)
 */
int main(void)
{
	printf("%d\n", total_sum(3, 3));
	return (0);
}
