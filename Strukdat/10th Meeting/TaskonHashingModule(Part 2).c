#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct hashtable_item {
  int key[101];
  int value[101];
  int flag[101];
  /* flag = 0 : Tidak ada data
   * flag = 1 : Ada data
   * flag = 2 : Sebelumnya ada datanya */
};

struct hashtable_item hash;
int max;

/* initializing hash table array */
void init_array() {
  int i;
  for (i = 0; i < max; i++) {
    hash.key[i] = 0;
    hash.value[i] = -1;
    hash.flag[i] = -1;
  }
}

/* to every key, it will generate a corresponding index */
int hashcode(int key) {
    return (key % max);
}

int size = 0; /* size dari hashtable */

int size_of_hashtable() {
    return size;
}

void insert(int key, int value) {
  int index = hashcode(key);
  int i = index;
  int quad = 1;

  if (hash.flag[i] == 2) {
    printf("\n Key (%d) has been inserted, then removed and can't be inserted "
           "again.\n",
           key);
  } else {
    /* probing through the array until we reach an empty space - Quadratic PROBING*/
    while (hash.flag[i] == 1) {

      if (hash.key[i] == key) {
        /* case where already existing key matches the given key */
        printf("\n Key already exists, hence updating its value \n");
        hash.value[i] = value;
        return;
      }

      i = (hashcode(key) + (quad*quad)) % max; // maju kuadrat langkah
      quad++;

      if (i == index) // jika sudah mengecek satu - satu index sampai balik lagi
                      // ke index penuh
      {
        printf("\n Hash table is full, cannot insert any more item \n");
        return;
      }
    }

    for (int j = 0; j < max; j++) {
      if (hash.flag[i] == 1) {
        if (hash.value[i] == value) {
          printf("Value already exists");
          return;
        }
      }
    }
    hash.flag[i] = 1;
    hash.key[i] = key;
    hash.value[i] = value;
    size++;
    printf("\n Key (%d) has been inserted \n", key);
  }
}

void remove_element(int key) {
  int index = hashcode(key);
  int i = index;

  /* probing through array until we reach an empty space where not even once an
   * element had been present */
  while (hash.flag[i] != 0) {
    int quad = 1;
    if (hash.flag[i] == 1 && hash.key[i] == key) {
      // case when data key matches the given key
      hash.flag[i] = 2;
      hash.key[i] = -1;
      hash.value[i] = -1;
      size--;
      printf("\n Key (%d) has been removed \n", key);
      return;
    }
    i = (hashcode(key) + (quad*quad)) % max; // maju kuadrat langkah
    quad++;
    if (i == index) {
      break;
    }
  }
  printf("\n This key does not exist \n");
}

/* to display all the elements of hash table */
void display() {
  int i;
  for (i = 0; i < max; i++) {

    if (hash.value[i] == -1) {
      printf("\n Array[%d] has no elements \n", i);
    } else {
      printf("\n Array[%d] has elements -: \n %d(key) and %d(value) ", i,
             hash.key[i], hash.value[i]);
    }
  }
}

int main() {
  int choice, key, value, n, c;
  printf("Implementation of Hash Table in C with Quadratic Probing \n\n");
  printf("Insert memory that want to used : ");
  scanf("%d", &max);
  init_array();

  do {
    printf("MENU-: \n1.Inserting item in the Hashtable"
           "\n2.Removing item from the Hashtable"
           "\n3.Check the size of Hashtable"
           "\n4.Display Hashtable"
           "\n\n Please enter your choice-:");

    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Inserting element in Hashtable\n");
      printf("Enter key-:\t");
      scanf("%d", &key);
      printf("Enter value-:\t");
      scanf("%d", &value);
      insert(key, value);

      break;

    case 2:
      printf("Deleting in Hashtable \n Enter the key to delete-:");
      scanf("%d", &key);
      remove_element(key);

      break;

    case 3:
      n = size_of_hashtable();
      printf("Size of Hashtable is-:%d\n", n);

      break;
    case 4:
      display();
      break;
    default:
      printf("Wrong Input\n");
    }
  } while (1);

  getchar();
  return 0;
}
