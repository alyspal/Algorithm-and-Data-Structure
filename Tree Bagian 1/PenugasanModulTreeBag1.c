#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    int idmahasiswa;
    int umur;
    int height;
    char  nama[30];
    struct node* left;
    struct node* right;
};

struct mahasiswa
{
    int idmahasiswa;
    char  nama[30];
    int   umur;
};

struct node* newNode(int idmahasiswa, char *nama, int umur)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));

    node->idmahasiswa = idmahasiswa;
    strcpy(node->nama, nama);
    node->umur = umur;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf

    return node;
}

void displayInorder(struct node* node)
{
    if(node == NULL)
        return;

    displayInorder(node->left); //subtree kiri

    printf("%d ", node->idmahasiswa); //root

    displayInorder(node->right); //subtree kanan
}

struct node* insert(struct node* root, int idmahasiswa, char *nama, int umur) //Fungsi untuk menambahkan node baru dengan data = newData ke BST
{
    if(root == NULL)
    {
        root = newNode(idmahasiswa, nama, umur);
    }
    else
    {
        int is_left = 0;
        struct node* cursor = root;
        struct node* prev = NULL;
        while(cursor != NULL)
        {
            prev = cursor;
            if(idmahasiswa < cursor->idmahasiswa)
            {
                is_left = 1;
                cursor = cursor->left;
            }
            else if(idmahasiswa > cursor->idmahasiswa)
            {
                is_left = 0;
                cursor = cursor->right;
            }
        }

        if(is_left == 1)
            prev->left = newNode(idmahasiswa, nama, umur);
        else
            prev->right = newNode(idmahasiswa, nama, umur);
    }

    return root;
}

void detail(struct node* node)
{
    if(node == NULL)
        return;

    detail(node->left); //subtree kiri
    printf("%d, %d, ", node->idmahasiswa,node->umur);     // root
    puts(node->nama);
    detail(node->right); //subtree kanan
}

int main( ) {

   struct mahasiswa mhs[9];
   int i;

   mhs[1].idmahasiswa = 3;
   strcpy( mhs[1].nama, "Hadi");
   mhs[1].umur = 17;

   mhs[2].idmahasiswa = 1;
   strcpy( mhs[2].nama, "Bayu");
   mhs[2].umur = 19;

   mhs[3].idmahasiswa = 6;
   strcpy( mhs[3].nama, "Annisa");
   mhs[3].umur = 22;

   mhs[4].idmahasiswa = 4;
   strcpy( mhs[4].nama, "Budi");
   mhs[4].umur = 17;

   mhs[5].idmahasiswa = 7;
   strcpy( mhs[5].nama, "Rini");
   mhs[5].umur = 20;

   mhs[6].idmahasiswa = 10;
   strcpy( mhs[6].nama, "Fajar");
   mhs[6].umur = 19;

   mhs[7].idmahasiswa = 14;
   strcpy( mhs[7].nama, "Rizky");
   mhs[7].umur = 21;

   mhs[8].idmahasiswa = 13;
   strcpy( mhs[8].nama, "Dinda");
   mhs[8].umur = 18;

   struct node* root;

    root = newNode(mhs[1].idmahasiswa,&mhs[1].nama,mhs[1].umur);

    for (i=2; i<9; i=i+1)
   {
   root = insert(root,mhs[i].idmahasiswa,&mhs[i].nama,mhs[i].umur);}

    printf("Isi Tree: \n");
    displayInorder(root);
    printf("\n\nIsi detail Tree: \n");
    detail(root);
   return 0;
}
