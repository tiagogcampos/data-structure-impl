#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
  int maximum_capacity;
  int number_of_elements;
  int *elements;
} Stack;

Stack *create_stack(int maximum_capacity) {
  Stack *stack = (Stack *)malloc(sizeof(Stack));

  if (stack == NULL) {
    perror("Couldn't allocate memory to stack");
    return NULL;
  }

  stack->maximum_capacity = maximum_capacity;
  stack->number_of_elements = 0;
  stack->elements = (int *)malloc(sizeof(int) * maximum_capacity);

  if (stack->elements == NULL) {
    perror("Couldn't allocate memory to stack elements");
    return NULL;
  }

  return stack;
}

Stack *add(int element, Stack *stack) {
  if (stack->number_of_elements == stack->maximum_capacity) {
    printf("Cannot add more items to stack. Stack is full\n");
    return stack;
  }

  printf("Adding %d to %d position of the stack\n", element,
         stack->number_of_elements);

  stack->elements[stack->number_of_elements++] = element;

  return stack;
}

int *pop(Stack *stack) {
  if (stack->number_of_elements <= 0) {
    printf("Cannot pop on empty stack");
    return NULL;
  }

  return stack->elements + stack->number_of_elements-- - 1;
}

void free_stack(Stack *stack) {
  free(stack->elements);
  free(stack);
}

void print_stack(Stack *stack) {
  printf("---------------\n");
  printf("      TOP      \n");
  printf("---------------\n");
  for (int i = stack->number_of_elements - 1; i >= 0; i--) {
    printf("%d\n", stack->elements[i]);
  }
  printf("---------------\n");
  printf("     BOTTOM    \n");
  printf("---------------\n");
}

int main() {
  Stack *stack = create_stack(10);

  add(10, stack);
  add(20, stack);
  add(30, stack);
  add(40, stack);
  add(50, stack);
  add(50, stack);
  add(50, stack);
  add(50, stack);
  add(50, stack);
  add(50, stack);
  add(50, stack);

  print_stack(stack);

  for (int i = stack->number_of_elements - 1; i >= 0; i--) {
    int *pv = pop(stack);
    printf("Popped value: %d\n", *pv);
  }

  print_stack(stack);

  free_stack(stack);

  return 0;
}
