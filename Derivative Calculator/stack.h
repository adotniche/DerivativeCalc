#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct stack
{
    int size;
    int top;
    char *arr; 
} stack;

void init(stack **st);
int stacktop(stack *st);
int isEmpty(stack *st);
int isFull(stack *st);
bool isOperator(char c);
void spush(stack **st, char val);
char spop(stack **st);
int precedence(char ch);
char *infixToPostfix(char *infix);
