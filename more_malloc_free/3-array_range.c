#include "main.h"

/**
 * array_range - creates an array of i
 * @min: minimum
 * @max: maximun
 *
 * Return: result
 */
int *array_range(int min, int max)
{

int *result;
int i;

if (min > max)
	return (NULL);

result = malloc((max - min + 1) * sizeof(int));
if (result == NULL)
	return (NULL);

i = 0;
while (i < (max - min + 1))
{
	result[i] = min + i;
	i++;
}
return (result);

}
