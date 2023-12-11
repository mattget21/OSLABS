// list/list.h
// 
// Interface definition for linked list.
//
// <Author>
#ifndef LIST_H_
#define LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* Defines the type of the elements in the linked list. You may change this if
 * you want! */
typedef int elem;

/* Defines the node structure. Each node contains its element, and points to the
 * next node in the list. The last element in the list should have NULL as its
 * next pointer. */
typedef struct node {
	elem value;
	struct node *next;
} node_t;

/* Defines the list structure, which simply points to the first node in the
 * list. */
typedef struct list {
	node_t *head;
    int length;
} list_t;

/**
 * Helper function to check if index is wihtin the list
*/
bool is_index_within_list(list_t *ll_head, int value);

/* Functions for allocating and freeing lists. By using only these functions,
 * the user should be able to allocate and free all the memory required for
 * this linked list library. */
list_t *list_alloc();
void list_free(list_t *ll_head);

/* Prints the list in some format. */
void list_print(list_t *ll_head);

/* Returns the length of the list. */
int list_length(list_t *ll_head);

/* Methods for adding to the list. */
void list_add_to_back(list_t *ll_head, elem value);
void list_add_to_front(list_t *ll_head, elem value);
void list_add_at_index(list_t *ll_head, elem value, int index);

/* Methods for removing from the list. Returns the removed element. */
elem list_remove_from_back(list_t *ll_head);
elem list_remove_from_front(list_t *ll_head);
elem list_remove_at_index(list_t *ll_head, int index);

/* Checks to see if the given element exists in the list. */
bool list_is_in(list_t *ll_head, elem value);

/* Returns the element at the given index. */
elem list_get_elem_at(list_t *ll_head, int index);

/* Returns the index at which the given element appears. */
int list_get_index_of(list_t *ll_head, elem value);

#endif /* LIST_H_ */