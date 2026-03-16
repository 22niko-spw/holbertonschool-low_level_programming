#include "function_pointers.h"
/**
 * print_name - afficher le nom
 * @name: nom
 * @f: pointeur du nom
 */
void print_name(char *name, void (*f)(char *))
{
	f(name);
}
