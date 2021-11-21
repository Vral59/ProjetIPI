#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "listech.h"


/*
@requires One arguements, an automata .aut
@assings ??
@ensures recognize langage 

https://www.tutorialspoint.com/cprogramming/c_file_io.html
https://pages.lip6.fr/Jean-Francois.Perrot/inalco/cours06/Cours6/TransC/LirOct.html
*/

#define TAILLE_MAX 1000

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

   /* Déclaration des variables */

	char chaine[TAILLE_MAX] = "";
   fgets(chaine, TAILLE_MAX, fentr); /* On récupère la première ligne avec le 'a n' */
   int n = chaine[2] - '0'; /* le caractère n et on le transforme en int avec de la magie*/
   char val;
   int action[n*128];
   int reduit1[n];
   int reduit2[n];
   int decale[n*128]; /* Ici on a aucune idée de la taille qu'il faut, je ferai des liste chainé plus tard, ici on prend large */
   int branchement[n*128]; /* Idem */

   /* Remplissage des tableaux contenant les actions de l'automate */

   for (int i = 0; i < (n-1)*128; i++){
      action[i] = fgetc(fentr);
      printf("%3d",action[i]);
   }
   printf("\n\n");

   for (int i = 0; i < n; i++){
      reduit1[i] = fgetc(fentr);
      printf("%3d",reduit1[i]);
   } 
   printf("\n\n");

   for (int i = 0; i < n; i++){
      reduit2[i] = fgetc(fentr);
      printf("%3d",reduit2[i]);
   }
   printf("\n");

	/* Ici ça ne fonctionne plus, on cherche les '\225' */
   int i = 0;
   while((val = fgetc(fentr)) != '\225'){
      int tmp = val;
      decale[i] = tmp;
      printf("voici le char : %2c, voici le int : %2i \n",val,tmp);
      i++;
   }

	fclose(fentr);
	return 0;
}
