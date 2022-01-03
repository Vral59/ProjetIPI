#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

/*
@requires : pointer on 2D matrix and the size
@assings : Free the momory
@ensures : nothing
*/
void freeMatrix(int **matrix,int size){
    for (int i =0 ; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
}

/*
@requires : pointer on FILE not NULL
@assings : nothing, just move cursor in the FILE
@ensures : 'n' the number of states
*/
int readNbStateTot(FILE *fentr){
    int numberStateTotal = 0;
    char val;
    while ((val = fgetc(fentr)) != '\n'){ /* because "n" can be written over several finish characters */
        numberStateTotal = numberStateTotal*10 + val - '0'; /* with the power of 10 we transforme n into an int  */
    }
    return numberStateTotal;
}

/*
@requires : pointer on FILE not NULL, pointer on Array and int number of states
@assings : fill in the array and move the cursor in the FILE
@ensures : Put the great value in the array
*/
void readAction(FILE *fentr,int *action,int numberStateTotal){
    for (int i = 0; i < numberStateTotal*128; i++){
        action[i] = fgetc(fentr);
    }
}


/*
@requires : pointer on FILE not NULL, pointer on Array and int number of states
@assings : fill in the array and move the cursor in the FILE
@ensures : Put the great value in the array
*/
void readReduit(FILE *fentr,int *reduit,int numberStateTotal){
    for (int i = 0; i < numberStateTotal; i++){
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
        int state1 = (int)value; // explicit Cast
        int lettre = fgetc(fentr); //The number of the character will give its place in the matrix
        int state2 = fgetc(fentr);
        matrice[state1][lettre] = state2;
    }
}

/*
@requires : Pointer on all array we need and the langage we need to test
@assings : nothing
@ensures : Accept or Not the langage
*/
void algoL1(int *action, int* reduit1, int *reduit2, int **decale, int **branchement, char langage[256]){

    int state = 0; // initial state is 0
    int cpt = 0;
    int valAct = 0;
    int lettre = langage[0]; // We take the first letter
    Stack *pileState = stackInit();
    valAct = action[state*128 + lettre];
    stackPush(pileState,state);
    while (valAct != 0 && valAct != 1){ // While the action is not accept or refuse 
        if (valAct == 2){ // if we shift
            stackPush(pileState,decale[state][lettre]); // we put the next state in the stack
            cpt ++;
            lettre = langage[cpt]; // we go to the next letter
        }
        else { // if we reduce
            int reduceState = reduit1[state]; // 1st reduction component
            int reduceChar = reduit2[state]; // 2nd reduction component
            int reduceStatePrime = state;
            for(int i = 0; i <= reduceState;i++){ // we pop reduceState times
                reduceStatePrime = stackPop(pileState);
            }
            state = reduceStatePrime; // state change ==> current state is the top of the stack
            stackPush(pileState,state);
            stackPush(pileState, branchement[state][reduceChar]); // we put the next state in the stack and do not change the letter
        }
        state = stackPop(pileState); // We pop the new state
        stackPush(pileState,state);
        valAct = action[state*128+lettre]; // Action change
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

    /* Input test */
	if (argc!=2) {
    	printf("Il faut un fichier .aut en entrée");
    	exit(1);
	}
	if ((fentr= fopen(argv[1], "r")) == NULL) {
        printf("Erreur dans l'ouverture %s", argv[1]);
     	exit(1);
	}

   /* Find 'n' the total number of states */

	fgetc(fentr); /* We read the 'a' */
    fgetc(fentr); /* We read the ' ' */

    int numberStateTotal = readNbStateTot(fentr);

    /* Declaration of the variables that will contain the values of the files */
    int *action = NULL;
    int *reduit1 = NULL;
    int *reduit2 = NULL;
    int **decale = NULL;
    int **branchement = NULL;

    action = malloc((numberStateTotal*128) * sizeof(int));
    reduit1 = malloc((numberStateTotal*sizeof(int)));
    reduit2 = malloc((numberStateTotal*sizeof(int)));
 
    decale = malloc(numberStateTotal * sizeof(int*));
    for(int i = 0; i < 256; i++){
        decale[i] = malloc(256 * sizeof(char));
    }

    branchement = malloc(numberStateTotal * sizeof(int*));
    for(int i = 0; i < 256; i++){
        branchement[i] = malloc(256 * sizeof(char));
    }

    /* Table fills */

    /* Action fills */
    readAction(fentr,action,numberStateTotal);
    fgetc(fentr); /* We read the '\n' */

    /* Reduit1 and Reduit2 fills */
    readReduit(fentr,reduit1,numberStateTotal);
    fgetc(fentr); /* We read the '\n' */
    readReduit(fentr,reduit2,numberStateTotal);
    fgetc(fentr); /* We read the '\n' */

    /* Shift fills*/
    readBranDecal(fentr, decale);
    fgetc(fentr); /* We read the remaining two '\255' */
    fgetc(fentr);

    /* Branchement fills */
    readBranDecal(fentr, branchement);

    /* We have finished reading the whole file */

    /* infinite loop to offer several input */
    while (1){
        char buf[256];
        printf("Entrer le langage à tester : \n");
        fgets(buf,sizeof(buf),stdin);
        algoL1(action,reduit1,reduit2,decale,branchement,buf); /* Use of algo */
    }

    /* Free memory */
    fclose(fentr);
    free(action);
    free(reduit1);
    free(reduit2);
    freeMatrix(decale,256);
    freeMatrix(branchement,256);
	return 0; 
}