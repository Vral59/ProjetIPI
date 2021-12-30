#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

/*
@requires : pointer on FILE not NULL
@assings : nothing, just move cursor in the FILE
@ensures : 'n' the number of states
*/
int readNbEtatTot(FILE *fentr){
    int nombreEtatTotal = 0;
    char val;
    while ((val = fgetc(fentr)) != '\n'){ /* n peut s'écrire sur plusieurs caractères */
        nombreEtatTotal = nombreEtatTotal*10 + val - '0'; /* le caractère n et on le transforme en int */
    }
    return nombreEtatTotal;
}

/*
@requires : pointer on FILE not NULL, pointer on Array and int number of states
@assings : fill in the array and move the cursor in the FILE
@ensures : Put the great value in the array
*/
void readAction(FILE *fentr,int *action,int nombreEtatTotal){
    for (int i = 0; i < nombreEtatTotal*128; i++){
        action[i] = fgetc(fentr);
    }
}


/*
@requires : pointer on FILE not NULL, pointer on Array and int number of states
@assings : fill in the array and move the cursor in the FILE
@ensures : Put the great value in the array
*/
void readReduit(FILE *fentr,int *reduit,int nombreEtatTotal){
    for (int i = 0; i < nombreEtatTotal; i++){
        reduit[i] = fgetc(fentr);
    }
}

/*
@requires : pointer on FILE not NULL, pointer on 2D Array
@assings : fill in the array and move the cursor in the FILE
@ensures : Put the great value in the array
*/
void readBranDecal(FILE *fentr,int **matrice){
    char value;
    while ((value = fgetc(fentr)) != '\255'){
        int etat1 = (int)value; // Cast explicite
        int lettre = fgetc(fentr); //Le numéro du caractère va donner sa place dans le tableau 2D
        int etat2 = fgetc(fentr);
        matrice[etat1][lettre] = etat2;
    }
}

/*
@requires : Pointer on all array we need and the langage we need to test
@assings : nothing
@ensures : Accept or Not the langage
*/

void algoL1(int *action, int* reduit1, int *reduit2, int **decale, int **branchement, char langage[256]){

    int etat = 0; // état initial est 0
    int cpt = 0;
    int valAct = 0;
    int lettre = langage[0]; // on récupère la 1ère lettre
    Stack *pileEtat = stackInit();
    valAct = action[etat*128 + lettre];
    stackPush(pileEtat,etat);
    while (valAct != 0 && valAct != 1){ // Tant que l'action n'est pas refusé ou accepté
        if (valAct == 2){ // Si on décale
            stackPush(pileEtat,decale[etat][lettre]); // on met dans la pile le prochain état
            cpt ++;
            lettre = langage[cpt]; // on change de lettre
        }
        else { // si on réduit 
            int rs = reduit1[etat]; // 1ere composante de réduit
            int rc = reduit2[etat]; // 2ème composante de réduit
            int rsp = etat;
            for(int i = 0; i <= rs;i++){ // on dépile rs fois
                rsp = stackPop(pileEtat);
            }
            etat = rsp; // l'état change ==> Etat courant ie haut de la pile
            stackPush(pileEtat,etat);
            stackPush(pileEtat, branchement[etat][rc]); // on met dans la pile le prochain état et on ne change pas de lettre
        }
        etat = stackPop(pileEtat); // On récupère le nouvel état
        stackPush(pileEtat,etat);
        valAct = action[etat*128+lettre]; // l'action change
    }
    if (valAct == 0){
        printf("Rejeté : Caractère en position %i \n\n",cpt+1);
    }
    else {
        printf("Accepté \n\n");
    }
}


int main(int argc, char *argv[]) {  
	FILE* fentr = NULL;

    /* Test d'entrée */
	if (argc!=2) {
    	printf("Il faut un fichier .aut en entrée");
    	exit(1);
	}
	if ((fentr= fopen(argv[1], "r")) == NULL) {
        printf("Erreur dans l'ouverture %s", argv[1]);
     	exit(1);
	}

   /* Récupération de 'n' le nombre d'état total */

	fgetc(fentr); /* On passe le 'a' */
    fgetc(fentr); /* On passe le ' ' */

    int nombreEtatTotal = readNbEtatTot(fentr);

    /* déclaration des différentes valeurs contenu dans le fichier */
    int *action = NULL;
    int *reduit1 = NULL;
    int *reduit2 = NULL;
    int **decale = NULL;
    int **branchement = NULL;

    action = malloc((nombreEtatTotal*128) * sizeof(int));
    reduit1 = malloc((nombreEtatTotal*sizeof(int)));
    reduit2 = malloc((nombreEtatTotal*sizeof(int)));
 
    decale = malloc(nombreEtatTotal * sizeof(int*));
    for(int i = 0; i < 256; i++){
        decale[i] = malloc(128 * sizeof(char));
    }

    branchement = malloc(nombreEtatTotal * sizeof(int*));
    for(int i = 0; i < 256; i++){
        branchement[i] = malloc(128 * sizeof(char));
    }

    /* Remplissage des tableaux contenant les actions de l'automate */

    /* Récupération de Action */
    readAction(fentr,action,nombreEtatTotal);
    fgetc(fentr); /* on vire le '\n' */

    /* Récupération de réduit1 et réduit2 */
    readReduit(fentr,reduit1,nombreEtatTotal);
    fgetc(fentr); /* on vire le '\n' */
    readReduit(fentr,reduit2,nombreEtatTotal);
    fgetc(fentr); /* on vire le '\n' */

    /* Récupération de decale*/
    readBranDecal(fentr, decale);
    fgetc(fentr); /* On lit les deux '\255' qu'il reste */
    fgetc(fentr);

    /* récupération de branchement */
    readBranDecal(fentr, branchement);

    /* On a finit de lire tout le fichier */

    /* On fait une boucle infini pour proposer plusieurs langages à tester */
    while (1){
        /* Initialisation de l'entréé */
        char buf[256];
        printf("Entrer le langage à tester : \n");
        fgets(buf,sizeof(buf),stdin);
        algoL1(action,reduit1,reduit2,decale,branchement,buf); /* On appel l'algo */
    }

    /* Libération de la mémoire */
    fclose(fentr);
    free(action);
    free(reduit1);
    free(reduit2);
    free(decale); // ATTENTION IL FAUT QUE JE MODIFIE ET FREE TOUTES LES CASES
    free(branchement);
	return 0; 
}