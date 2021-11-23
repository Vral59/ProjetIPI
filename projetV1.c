#include <stdio.h>
#include <stdlib.h>
#include "pile.h"


/*
@requires One arguements, an automata .aut
@assings ??
@ensures recognize langage 
*/



int main(int argc, char *argv[]) {
	FILE* fentr = NULL;

   /* Test d'entrée */

	if (argc!=2) {
    	printf("Il me faut un fichier");
    	exit(1);
	}
	if ((fentr= fopen(argv[1], "r")) == NULL) {
     	printf("Je ne peux pas ouvrir %s", argv[1]);
     	exit(1);
	}


   /* Récupération de n */

	fgetc(fentr); /* On passe le 'a' */
   fgetc(fentr); /* On passe le ' ' */
   int n = 0;
   char val;
   while ((val = fgetc(fentr)) != '\n'){ /* n peut s'écrire sur plusieurs caractères */
      n = n*10 + val - '0'; /* le caractère n et on le transforme en int */
   }
   printf("Voici n : %i \n",n);
   


   /* déclaration des différentes valeurs contenu dans le fichier */
   int *action = NULL;
   int *reduit1 = NULL;
   int *reduit2 = NULL;
   int *decale = NULL;
   int *branchement = NULL;

   action = malloc((n*128) * sizeof(int));
   reduit1 = malloc((n*sizeof(int)));
   reduit2 = malloc((n*sizeof(int)));
   decale = (int *)malloc((n*128) * sizeof(int));
   branchement = (int *)malloc((n*128) * sizeof(int));



   /* Remplissage des tableaux contenant les actions de l'automate */

   for (int i = 0; i < (n-1)*128; i++){
      action[i] = fgetc(fentr);
      printf("%3d",action[i]); // Les prochains printf seront la pour afficher les valeurs et tout vérifier
   }
   printf("\n\n");
   fgetc(fentr); /* on vire le '\n' */
   for (int i = 0; i < n; i++){
      reduit1[i] = fgetc(fentr);
      printf("%3d",reduit1[i]);
   } 
   printf("\n\n");
   fgetc(fentr); /* on vire le '\n' */
   for (int i = 0; i < n; i++){
      reduit2[i] = fgetc(fentr);
      printf("%3d",reduit2[i]);
   }
   printf("\n");
   fgetc(fentr); /* on vire le '\n' */

   /* Récupération de decale*/
   char value1;
   while ((value1 = fgetc(fentr)) != '\255'){
      int etat1 = (int)value1; // Cast explicite
      int *lettre = fgetc(fentr); //Le numéro du caractère va donner sa place dans le tableau 2D
      int etat2 = fgetc(fentr);
      printf("%i %i %i \n",etat1,lettre,etat2);
      decale[etat1][lettre] = etat2;
   }
   
   printf("\n\n");
   fgetc(fentr); // On vire les deux '\255' qu'il reste
   fgetc(fentr);
   /* récupération de branchement */
   char value2;
   while ((value2 = fgetc(fentr)) != '\255'){
      int etat1 = (int)value2; // Cast explicite
      int *lettre = fgetc(fentr);
      int etat2 = fgetc(fentr);
      printf("%i %i %i \n",etat1,lettre,etat2);
      branchement[etat1][lettre] = etat2;
   }

   /* On a finit de lire tout le fichier */


   /* Libération de la mémoire */
	fclose(fentr);
   free(action);
   free(reduit1);
   free(reduit2);
   free(decale);
   free(branchement);
	return 0; 
}