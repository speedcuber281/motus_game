#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LENGTH 100
#define TENTATIVE_MAX 8

void choisirMot(char *motChoisi);
void afficherProposition(char *motSecret, char *proposition, int essai);

int main()
{
    srand(time(NULL));

    char motSecret[MAX_LENGTH];
    choisirMot(motSecret);

    int longueurMot = strlen(motSecret);
    char proposition[MAX_LENGTH];
    int essai = 1;
    int essaiRestant = TENTATIVE_MAX;

    printf("Bienvenue dans le jeu du motus !\n");
    printf("Trouvez le mot secret de %d lettres. Voici la premiere lettre : %c\n", longueurMot, motSecret[0]);

    while (1)
    {
        printf("\nEssai restant : %d\n", essaiRestant);
        printf("Essai %d\n", essai);
        printf("Proposition : ");
        scanf("%s", proposition);

        if (strlen(proposition) != longueurMot)
        {
            printf("Erreur : La longueur de la proposition est incorrecte. Veuillez entrer un mot de %d lettres.\n", longueurMot);
            continue;
        }

        int i, bienPlace = 0, malPlace = 0;
        for (i = 0; i < longueurMot; i++)
        {
            if (proposition[i] == motSecret[i])
            {
                proposition[i] = toupper(proposition[i]); // lettre bien placée en majuscule
                bienPlace++;
            }
            else if (strchr(motSecret, proposition[i]))
            {
                proposition[i] = tolower(proposition[i]); // lettre mal placée en minuscule
                malPlace++;
            }
            else
            {
                proposition[i] = '.'; // lettre absente ou moins d'occurrences
            }
        }

        proposition[longueurMot] = '\0'; // Assurer que la chaîne est terminée

        printf("Resultat : %s\n", proposition);

        if (bienPlace == longueurMot)
        {
            printf("Felicitations ! Vous avez trouve le mot secret en %d essais.\n", essai);
            break;
        }

        printf("Lettres bien placees : %d\n", bienPlace);
        printf("Lettres mal placees : %d\n", malPlace);

        essai++;
        essaiRestant--;

        if (essaiRestant == 0)
        {
            printf("\nDommage vous avez perdu ...\n");
            printf("le mot etait : %s", motSecret);
            break;
        }
    }

    return 0;
}

void choisirMot(char *motChoisi)
{
    FILE *fichier;
    char ligne[MAX_LENGTH];
    int nombreMots = 0, motAleatoire;

    fichier = fopen("dico.txt", "r");

    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier dico.txt");
        exit(EXIT_FAILURE);
    }

    while (fgets(ligne, MAX_LENGTH, fichier) != NULL)
    {
        if (strlen(ligne) >= 7 && strlen(ligne) <= 10)
        {
            nombreMots++;
        }
    }

    motAleatoire = rand() % nombreMots + 1;
    rewind(fichier);

    while (motAleatoire > 0)
    {
        fgets(ligne, MAX_LENGTH, fichier);
        if (strlen(ligne) >= 7 && strlen(ligne) <= 10)
        {
            motAleatoire--;
        }
    }

    // Retirer le caractère de nouvelle ligne à la fin du mot
    ligne[strcspn(ligne, "\n")] = '\0';

    fclose(fichier);

    strcpy(motChoisi, ligne);
}

void afficherProposition(char *motSecret, char *proposition, int essai)
{
    printf("\nEssai %d\n", essai);
    printf("Proposition : %s\n", proposition);

    int i;
    for (i = 0; i < strlen(motSecret); i++)
    {
        if (proposition[i] == motSecret[i])
        {
            printf("%c", toupper(proposition[i])); // lettre bien placée en majuscule
        }
        else if (strchr(motSecret, proposition[i]))
        {
            printf("%c", tolower(proposition[i])); // lettre mal placée en minuscule
        }
        else
        {
            printf("."); // lettre absente ou moins d'occurrences
        }
    }

    printf("\n");
}
