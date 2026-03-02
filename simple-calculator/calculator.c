#include<stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * addition - Additionne deux nombres.
 * @a: Le premier nombre.
 * @b: Le deuxième nombre.
 *
 * Return: La somme de @a et @b.
 */
double addition(double a, double b)
{
	return (a + b);
}
/**
 * soustraction -  Soustraire deux nombres.
 * @a: Le premier nombre.
 * @b: Le deuxième nombre.
 *
 * Return: La différence de @a et @b.
 */
double soustraction(double a, double b)
{
	return (a - b);
}
/**
 * multiplication -  Multiplier deux nombres.
 * @a: Le premier nombre.
 * @b: Le deuxième nombre.
 *
 * Return: La multiplication de @a et @b.
 */
double multiplication(double a, double b)
{
	return (a * b);
}

/**
 * division -  Diviser deux nombres.
 * @a: Le premier nombre.
 * @b: Le deuxième nombre.
 *
 * Return: La division de @a et @b.
 */
double division(double a, double b)
{
	return (a / b);
}

/**
 * main - Entry point for the calculator program.
 * * Return: 0 if the program exits successfully,
 * otherwise a non-zero error code.
 */
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
			break;
		}
		if (choice >= 1 && choice <= 4)
		{
			printf("Enter first number\n");
			scanf("%lf", &num1);
			printf("Enter second number\n");
			scanf("%lf", &num2);
			if (choice == 1)
				resultat = addition(num1, num2);
			else if (choice == 2)
				resultat = soustraction(num1, num2);
			else if (choice == 3)
				resultat = multiplication(num1, num2);
			else if (choice == 4)
			{
				if (num2 == 0)
					printf("Error: division by zero !\n");
				else
					resultat = division(num1, num2);
			}
		printf("Result: %.2f\n", resultat);
		}
		else if (choice != 0)
			printf("Invalid choice\n");
	}
	return (0);
}
