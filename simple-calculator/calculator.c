#include<stdio.h>
/**
 * main - Entry point for the calculator program.
 * * Return: 0 if the program exits successfully,
 * otherwise a non-zero error code.
 */
int main(void)
{
	int choice;

	printf("Simple Calculator\n");
	printf("1) ADD\n");
	printf("2) Substract\n");
	printf("3) Multiply\n");
	printf("4) Divide\n");
	printf("0) Quit\n");

	scanf("%d", &choice);

	if (choice == 0)
	{
		printf("Bye!\n");
	}
	else if (choice >= 1 && choice <= 4)
	{
		printf("add a number\n");
	}
	else
	{
		printf("Invalid Choice\n");
	}
		return (0);

}
