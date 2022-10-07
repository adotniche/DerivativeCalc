#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include"stack.h"

void init(stack **st)
{
    stack *s = *st;
    s->size = 10;
    s->top = -1;
    s->arr = (char *)malloc(sizeof(char) * 10); 
}

int stacktop(stack *st)
{
    return st->top;
}

int isEmpty(stack *st)
{
    if (st->top == -1)
        return 1;
    return 0;
}

int isFull(stack *st)
{
    if (st->top == (st->size) - 1)
        return 1;
    return 0;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void spush(stack **st, char val)
{
    stack *s = *st;
    if (isFull(s))
    {
        printf("Stack Overflow");
        return;
    }

    s->top++;
    s->arr[s->top] = val;
}

char spop(stack **st) 
{
    stack *s = *st;
    if (isEmpty(s))
    {
        printf("Stack Underflow");
        return 'E';
    }

    char val = s->arr[s->top];
    s->top--;
    return val;
}

int precedence(char ch)
{
    if (ch == '^')
        return 3;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    return 0;
}


char *infixToPostfix(char *infix)
{

    stack *s = (stack *)malloc(sizeof(stack));
    init(&s);

    char *postfix = (char *)malloc(sizeof(char) * 50); // char array to store postfix expr

    int i = 0; // to keep track of infix traversal
    int j = 0; // to keep track of postfix traversal

    while (infix[i] != '\0') // till we dont reach end of infix expr
    {

        if (!isOperator(infix[i])) // index[i] is a opearand
            {
                postfix[j] = infix[i];
                j++;
                i++;
            }
         // index[i] is a operator
        else{
                if (precedence(infix[i]) > precedence(s->arr[stacktop(s)])) // precedence of index[i] operator is GREATER THAN that of already present in stack
                {
                    spush(&s, infix[i]);
                    i++;
                }
                else // precedence of index[i] operator is LESS THAN or EQUAL to that of already present in stack
                {
                    postfix[j] = spop(&s);
                    j++;
                }
            }
    }
    while (!isEmpty(s)) // popping out all the operators from stack till it gets empty
    {
        postfix[j] = spop(&s);
        j++;
    }
    postfix[j] = '\0'; // making last char of postfix string as EOS

    return postfix;
}
