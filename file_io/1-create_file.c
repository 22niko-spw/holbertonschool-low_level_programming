#include "main.h"

/**
 * create_file - Crée un fichier et y écrit du texte.
 * @filename: Nom du fichier à créer.
 * @text_content: Chaîne de caractères à écrire dans le fichier.
 *
 * Return: 1 en cas de succès, -1 en cas d'échec.
 */
int create_file(const char *filename, char *text_content)
{
	int fd, len = 0, n_wrote;

	if (filename == NULL)
		return (-1);

	/* 1. Calculer la longueur du texte si text_content n'est pas NULL */
	if (text_content != NULL)
	{
		while (text_content[len])
			len++;
	}

	/* 2. Ouvrir/Créer le fichier avec les bons flags et permissions */
	/* O_CREAT: créer, O_WRONLY: écrire, O_TRUNC: vider si existe */
	/* 0600: rw------- (propriétaire seul) */
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	/* 3. Écrire le texte si présent */
	if (text_content != NULL)
	{
		n_wrote = write(fd, text_content, len);
		if (n_wrote == -1 || n_wrote != len)
		{
			close(fd);
			return (-1);
		}
	}

	close(fd);
	return (1);
}
