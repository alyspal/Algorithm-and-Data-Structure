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

struct node *insert(struct node *root, int newData)
{
    if (root == NULL)
    {
        root = newNode(newData);
    }
    else
    {
        int is_left = 0;
        struct node *cursor = root;
        struct node *prev = NULL;
        while (cursor != NULL)
        {
            prev = cursor;
            if (newData < cursor->data)
            {
                is_left = 1;
                cursor = cursor->left;
            }
            else if (newData > cursor->data)
            {
                is_left = 0;
                cursor = cursor->right;
            }
        }
        if (is_left == 1)
            prev->left = newNode(newData);
        else
            prev->right = newNode(newData);
    }
    return root;
}

struct node *delete_node(struct node *root, int deletedData) {
    if (root == NULL)
        return NULL;

    struct node *cursor;
    if (deletedData > root->data)
        root->right = delete_node(root->right, deletedData);
    else if (deletedData < root->data)
        root->left = delete_node(root->left, deletedData);
    else
    {
        // 1 CHILD
        if (root->left == NULL)
        {
            cursor = root->right;
            free(root);
            root = cursor;
        }
        else if (root->right == NULL)
        {
            cursor = root->left;
            free(root);
            root = cursor;
        }
        // 2 CHILDS NODE
        else
        {
            cursor = root->right;
            struct node* parent = NULL;

            while (cursor->left != NULL)
            {
                parent = cursor;
                cursor = cursor->left;
            }
            root->data = cursor->data;
            if (parent != NULL)
                parent->left = delete_node(parent->left, parent->left->data);
            else
                root->right = delete_node(root->right, root->right->data);
        }
    }
    return root;
}

void search_node(struct node* root, int data)
{
    struct node *cursor = root;

    while (cursor->data != data) {
        if (cursor != NULL) {
            if (cursor->data > data) {
                cursor = cursor->left;
            }
            else {
                cursor = cursor->right;
            }

            if (cursor == NULL) {
                printf("\nNode %d tidak ditemukan", data);
                return;
            }
        }
    }

    printf("\nNode %d ditemukan", data);
    return;
}

int main( ) {

   struct node* root;
   root = newNode(20);
   root = insert(root,5);
   root = insert(root,1);
   root = insert(root,15);
   root = insert(root,9);
   root = insert(root,7);
   root = insert(root,12);
   root = insert(root,30);
   root = insert(root,25);
   root = insert(root,40);
   root = insert(root,45);
   root = insert(root,42);

   printf("Isi Tree: \n");
   displayInorder(root); // LEFT ROOT RIGHT
   search_node(root,1);
   search_node(root,30);

   root = delete_node(root,1);

   printf("\nIsi Tree (Setelah Delete): \n");
   displayInorder(root);
   search_node(root,1);
   search_node(root,30);

   return 0;
}
