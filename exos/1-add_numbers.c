#include <stdio.h>

/**
 * add_numbers - Additionne deux nombres entiers
 * @a: Premier nombre
 * @b: Deuxième nombre
 *
 * Return: La somme de a et b
 */
int add_numbers(int a, int b)
{
	int result;

	result = a + b;
	return (result);
}

/**
 * main - Point d'entrée du programme
 *
 * Description: Démontre l'utilisation de la fonction add_numbers
 *
 * Return: Toujours 0 (succès)
 */
int main(void)
{
	int x = 5;
	int y = 10;
	int sum;

	sum = add_numbers(x, y);
	printf("La somme de %d et %d est %d\n", x, y, sum);

	return (0);
}
