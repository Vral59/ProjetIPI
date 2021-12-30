#include<stdlib.h>
#include<stdio.h>


typedef struct elementStack{
    int etatValue;
    struct elementStack *next;
} elementStack;


typedef struct Stack {
    elementStack *first;
} Stack;

/* création d'une pile vide */
Stack *stackInit();

/* rajoute un élément dans la pile */
void stackPush(Stack *stack, int elementValue);

/* retire un élément de la pile */
int stackPop(Stack *stack);