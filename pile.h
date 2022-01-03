#include<stdlib.h>
#include<stdio.h>


typedef struct elementStack{
    int etatValue;
    struct elementStack *next;
} elementStack;


typedef struct Stack {
    elementStack *first;
} Stack;

/* Initialization of a stack */
Stack *stackInit();

/* Add and int at the top of the stack */
void stackPush(Stack *stack, int elementValue);

/* Pop the top of the stack */
int stackPop(Stack *stack);