#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void displayPreorder (struct node* node)
{
	if (node == NULL)
		return;

	printf("%d ", node->data);

	displayPreorder(node->left);

	displayPreorder(node->right);
}

void displayInorder (struct node* node)
{
	if (node == NULL)
		return;

	displayInorder(node->left);

	printf("%d ", node->data);

	displayInorder(node->right);
}

void displayPostorder (struct node* node)
{
	if (node == NULL)
		return;

	displayPostorder(node->left);

	displayPostorder(node->right);

	printf("%d ", node->data);
}

int main( ) {

   struct node *root = newNode(1);
   root->left = newNode(2);
   root->right = newNode(3);
   root->left->left = newNode(4);
   root->left->right = newNode(5);

   printf("\nIsi dari binary tree (Pre-Order) adalah \n");
   displayPreorder(root);

   printf("\nIsi dari binary tree (In-Order) adalah \n");
   displayInorder(root);

   printf("\nIsi dari binary tree (Post-Order) adalah \n");
   displayPostorder(root);

   return 0;
}
