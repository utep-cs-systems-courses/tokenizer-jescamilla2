#include <stdlib.h>
#include <stdio.h>


typedef struct s_Item {
  int id;
  char *str;
  struct s_Item *next;
} Item;

typedef struct s_List {
  struct s_Item *root;
} List;

/* Initialize the linked list to keep the history. 
   This is a pointer to the List.
*/
List *init_history() {
  List *L = (List*)malloc(1*sizeof(List)); //allocate memory for L

  L->root = NULL;
  return L; // returns the pointer to the new list

}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store */
void add_history(List *list, char *str) {
  Item *item = (Item*)malloc(1*sizeof(Item)); // allocate memory for new Item

  // make the new Item
  item->id = 1;
  item->next = NULL;
  item->str = str;

  if (list->root == NULL) {
    list->root = item; // empty list has new item as root
  } else {
    Item *current = list->root; // start at the root
    while (current->next != NULL) {
      current = current->next;
    }
    item->id = current->id + 1; // item id should be 1 more
    current->next = item; // last non-empty node points to the new item
  }

}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id) {

  if (list->root == NULL) {
    printf("No history to display.\n");
  }

  Item *current = list->root; // start at root

  //traverse the list until id is found. If not found, return empty string.
  while (current->id != id) {
    current = current->next;
    if (current == NULL) {
      goto empty_string;
    }
  }

  // id match. return the pointer
  return current->str;

 empty_string:
  return "";
  
}

/* Print the entire contents of the list. */
void print_history(List *list) {
  Item *current = list->root;

  if (list->root == NULL) {
    printf("History empty");
  } else {
    while (current != NULL) {
      printf("%d. %s\n", current->id, current->str);
      current = current->next;
    }
  }
  
}

/* Free the history list and the strings it references. */
void free_history(List *list) {

  Item *previous;
  Item *current = list->root;

  if (list->root == NULL) {
    free(list->root);
  }

  // the list was not empty so we proceed
  while (current->next != NULL) {
    previous = current; // keep track of previous item
    current = current->next; // go to next Item
    free(previous); // free previous node
  }
  free(current); // frees the last node
  free(list); // finally, frees the list itself

}
