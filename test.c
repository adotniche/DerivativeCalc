#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct node {
	char data;
	struct node* left;
	struct node* right;
	struct node* next;
    struct node* parent;
};
struct node *head=NULL;

struct node *dhead = NULL;
struct node *dl = NULL;
struct node *dr = NULL;
struct node *droot = NULL;
/* Helper function that allocates a new node with the
given data and NULL left and right pointers. */
struct node* newNode(char data)
{
	struct node* node
		= (struct node*)malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	
	return (node);
}
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
void printInorder(struct node* node)
{
	if (node == NULL)
		return;
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
void dpush(struct node* x){
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
struct node* dpop()
{
	// Poping out the top most[ pointed with head] element
	struct node* p = dhead;
	dhead = dhead->next;
	return p;
}
//function to find derivative
// d(x)/dx = 1 
// d(c)/dx = 0
struct node* ddx(struct node* ele)
{
    struct node* new;
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
void eval(struct node* root){
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
        struct node* new = newNode(root->data);
        new->right = dpop();
        new->left = dpop();
        dpush(new);
        
        droot = new;
    }

    //d(a-b)/dx = d(a)/dx - d(b)/dx
    else if(root->data == '-'){
        struct node* new = newNode(root->data);
        new->right = dpop();
        new->left = dpop();
        dpush(new);
        
        droot = new;
    }

    //d(a*b)/dx = b*d(a)/dx + a*d(b)/dx
    else if(root->data == '*'){
        struct node *new, *new2, *sec; 
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
        struct node *mul1, *mul2, *mul3;
        struct node *sub, *div;
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

int main(){
    char s = '2';
    char p = 'x';
    char r = '/';
    char q = '+';
    struct node* root = newNode(q);
    root->left = newNode(r);
    root->left->left = newNode(p);
    root->left->right = newNode(s);
    root->right = newNode(p);
    root->left->parent = root;
    root->right->parent = root;
    printInorder(root);
    eval(root);
    printf("\n");
    printInorder(droot); 
}