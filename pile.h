#include<stdlib.h>
#include<stdio.h>

struct stack {
    int t[1000];
    int top;
};

typedef struct stack stack;


int emptystack(stack *p){
    return p->top == -1;
}

void push(stack *p, int el){
    if (p->top >= 1000-1)
        return;
    p->top++;
    p->t[p->top] = el;
}

int pop(stack *p){
    if (p->top == -1)
        return 1;
    int el;
    el = p->t[p->top];
    p->top--;
    return el;
}

void afficher(stack p){
    int i;
    int a = p.top;
    printf("%d \n",a);
    for(i=p.top;i>=0;i--){;
        printf("\n%d",p.t[i]);
    }
}
