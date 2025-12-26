/**
 * shell.c - Interpréteur de commandes UNIX simple (version 0.1)
 *
 * Description: Ce programme implémente un shell basique qui:
 *   - Affiche un prompt ($)
 *   - Lit une commande entrée par l'utilisateur
 *   - Exécute cette commande (chemin complet requis, ex: /bin/ls)
 *   - Réaffiche le prompt après exécution
 *   - Gère Ctrl+D (fin de fichier)
 *   - Gère les erreurs si la commande n'existe pas
 */

#include "shell.h"

/**
 * main - Point d'entrée du shell
 * @argc: Nombre d'arguments (non utilisé)
 * @argv: Tableau des arguments
 * @env: Variables d'environnement
 *
 * Return: 0 en cas de succès, 1 en cas d'erreur
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	char *ligne = NULL;      /* Buffer pour stocker la ligne lue */
	size_t taille = 0;       /* Taille du buffer (gérée par getline) */
	ssize_t caracteres_lus;  /* Nombre de caractères lus */
	int est_interactif;      /* 1 si mode interactif, 0 sinon */

	est_interactif = isatty(STDIN_FILENO);

	/* Boucle principale du shell */
	while (1)
	{
		/* Afficher le prompt uniquement en mode interactif */
		if (est_interactif)
			write(STDOUT_FILENO, "$ ", 2);

		/* Lire la ligne entrée par l'utilisateur */
		caracteres_lus = getline(&ligne, &taille, stdin);

		/* Gérer Ctrl+D (fin de fichier) */
		if (caracteres_lus == -1)
		{
			if (est_interactif)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Supprimer le retour à la ligne final */
		if (ligne[caracteres_lus - 1] == '\n')
			ligne[caracteres_lus - 1] = '\0';

		/* Ignorer les lignes vides */
		if (ligne[0] == '\0')
			continue;

		/* Exécuter la commande */
		executer_commande(ligne, argv[0], env);
	}

	/* Libérer la mémoire allouée par getline */
	free(ligne);

	return (0);
}

/**
 * executer_commande - Crée un processus fils et exécute la commande
 * @commande: La commande à exécuter (chemin complet)
 * @nom_programme: Nom du shell (pour les messages d'erreur)
 * @env: Variables d'environnement
 *
 * Description: Cette fonction utilise fork() pour créer un processus fils.
 *   Le fils exécute la commande avec execve().
 *   Le père attend que le fils termine.
 */
void executer_commande(char *commande, char *nom_programme, char **env)
{
	pid_t pid;           /* ID du processus */
	int statut;          /* Statut de sortie du fils */
	char *args[2];       /* Tableau d'arguments pour execve */

	/* Préparer les arguments (commande + NULL) */
	args[0] = commande;
	args[1] = NULL;

	/* Créer un processus fils */
	pid = fork();

	if (pid == -1)
	{
		/* Erreur lors de la création du processus */
		perror("Erreur fork");
		return;
	}

	if (pid == 0)
	{
		/* Code exécuté par le processus FILS */
		/* execve remplace le processus par la commande */
		if (execve(commande, args, env) == -1)
		{
			/* Si execve échoue, afficher l'erreur */
			afficher_erreur(nom_programme, commande);
			exit(127);  /* Code d'erreur standard: commande non trouvée */
		}
	}
	else
	{
		/* Code exécuté par le processus PÈRE */
		/* Attendre que le fils termine */
		wait(&statut);
	}
}

/**
 * afficher_erreur - Affiche un message d'erreur formaté
 * @nom_programme: Nom du shell
 * @commande: La commande qui a échoué
 *
 * Description: Affiche un message d'erreur au format standard:
 *   nom_programme: 1: commande: not found
 */
void afficher_erreur(char *nom_programme, char *commande)
{
	/* Afficher: ./shell: 1: commande: not found */
	write(STDERR_FILENO, nom_programme, _strlen(nom_programme));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, commande, _strlen(commande));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * _strlen - Calcule la longueur d'une chaîne
 * @s: La chaîne à mesurer
 *
 * Return: La longueur de la chaîne
 */
int _strlen(char *s)
{
	int longueur = 0;

	while (s[longueur] != '\0')
		longueur++;

	return (longueur);
}
