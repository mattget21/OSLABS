// list/list.c
// 
// Implementation for linked list.
//
// <Author>
#include "list.h"

//* allocate the memory location for the head of the linked list
list_t *list_alloc() {
  list_t *list = (list_t *) malloc(sizeof(list_t));
  list->head = NULL;
  list->length = 0;
  return list; 
}


/**
 * * Frees up the memory allocated for the linked list
 * @param ll_head: pointer to the head of the linked list
*/
void list_free(list_t *ll_head) {
  printf("Freeing up the memory allocated for the linked list...\n");
  if (ll_head -> length > 0) {
    node_t *current = ll_head->head;
    while (current != NULL) {
      node_t *next = current->next;
      free(current);
      current = next;
      ll_head->length--;
    }
  }

  ll_head->head = NULL;
  ll_head->length = 0;
  free(ll_head);
  printf("Memory freed!\n");
}

/**
 * * returns the length of the linked list
 * @param ll_head: pointer to the head of the linked list
*/
int list_length(list_t *ll_head) {
  return ll_head->length;
}

/**
 * * prints the values of the linked list
 * @param ll_head: pointer to the head of the linked list
*/
void list_print(list_t *ll_head) {
  node_t *current = ll_head->head;
  printf("Here are the current values for the linked list: \n");
  while (current != NULL && ll_head->length > 0) {
    printf("%d->", current->value);
    current = current->next;
  }
  printf("\n");
}

/**
 * * adds a node to the front of the linked list
 * @param ll_head: pointer to the head of the linked list
*/
void list_add_to_front(list_t *ll_head, elem value) {
  node_t *newNode = (node_t *) malloc(sizeof(node_t));
  newNode->value = value;
  newNode->next = ll_head->head;
  ll_head->head = newNode;
  ll_head->length++;
}

/**
 * * adds a node to the back of the linked list
 * @param ll_head: pointer to the head of the linked list
*/
void list_add_to_back(list_t *ll_head, elem value) {
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    newNode->value = value;
    
    //loop to the end of the linked list
    node_t *current = ll_head->head;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
    newNode->next = NULL;
    ll_head->length++;
}

//add a node to the linked list given the index
void list_add_at_index(list_t *ll_head, elem value, int index) {
  if (is_index_within_list(ll_head, index)) {
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    newNode->value = value;
    node_t *current = ll_head->head;
    node_t *prev = NULL;
    int count = 1;
    
    if (index == 1) {
      list_add_to_front(ll_head, value);
    } 
    else if (!is_index_within_list(ll_head, index)) {
      list_add_to_back(ll_head, value);
    } 
    else {
      while (count < index) {
      prev = current;
      current = current->next;
      count++;
      }
      prev->next = newNode;
      newNode->next = current;
      ll_head->length++;
    }
  }
}

/**
 * * removes a node from the front of the linked list
 * @param ll_head: pointer to the head of the linked list
*/
elem list_remove_from_front(list_t *ll_head) {
  if(ll_head->head == NULL){
    printf("Linked list is empty\n");
    return -1;
  }
  ll_head->length--;
  node_t *current = ll_head->head;
  elem value = current->value;
  ll_head->head = current->next;
  free(current);
  return value;
}

/**
 * * removes a node from the back of the linked list
 * @param ll_head: pointer to the head of the linked list
*/
elem list_remove_from_back(list_t *ll_head) {
  if(ll_head->head == NULL){
    printf("Linked list is empty\n");
    return -1;
  }
  node_t *current = ll_head->head;
  node_t *prev = NULL;
  while (current->next != NULL) {
    prev = current;
    current = current->next;
  }
  elem value = current->value;
  if (prev != NULL){
    prev->next = NULL;
  } 
  else{
    free(prev);
  }
  ll_head->length--;
  return value;
  free(current);
}

/**
 * * removes a node from the linked list given the index
 * @param ll_head: pointer to the head of the linked list
*/
elem list_remove_at_index(list_t *ll_head, int index) {
  node_t *current = ll_head->head; //pointer to keep track of the current node
  node_t *prev = NULL; //pointer to keep track of the previous node before current
  
  //checks if the index is valid
  if (is_index_within_list(ll_head, index)) {
    int count = 1;
    while (count < index) {
      prev = current;
      current = current->next;
      count++;
    }
    elem value = current->value;
    if (prev != NULL) {
      prev->next = current->next;
    }
    else {
      free(prev);
    }
    ll_head->length--;
    free(current);
    return value;
  }

  return -1;
}

/**
 * * checks if a value is in the linked list
 * @param ll_head: pointer to the head of the linked list
*/
bool list_is_in(list_t *ll_head, elem value) {
  node_t *current = ll_head->head;
  while (current != NULL) {
    if (current->value == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}

/**
 * * gets the value of a node given the index
 * @param ll_head: pointer to the head of the linked list
 * @param index: index of the node
*/
elem list_get_elem_at(list_t *ll_head, int index) {
  node_t *current = ll_head->head;
  int count = 1;

  //checks if the index is within the list length
  if (is_index_within_list(ll_head, index)) {
    while (count < index) {
    current = current->next;
    count++;
  }
  return current->value;
  }
  return -1;
}

/**
 * * gets the index of a node given the value
 * @param ll_head: pointer to the head of the linked list
 * @param value: value of the node
*/
int list_get_index_of(list_t *ll_head, elem value) {
  node_t *current = ll_head->head;
  int count = 1;
  while (current != NULL) {
    if (current->value == value) {
      return count;
    }
    current = current->next;
    count++;
  }
  return -1;
}

/**
 * *returns true if index is valid
 * @param value: index value
*/
bool is_index_within_list(list_t *ll_head, int index){
  bool is_index_valid = (list_length(ll_head) >= index && (index > 0))? true : false;
  return is_index_valid;
}