#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int idmahasiswa;
  int umur;
  int height;
  char nama[30];
  struct node *left;
  struct node *right;
};

struct mahasiswa {
  int idmahasiswa;
  int umur;
  char nama[30];
};

int max(int a, int b) {
  if (a > b)
    return a;
  else
    return b;
}

int height(struct node *N) {
  if (N == NULL) {
    return 0;
  }
  return N->height;
}

// Hitung Balance factor untuk node N
int getBalanceFactor(struct node *N) {
  if (N == NULL) {
    return 0;
  }
  return height(N->left) - height(N->right);
}

struct node *rightRotate(struct node *T) {
  struct node *new_root = T->left;
  struct node *orphan = new_root->right;

  // Lakukan rotasi
  new_root->right = T;
  T->left = orphan;

  // Update height
  T->height = max(height(T->left), height(T->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

  // Return root baru
  return new_root;
}

struct node *leftRotate(struct node *T) {
  struct node *new_root = T->right;
  struct node *orphan = new_root->left;

  // Lakukan rotasi
  new_root->left = T;
  T->right = orphan;

  // Update height
  T->height = max(height(T->left), height(T->right)) + 1;
  new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

  // Return root baru
  return new_root;
}

struct node *newNode(int idmahasiswa, char *nama, int umur) {
  struct node *node = (struct node *)malloc(sizeof(struct node));

  node->idmahasiswa = idmahasiswa;
  strcpy(node->nama, nama);
  node->umur = umur;
  node->left = NULL;
  node->right = NULL;
  node->height = 1; // new node is initially added at leaf

  return node;
}

void displayPreorder(struct node *node) {
  if (node == NULL) {
    return;
  }

  printf("%d ", node->idmahasiswa); // root
  displayPreorder(node->left);      // subtree kiri
  displayPreorder(node->right);     // subtree kanan
}

void displayInorder(struct node *node) {
  if (node == NULL) {
    return;
  }

  displayInorder(node->left); // subtree kiri

  printf("%d ", node->idmahasiswa); // root

  displayInorder(node->right); // subtree kanan
}

void displayPostorder(struct node *node) {
  if (node == NULL) {
    return;
  }

  displayPostorder(node->left);     // subtree kiri
  displayPostorder(node->right);    // subtree kanan
  printf("%d ", node->idmahasiswa); // root
}

void detail(struct node *node) {
  if (node == NULL) {
    return;
  }

  detail(node->left);                                // subtree kiri
  printf("%d, %d, ", node->idmahasiswa, node->umur); // root
  puts(node->nama);
  detail(node->right); // subtree kanan
}

/* Print nodes at a current level */
void printCurrentLevel(struct node *root, int level) {
  if (root == NULL) {
    return;
  }
  if (level == 1) {
    printf("%d ", root->idmahasiswa);
  } else if (level > 1) {
    printCurrentLevel(root->left, level - 1);
    printCurrentLevel(root->right, level - 1);
  }
}

void printLevelOrder(struct node *root) {
  int h = height(root);
  int i;
  for (i = 1; i <= h; i++)
    printCurrentLevel(root, i);
}

struct node *insert(struct node *node, int idmahasiswa, char *nama, int umur) {
  // 1. Lakukan BST insert biasa
  if (node == NULL)
    return (newNode(idmahasiswa, nama, umur));

  if (idmahasiswa < node->idmahasiswa)
    node->left = insert(node->left, idmahasiswa, nama, umur);
  else if (idmahasiswa > node->idmahasiswa)
    node->right = insert(node->right, idmahasiswa, nama, umur);
  else
    return node; // asumsi tidak boleh ada nilai yang sama dalam BST

  // 2. Update height dari node
  node->height = 1 + max(height(node->left), height(node->right));

  // 3. Hitung balance factor untuk menentukan apakah node unbalanced
  int balance = getBalanceFactor(node);

  // Jika tidak balanced, return hasil rotation
  // Kasus 1: Left Left
  if (balance > 1 && idmahasiswa < node->left->idmahasiswa)
    return rightRotate(node);

  // Kasus 2: Right Right
  if (balance < -1 && idmahasiswa > node->right->idmahasiswa)
    return leftRotate(node);

  // Kasus 3: Right Left
  if (balance < -1 && idmahasiswa < node->right->idmahasiswa) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // Kasus 4: Left Right
  if (balance > 1 && idmahasiswa > node->left->idmahasiswa) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // return node jika balanced
  return node;
}

void search_node(struct node *root, int idmahasiswa) {
  struct node *cursor = root;

  while (cursor->idmahasiswa != idmahasiswa) {
    if (cursor != NULL) {
      if (idmahasiswa > cursor->idmahasiswa) {
        cursor = cursor->right;
      } else {
        cursor = cursor->left;
      }

      if (cursor == NULL) {
        printf("\nNode %d tidak ditemukan", idmahasiswa);
        return;
      }
    }
  }

  printf("\nNode %d ditemukan", idmahasiswa);
  return;
}

struct node *delete_node(struct node *root, int deletedData) {
  if (root == NULL)
    return NULL;

  struct node *cursor;
  if (deletedData > root->idmahasiswa)
    root->right = delete_node(root->right, deletedData);
  else if (deletedData < root->idmahasiswa)
    root->left = delete_node(root->left, deletedData);
  else {
    // 1 CHILD
    if (root->left == NULL) {
      cursor = root->right;
      free(root);
      root = cursor;
    } else if (root->right == NULL) {
      cursor = root->left;
      free(root);
      root = cursor;
    }

    // 2 CHILDS NODE
    else {
      cursor = root->right;
      while (cursor->left != NULL) {
        cursor = cursor->left;
      }
      // proses pemindahan data ke branch sebelumnya karena pengahapusan data
      // setelah ini dept terdalam sehingga perlu adanya penaiakan branch
      // dibawahnya.
      root->idmahasiswa = cursor->idmahasiswa;
      strcpy(root->nama, cursor->nama);
      root->umur = cursor->umur;
      // Melanjutkan proses delete node dept terdalam.
      root->right = delete_node(root->right, cursor->idmahasiswa);
    }
  }

  // Jika setelah dilakukan delete, tree kosong maka return root
  if (root == NULL)
    return root;
  // 2. Update height dari node
  root->height = 1 + max(height(root->left), height(root->right));
  // 3. Hitung balance factor untuk menentukan apakah root unbalanced
  int balance = getBalanceFactor(root);
  // Jika tidak balanced, return hasil rotation

  // Kasus 1: Left Left
  if (balance > 1 && getBalanceFactor(root->left) >= 0)
    return rightRotate(root);

  // Kasus 2: Right Right
  if (balance < -1 && getBalanceFactor(root->right) <= 0)
    return leftRotate(root);

  // Kasus 3: Right Left
  if (balance < -1 && getBalanceFactor(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  // Kasus 4: Left Right
  if (balance > 1 && getBalanceFactor(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  return root;
}

void printmhs(struct mahasiswa *mhs) {
  printf("Id Mahasiswa : %d\n", mhs->idmahasiswa);
  printf("Nama : %s\n", mhs->nama);
  printf("Umur : %d\n", mhs->umur);
}

int main() {

  struct mahasiswa mhs[9];
  int i;

  mhs[1].idmahasiswa = 3;
  strcpy(mhs[1].nama, "Hadi");
  mhs[1].umur = 17;

  mhs[2].idmahasiswa = 1;
  strcpy(mhs[2].nama, "Bayu");
  mhs[2].umur = 19;

  mhs[3].idmahasiswa = 6;
  strcpy(mhs[3].nama, "Annisa");
  mhs[3].umur = 22;

  mhs[4].idmahasiswa = 4;
  strcpy(mhs[4].nama, "Budi");
  mhs[4].umur = 17;

  mhs[5].idmahasiswa = 7;
  strcpy(mhs[5].nama, "Rini");
  mhs[5].umur = 20;

  mhs[6].idmahasiswa = 10;
  strcpy(mhs[6].nama, "Fajar");
  mhs[6].umur = 19;

  mhs[7].idmahasiswa = 14;
  strcpy(mhs[7].nama, "Rizky");
  mhs[7].umur = 21;

  mhs[8].idmahasiswa = 13;
  strcpy(mhs[8].nama, "Dinda");
  mhs[8].umur = 18;

  struct node *root;

  root = newNode(mhs[1].idmahasiswa, &mhs[1].nama, mhs[1].umur);

  for (i = 2; i < 9; i = i + 1) {
    root = insert(root, mhs[i].idmahasiswa, &mhs[i].nama, mhs[i].umur);
  }

  // printf("Isi Tree: \n");
  // displayInorder(root);
  detail(root);
  printf("\nBerikut adalah Isi Tree secara Preorder : ");
  displayPreorder(root);
  printf("\nBerikut adalah Isi Tree secara Inorder : ");
  displayInorder(root);
  printf("\nBerikut adalah Isi Tree secara Postorder : ");
  displayPostorder(root);
  printf("\nBerikut adalah Isi Tree secara Level Order : ");
  printLevelOrder(root);
  printf("\n\n");

  root = delete_node(root, 10);

  detail(root); // Inituh Idmahasiswanya kehapus, tapi untuk nama dan umur
  // yang kehapus malah beda
  printf(
      "\nBerikut adalah Isi Tree (Setelah elemen dihapus) secara Preorder : ");
  displayPreorder(root);
  printf(
      "\nBerikut adalah Isi Tree (Setelah elemen dihapus) secara Inorder : ");
  displayInorder(root);
  printf(
      "\nBerikut adalah Isi Tree (Setelah elemen dihapus) secara Postorder : ");
  displayPostorder(root);
  printf("\nBerikut adalah Isi Tree (Setelah elemen dihapus) secara Level "
         "Order : ");
  printLevelOrder(root);

  return 0;
}
