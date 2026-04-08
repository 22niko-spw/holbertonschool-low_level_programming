#include "main.h"
#include <stdio.h>

/**
 * error_98 - Gère l'erreur de lecture.
 * @file: Nom du fichier.
 */
void error_98(char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
	exit(98);
}

/**
 * error_99 - Gère l'erreur d'écriture.
 * @file: Nom du fichier.
 */
void error_99(char *file)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
	exit(99);
}

/**
 * error_100 - Gère l'erreur de fermeture.
 * @fd: Valeur du descripteur de fichier.
 */
void error_100(int fd)
{
	dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
	exit(100);
}

/**
 * main - Copie le contenu d'un fichier dans un autre.
 * @ac: Nombre d'arguments.
 * @av: Tableau des arguments.
 *
 * Return: 0 en cas de succès.
 */
int main(int ac, char **av)
{
	int fd_from, fd_to;
	ssize_t n_read, n_wrote;
	char buffer[1024];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	fd_from = open(av[1], O_RDONLY);
	if (fd_from == -1)
		error_98(av[1]);
	fd_to = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
		error_99(av[2]);
	while ((n_read = read(fd_from, buffer, 1024)) > 0)
	{
		n_wrote = write(fd_to, buffer, n_read);
		if (n_wrote == -1 || n_wrote != n_read)
			error_99(av[2]);
	}
	if (n_read == -1)
		error_98(av[1]);
	if (close(fd_from) == -1)
		error_100(fd_from);
	if (close(fd_to) == -1)
		error_100(fd_to);
	return (0);
}
