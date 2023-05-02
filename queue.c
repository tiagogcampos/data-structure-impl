#include <stdio.h>
#include <stdlib.h>

struct QueueNode;

typedef struct QueueNode {
  int value;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *head;
  QueueNode *tail;
  int current_capacity;
} Queue;

Queue *create_queue() {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  if (queue == NULL) {
    perror("Could not allocate memory to queue");
    return NULL;
  }
  queue->current_capacity = 0;
  return queue;
}

QueueNode *create_node(int value) {
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));

  if (node == NULL) {
    return NULL;
  }

  node->value = value;
  node->next = NULL;
  return node;
}

void remove_queue(Queue *queue) {
  QueueNode *current = queue->head;
  while (current != NULL) {
    QueueNode *prev = current;
    current = current->next;
    free(prev);
  }
  free(queue);
}

void insert(int element, Queue *queue) {
  QueueNode *node = create_node(element);

  if (queue->current_capacity == 0) {
    queue->head = queue->tail = node;
  } else {
    queue->tail->next = node;
    queue->tail = queue->tail->next;
  }

  queue->current_capacity++;
  printf("Inserted %d at address %p and current capacity is %d.\n", node->value,
         node, queue->current_capacity);
}

void pop(Queue *queue) {
  if (queue->head == NULL || queue->head->next == NULL) {
    return;
  }

  QueueNode *first_in_queue = queue->head;
  printf("First in queue %d\n", first_in_queue->value);
  queue->head = queue->head->next;

  printf("First in queue %d after pop\n", queue->head->value);

  printf("Removing element %d from the queue.\n", first_in_queue->value);

  free(first_in_queue);
}

void print_queue(Queue *queue) {
  printf("Current Capacity: %d\n", queue->current_capacity);
  QueueNode *current = queue->head;
  while (current != NULL) {
    printf("Element: %d\tAddress: %p\n", current->value, current);
    current = current->next;
  }
}

int main() {
  Queue *queue = create_queue();

  for (int i = 50; i < 100; i++) {
    insert(i, queue);
  }

  print_queue(queue);

  for (int i = 0; i < 10; i++) {
    pop(queue);
  }

  print_queue(queue);
  remove_queue(queue);

  return 0;
}
