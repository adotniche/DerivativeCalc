#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	char data;
	struct node* left;
	struct node* right;
	struct node* next;
}node;
bool isOperator(char c);
node* newNode(char data);
void printInorder(node* node);
void push(node* x);
node* pop();
void dpush(node* x);
node* dpop();
node* ddx(node* ele);
void eval(node* root);

