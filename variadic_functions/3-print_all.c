#include "variadic_functions.h"
/**
 * print_all - prints anything based on a format string
 * @format: list of types of arguments passed to the function
 *
 * Return: void
 */
void print_all(const char * const format, ...)
{
	va_list ap;
	const char *p;
	char c;
	int i;
	float f;
	char *str;
	char *sep;

	if (format == NULL)
	{
   	 printf("\n");
    	return;
	}

	va_start(ap, format);

	p = format;
	sep = "";
	while (*p)
	{
		switch (*p)
		{
		case 'c':
			c = va_arg(ap, int);
			printf("%s%c", sep, c);
			sep = ", ";
			break;

		case 'i':
			i = va_arg(ap, int);
			printf("%s%d", sep, i);
			sep = ", ";
			break;

		case 'f':
			f = va_arg(ap, double);
			printf("%s%f", sep, f);
			sep = ", ";
			break;

		case 's':
    		str = va_arg(ap, char *);
    		if (str == NULL)
       		str = "(nil)";
    		printf("%s%s", sep, str);
    		sep = ", ";
    		break;

			default: 
			break;

		}
		p++;

	}

	va_end(ap);
	printf("\n");
}
