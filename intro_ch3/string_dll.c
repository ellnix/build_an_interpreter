#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct DLLNode {
  char *string;
  struct DLLNode *next;
  struct DLLNode *prev;
} DLLNode;

DLLNode* dll_append(DLLNode *node, char* new_string) {
  DLLNode *new_node = malloc(sizeof(DLLNode));
  DLLNode *next_node = node->next;

  new_node->next = next_node;
  new_node->prev = node;
  new_node->string = new_string;

  node->next = new_node;

  if(next_node) {
    next_node->prev = new_node;
  }

  return new_node;
}

DLLNode* dll_prepend(DLLNode *node, char *new_string) {
  DLLNode *new_node = malloc(sizeof(DLLNode));
  DLLNode *prev_node = node->prev;

  new_node->next = node;
  new_node->prev = prev_node;
  new_node->string = new_string;

  node->prev = new_node;

  if(prev_node) {
    prev_node->next = new_node;
  }

  return new_node;
}

DLLNode *pop_node(DLLNode *node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;
}

DLLNode* new_cyclical_list() {
  DLLNode* list = malloc(sizeof(DLLNode));
  list->next = list;
  list->prev = list;
  return list;
}

DLLNode *find_node(DLLNode *node, char *needle) {
  DLLNode *original_node = node;
  
  do {
    if (needle == node->string) {
      return node;
    }

    node = node->next;
  } while (node && node != original_node);

  return NULL;
}

DLLNode *find_node_backward(DLLNode *node, char *needle) {
  DLLNode *original_node = node;
  
  do {
    if (needle == node->string) {
      return node;
    }

    node = node->prev;
  } while (node && node != original_node);

  return NULL;
}

int main() {
  DLLNode *start = new_cyclical_list();
  start->string = "A cirle has no beginning";

  // Appending and prepending

  DLLNode *phoenix = dll_append(start, "What came first, the phoenix or the flame?");
  assert(phoenix->next == start);
  assert(phoenix->prev == start);

  DLLNode *hello = dll_prepend(start, "Hello world");
  assert(hello->next == start);
  assert(hello->prev == phoenix);

  DLLNode *goodbye = dll_append(hello, "and goodbye");
  assert(goodbye->next == start);
  assert(goodbye->prev == hello);
  printf("All append and prepend tests passed! 🎉\n");

  // Finding nodes

  DLLNode *goodbye_node = find_node(start, "and goodbye");
  assert(goodbye_node == goodbye);

  DLLNode *hw_node = find_node_backward(start, "Hello world");
  assert(hw_node == hello);

  printf("All searching tests passed! 🎉\n");

  // Deleting nodes

  pop_node(hello);
  assert(!find_node(start, "Hello world"));

  printf("All deletion tests passed! 🎉\n");

  printf("All tests passed! 🎉🎉🎉\n");
}
