#include "main.h"

/**
 * read_textfile - Lit un fichier texte et l'affiche sur la sortie standard.
 * @filename: Nom du fichier à lire.
 * @letters: Nombre de lettres à lire et afficher.
 *
 * Return: Le nombre réel de lettres lues et affichées.
 * 0 si le fichier ne peut pas être ouvert, lu, ou si write échoue.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	ssize_t n_lu, n_ecrit;
	char *tampon;

	if (filename == NULL)
		return (0);

	/* Allocation de la mémoire pour stocker les caractères lus */
	tampon = malloc(sizeof(char) * letters);
	if (tampon == NULL)
		return (0);

	/* Ouverture du fichier en lecture seule (O_RDONLY) */
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(tampon);
		return (0);
	}

	/* Lecture du fichier */
	n_lu = read(fd, tampon, letters);
	if (n_lu == -1)
	{
		free(tampon);
		close(fd);
		return (0);
	}

	/* Écriture sur la sortie standard (STDOUT_FILENO = 1) */
	n_ecrit = write(STDOUT_FILENO, tampon, n_lu);
	if (n_ecrit == -1 || n_ecrit != n_lu)
	{
		free(tampon);
		close(fd);
		return (0);
	}

	/* Nettoyage : on libère la mémoire et on ferme le fichier */
	free(tampon);
	close(fd);

	return (n_ecrit);
}
