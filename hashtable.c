#include <stdio.h>
#include <stdlib.h>

struct HashTableNode;

typedef struct HashTableNode {
  int value;
  struct HashTableNode *next;
} HashTableNode;

typedef struct HashTable {
  int total_capacity;
  int current_capacity;

  HashTableNode **elements;

  int (*hash)(int, int);
} HashTable;

HashTable *create(int (*hash_f)(int, int), int total_capacity) {
  HashTable *t = (HashTable *)malloc(sizeof(HashTable));
  t->elements =
      (HashTableNode **)malloc(sizeof(HashTableNode *) * total_capacity);

  t->hash = hash_f;
  t->total_capacity = total_capacity;
  t->current_capacity = 0;

  return t;
}

HashTableNode *create_node(int element) {
  HashTableNode *node = (HashTableNode *)malloc(sizeof(HashTableNode));
  node->value = element;
  node->next = NULL;

  return node;
}

HashTableNode *add(int element, HashTable *table) {
  if (table->total_capacity == table->current_capacity) {
    perror("HashTable is full. Cannot add more elements");
    return NULL;
  }

  int idx = table->hash(element, table->total_capacity);

  int exists = table->elements[idx] != 0;
  HashTableNode *node = create_node(element);
  if (exists) {
    HashTableNode *current = table->elements[idx];

    while (current->next != NULL) {
      current = current->next;
    }
    current->next = node;

  } else {
    table->elements[idx] = node;
  }

  table->current_capacity++;

  return node;
}

int hash(int key, int total_capacity) {
  // TODO: impl better hashing
  return key % total_capacity;
}

void cleanup(HashTable *table) {
  for (int i = 0; i < table->total_capacity; i++) {
    HashTableNode *current = table->elements[i];
    while (current != NULL) {
      HashTableNode *temp = current;
      current = current->next;
      free(temp);
    }
  }
}

void print_hash_table(HashTable *table) {
  for (int i = 0; i < table->total_capacity; i++) {
    printf("In index %d:\t", i);
    HashTableNode *curr = table->elements[i];
    while (curr != NULL) {
      printf(" %d ", curr->value);
      curr = curr->next;
    }
    printf("\n");
  }
}

int main() {
  HashTable *table = create(hash, 100);

  add(10, table);
  add(20, table);
  add(110, table);
  add(120, table);

  print_hash_table(table);

  cleanup(table);

  return 0;
}
