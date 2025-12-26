#ifndef SHELL_H
#define SHELL_H

/*
 * shell.h - Fichier d'en-tête pour le shell simple
 *
 * Description: Contient tous les prototypes de fonctions
 *   et les bibliothèques nécessaires au fonctionnement du shell
 */

/* ========== BIBLIOTHÈQUES STANDARD ========== */

#include <stdio.h>      /* Pour getline, perror */
#include <stdlib.h>     /* Pour malloc, free, exit */
#include <unistd.h>     /* Pour fork, execve, write, isatty */
#include <sys/types.h>  /* Pour pid_t */
#include <sys/wait.h>   /* Pour wait */

/* ========== PROTOTYPES DES FONCTIONS ========== */

/**
 * executer_commande - Exécute une commande dans un processus fils
 * @commande: Chemin complet de la commande à exécuter
 * @nom_programme: Nom du shell (argv[0])
 * @env: Variables d'environnement
 */
void executer_commande(char *commande, char *nom_programme, char **env);

/**
 * afficher_erreur - Affiche un message d'erreur sur stderr
 * @nom_programme: Nom du shell
 * @commande: La commande qui a échoué
 */
void afficher_erreur(char *nom_programme, char *commande);

/**
 * _strlen - Calcule la longueur d'une chaîne de caractères
 * @s: La chaîne à mesurer
 * Return: La longueur de la chaîne
 */
int _strlen(char *s);

#endif /* SHELL_H */
