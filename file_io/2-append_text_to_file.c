#include "main.h"

/**
 * append_text_to_file - Ajoute du texte à la fin d'un fichier existant.
 * @filename: Nom du fichier.
 * @text_content: Chaîne de caractères à ajouter.
 *
 * Return: 1 en cas de succès, -1 en cas d'échec.
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd, len = 0, n_wrote;

	if (filename == NULL)
		return (-1);

	/* 1. Ouvrir le fichier en mode écriture seule et ajout (append) */
	/* Note: On n'utilise pas O_CREAT ici */
	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);

	/* 2. Si text_content est NULL, on a juste besoin de savoir si le fichier existe */
	if (text_content != NULL)
	{
		/* Calcul de la longueur de la chaîne */
		while (text_content[len])
			len++;

		/* Écriture à la fin du fichier */
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
