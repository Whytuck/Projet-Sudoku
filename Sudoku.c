#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define N 3
#define TAILLE N * N
typedef int Grille[TAILLE][TAILLE];

/**
 * @file sudoku.c
 * @brief Programme de jeu de Sudoku.
 * @author MILIN Louis
 * @date 28/11/2023
 */

/**
 * @brief Charge une grille à partir d'un fichier .sud
 * @param grille La grille à charger.
 */
void chargerGrille(Grille grille);

/**
 * @brief Affiche la grille dans un format lisible.
 * @param grille La grille à afficher.
 */
void afficherGrille(Grille grille);

/**
 * @brief Saisie d'un entier compris entre 1 et TAILLE inclus.
 * @param valeur Pointeur vers la variable qui stockera la valeur saisie.
 */
void saisir(int *valeur);

/**
 * @brief Vérifie si une valeur peut être insérée dans une position donnée de la grille.
 * @param grille La grille.
 * @param numLigne Le numéro de ligne.
 * @param numColonne Le numéro de colonne.
 * @param valeur La valeur à insérer.
 * @return true si l'insertion est possible, false sinon.
 */
bool possible(Grille grille, int numLigne, int numColonne, int valeur);

/**
 * @brief Vérifie si la grille est pleine.
 * @param grille La grille.
 * @return true si la grille est pleine, false sinon.
 */
bool grillePleine(Grille grille);

/***************************************************** 
 *               PROGRAMME PRINCIPAL                 * 
 *****************************************************/

/**
 * @brief Fonction principale du programme.
 * @return EXIT_SUCCESS en cas de succès.
 */
int main() {
    /** Initialisation de la grille de Sudoku */
    Grille grille1;
    int numLigne, numColonne, valeur;

    /** Chargement initial de la grille depuis un fichier binaire */
    chargerGrille(grille1);

    /** Boucle principale du jeu, continue jusqu'à ce que la grille soit pleine */
    while (!grillePleine(grille1)) {
        /** Affichage de la grille actuelle */
        afficherGrille(grille1);

        /** Saisie des indices de la case à remplir */
        printf("Indices de la case ? ");
        saisir(&numLigne);
        saisir(&numColonne);
        numLigne--;
        numColonne--;

        /** Vérification si la case est libre */
        if (grille1[numLigne][numColonne] != 0) {
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        } else {
            /** Saisie de la valeur à insérer */
            printf("Valeur à insérer ? ");
            saisir(&valeur);

            /** Vérification si l'insertion est possible, puis mise à jour de la grille */
            if (possible(grille1, numLigne, numColonne, valeur)) {
                grille1[numLigne][numColonne] = valeur;
            }
        }
    }

    /** Message de fin de partie lorsque la grille est pleine */
    printf("Grille pleine, fin de partie\n");
    return EXIT_SUCCESS;
}

/*****************************************************
* FONCTIONS UTILITAIRES POUR MANIPULER LES PRODUITS *
*****************************************************/

/**
 * @brief Charge une grille à partir d'un fichier binaire.
 * @param grille La grille à charger.
 */
void chargerGrille(Grille grille) {
    /** Saisie du nom du fichier */
    char nomFichier[30];
    FILE *f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);

    /** Ouverture du fichier en mode lecture binaire */
    f = fopen(nomFichier, "rb");
    if (f == NULL) {
        /** Affichage d'une erreur si le fichier n'a pas pu être ouvert */
        printf("\nERREUR sur le fichier %s\n", nomFichier);
    } else {
        /** Lecture des données binaires dans la grille */
        fread(grille, sizeof(int), TAILLE * TAILLE, f);
    }

    /** Fermeture du fichier */
    fclose(f);
}

/**
 * @brief Affiche la grille dans un format lisible.
 * @param grille La grille à afficher.
 */
void afficherGrille(Grille grille) {
    /** Affichage du format de la grille */
    printf("         1       2       3         4       5       6         7       8       9    \n");
    printf("    +------------------------+-------------------------+-------------------------+\n");

    /** Parcours de la grille pour affichage */
    for (int i = 0; i < TAILLE; i++) {
        if (i % N == 0 && i != 0) {
            printf("    +------------------------+-------------------------+-------------------------+\n");
        }
        printf("%d   |", i + 1);
        for (int j = 0; j < TAILLE; j++) {
            if (j % N == 0 && j != 0) {
                printf("| ");
            }
            if (grille[i][j] == 0) {
                printf("    .   ");
            } else {
                printf("    %d   ", grille[i][j]);
            }
        }
        printf("|\n");
    }

    /** Ligne de séparation en bas de la grille */
    printf("    +------------------------+-------------------------+-------------------------+\n");
}

/**
 * @brief Saisie sécurisée d'un entier entre 1 et TAILLE inclus.
 * @param valeur Pointeur vers la variable qui stockera la valeur saisie.
 */
void saisir(int *valeur) {
    /** Saisie de la valeur en format chaîne de caractères */
    char ch[30];
    int x;
    printf("Saisir une valeur entre 1 et %d : ", TAILLE);
    scanf("%s", ch);

    /** Validation de la saisie jusqu'à obtenir un entier valide */
    while (sscanf(ch, "%d", &x) == 0 || x < 1 || x > TAILLE) {
        printf("La valeur n'est pas valide. Réessayez : ");
        scanf("%s", ch);
    }

    /** Assignation de la valeur convertie */
    *valeur = x;
}

/**
 * @brief Vérifie si une valeur peut être insérée dans une position donnée de la grille.
 * @param grille La grille.
 * @param numLigne Le numéro de ligne.
 * @param numColonne Le numéro de colonne.
 * @param valeur La valeur à insérer.
 * @return true si l'insertion est possible, false sinon.
 */
bool possible(Grille grille, int numLigne, int numColonne, int valeur) {
    /** Vérification de la présence de la valeur sur la même ligne */
    for (int i = 0; i < TAILLE; i++) {
        if (grille[numLigne][i] == valeur) {
            printf("La valeur %d est déjà présente sur la même ligne.\n", valeur);
            return false;
        }
    }

    /** Vérification de la présence de la valeur sur la même colonne */
    for (int i = 0; i < TAILLE; i++) {
        if (grille[i][numColonne] == valeur) {
            printf("La valeur %d est déjà présente sur la même colonne.\n", valeur);
            return false;
        }
    }

    /** Calcul du début du bloc pour vérifier la présence de la valeur dans le même bloc */
    int debutLigneBloc = (numLigne / N) * N;
    int debutColonneBloc = (numColonne / N) * N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grille[debutLigneBloc + i][debutColonneBloc + j] == valeur) {
                printf("La valeur %d est déjà présente dans le même bloc.\n", valeur);
                return false;
            }
        }
    }

    /** Si aucune condition n'est violée, l'insertion est possible */
    return true;
}

/**
 * @brief Vérifie si la grille est pleine.
 * @param grille La grille.
 * @return true si la grille est pleine, false sinon.
 */
bool grillePleine(Grille grille) {
    /** Vérification si une case vide est présente dans la grille */
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (grille[i][j] == 0) {
                return false;
            }
        }
    }
    /** Si aucune case vide n'est trouvée, la grille est pleine */
    return true;
}
