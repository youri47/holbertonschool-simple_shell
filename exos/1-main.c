#include "main.h"

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
