#include<stdlib.h>
#include<stdio.h>
#include"pile.h"


/*
@requires : Stack pointer
@assingment :
@ensure : First element of Stack is NULL
*/
Stack *stackInit(){
    Stack *stack = malloc(sizeof(*stack));
    stack->first = NULL;
    return stack;
}
/*
@requires : Stack pointer & an int to add
@assingment : new malloc size of elementStack
@ensure : add by adress a new value on the Stack
*/
void stackPush(Stack *stack, int elementValue){
    elementStack *new = malloc(sizeof(*new));
    if (stack == NULL) exit(1);
    new->etatValue = elementValue;
    new->next = stack->first;
    stack->first = new;
}

/*
@requires : Stack pointer
@assingment : Nothing
@ensure : returns the top of the Stack and erase it from the Stack
*/
int stackPop(Stack *stack){
    if (stack == NULL || stack->first == NULL) exit(1);
    int top;
    elementStack *elementTop = stack->first;
    top = elementTop->etatValue;
    stack->first = elementTop->next;
    free(elementTop);
    return top;
}