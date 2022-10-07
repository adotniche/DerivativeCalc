#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include"ddx.h"
node *head, *dhead, *droot;
node* newNode(char data)
{
	node* node1 = (node*)malloc(sizeof(node));
	node1->data = data;
	node1->left = NULL;
	node1->right = NULL;
	node1->next = NULL;
	
	return (node1);
}



void printInorder(node* node)
{
	if (node == NULL){
		return;}
	else{
	/* first recur on left child */
    if (isOperator(node->data)) {
        printf("(");
    }
	printInorder(node->left);

	/* then print the data of node */
    
	printf("%c", node->data);

	/* now recur on right child */
	printInorder(node->right);
        if (isOperator(node->data)) {
        printf(")");
    }
	}
}

void push(node* x)
{
	if(head==NULL)
	head = x;
	else
	{
		(x)->next = head;
		head = x;
	}
	// struct node* temp;
	// while(temp!=NULL)
	// {
	//	 printf("%c ", temp->data);
	//	 temp = temp->next;
	// }
}
node* pop()
{
	// Poping out the top most[ pointed with head] element
	node* p = head;
	head = head->next;
	return p;
}

void dpush(node* x){
	if(dhead==NULL)
	dhead = x;
	else
	{
		(x)->next = dhead;
		dhead = x;
	}
	// struct node* temp;
	// while(temp!=NULL)
	// {
	//	 printf("%c ", temp->data);
	//	 temp = temp->next;
	// }
}

node* dpop()
{
	// Poping out the top most[ pointed with head] element
	node* p = dhead;
	dhead = dhead->next;
	return p;
}
//function to find derivative
// d(x)/dx = 1 
// d(c)/dx = 0
node* ddx(node* ele){
    node* new;
    int xd = ele->data - '0';
    if(xd==72){
        char c = '1';
        new = newNode(c);
        return new;
    }
    else{
        char c = '0';
        new = newNode(c);
        return new;
    }
}

//function to evaluate the whole tree to give the differentiated expression
void eval(node* root){
    //finds a leaf node, makes a d-tree node and calls ddx
    if(!root->left && !root->right){
        struct node* aa = ddx(root);
        dpush(aa);
        
        return;
    }
    //evaluates left subtree
    eval(root->left);

    //evaluates right subtree
    eval(root->right);

    //on encountering operators

    //d(a+b)/dx = d(a)/dx + d(b)/dx
    if(root->data == '+'){
        node* new = newNode(root->data);
        new->right = dpop();
        new->left = dpop();
        dpush(new);
        
        droot = new;
    }

    //d(a-b)/dx = d(a)/dx - d(b)/dx
    else if(root->data == '-'){
        node* new = newNode(root->data);
        new->right = dpop();
        new->left = dpop();
        dpush(new);
        
        droot = new;
    }

    //d(a*b)/dx = b*d(a)/dx + a*d(b)/dx
    else if(root->data == '*'){
        node *new, *new2, *sec; 
        char s = '+';
        new = newNode(root->data);
        new2 = newNode(root->data);
        new2->right = dpop();
        new2->left = root->left;
        new->left = dpop();
        new->right = root->right;
        sec = newNode(s);
        sec->right = new2;
        sec->left = new;
        dpush(sec);
        
        droot = sec;
    }

    //d(a/b)/dx = (b*d(a)/dx - a*d(b)/dx)/b^2
    else if (root->data == '/'){
        node *mul1, *mul2, *mul3;
        node *sub, *div;
        char m = '*';
        char s = '-';
        mul1 = newNode(m);
        mul2 = newNode(m);
        mul3 = newNode(m);
        sub = newNode(s);
        div = newNode(root->data);
        
        //v * d(u)/dx
        mul1->left = root->left;
        mul1->right = dpop();

        //u * d(v)/dx 
        mul2->left = root->right;
        mul2->right = dpop();      

        //subtracting
        sub->left = mul2;
        sub->right = mul1;

        //squaring the denom
        mul3->left = root->right;
        mul3->right = root->right;

        //dividing the subs and square
        div->left = sub;
        div->right = mul3;

        dpush(div);
        
        droot = div;
    }

    return;
}
