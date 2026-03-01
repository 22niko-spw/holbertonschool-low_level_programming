#include<stdio.h>
/**
 * main - Entry point for the calculator program.
 * * Return: 0 if the program exits successfully,
 * otherwise a non-zero error code.
 */


/**
 * addition - Additionne deux nombres réels.
 * @a: Le premier nombre à additionner.
 * @b: Le deuxième nombre à additionner.
 *
 * Return: La somme de @a et @b.
 */
double addition(double a, double b)
{
	return (a + b);
}
int main(void)
{
	int choice = -1;
	double num1 = 0, num2 = 0, resultat = 0;

	while (choice != 0)
	{
	printf("\n---Simple Calculator---\n");
	printf("1) ADD\n2) Substract\n3) Multiply\n4) Divide\n0) Quit\n");
	printf("Your Choice: ");
	scanf("%d", &choice);

	if (choice == 0)
	{
		printf("Bye!\n");
	}
	else if (choice >= 1 && choice <= 4)
	{
		printf("Enter first number\n");
		scanf("%lf", &num1);
		printf("Enter second number\n");
		scanf("%lf", &num2);

		if (choice == 1)
			resultat = addition(num1, num2);
	}
		printf("Result; %.2f\n", resultat);

	}
	return (0);
}
