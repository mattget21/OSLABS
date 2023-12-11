
#include "list.h"


/**
 * Test if the values were added correctly to the front of the linked list
 * *Returns true if the values were added correctly to the front of the linked list
 * @param ll_head: pointer to the head of the linked list
 * @param value_array: array of values to be added to the linked list
*/
bool test_list_add_to_front(list_t *ll_head, int *value_array, int array_size) {
    int i;
    for (i = 0; i < array_size; i++) {
        printf("Value added to front: %d\n", value_array[i]);
        list_add_to_front(ll_head, value_array[i]);
        list_print(ll_head);
        if (value_array[i] != list_get_elem_at(ll_head, 1)) {
            return false;
        }
    }
    return true;
    //?might want to free up memory for the linked list
}


/**
 * * Test if the values were added correctly to the back of the linked list
 * Returns true if the values were added correctly to the front of the linked list
 * @param ll_head: pointer to the head of the linked list
 * @param value_array: array of values to be added to the linked list
*/
bool test_list_add_to_back(list_t *ll_head, int *value_array, int array_size) {
    int i= 0;
    for (i = 0; i < array_size; i++) {
        list_add_to_back(ll_head, value_array[i]);
        printf("Value added to back: %d\n", value_array[i]);
        list_print(ll_head);
        if (value_array[i] != list_get_elem_at(ll_head, list_length(ll_head))) {
            return false;
        }
    }
    return true;
    //?might want to free up memory for the linked list
}


/**
 * Test if value was added correctly at the given index
 * *Returns true if the values were added correctly to the right index of the linked list
 * @param ll_head: pointer to the head of the linked list
 * @param value_array: array of values to be added to the linked list
*/
bool test_list_add_at_index(list_t *ll_head, int *value_array, int array_size) {
    int i;
    int min = 1;
    
    //! SHOULD MODIFY THIS FUNCTION TO INCLUDE A RANDOM INDEX BEYOND THE LENGTH OF THE LINKED LIST
    
    for (i = 0; i < array_size; i++) {
        int max = ll_head->length; //dynamically gets the length of the linked list
        int randomNum = (rand() % (max - min + 1)) + min; //gets a random number to serve as index within given linked list
        list_add_at_index(ll_head, value_array[i], randomNum);
        printf("Value added to index %d: %d\n", randomNum, value_array[i]);
        list_print(ll_head);
        if (value_array[i] != list_get_elem_at(ll_head, randomNum)) {
            return false;
        }
    }
    return true;
}


/**
 * * Test if the first node in the list is removed, 
 * returns true if removed correctly
 * @param ll_head: pointer to the first node in the list
*/
bool test_list_remove_from_front(list_t *ll_head) {
    int count = 0;
    int max = ll_head->length;
    int min = 1;
    
    if (max > 0) {
        int num_of_nodes_to_remove =  (rand() % (max - min + 1)) + min; // generate a random number between min and max to remove
        printf("Here are the amount of nodes to remove from the list: %d\n", num_of_nodes_to_remove);
        while (count < 3) {
            list_print(ll_head);
            if (list_get_elem_at(ll_head, 1) != list_remove_from_front(ll_head)) {
                return false;
            }
            count++;
            continue;
        }
        list_print(ll_head);
        return true;
    }
    printf("The list is empty");
    return false;
}


/**
 * *Test if the last node in the list is removed
 * returns true if removed correctly from the back
 * @param ll_head: pointer to the first node(head) of the list
*/
bool test_list_remove_from_back(list_t *ll_head) {
   int count = 0;
   int max = ll_head->length;
   int min = 1;
   
   if (max > 0){
    int num_of_nodes_to_remove =  (rand() % (max - min + 1)) + min; // generate a random number between min and max to remove
    list_print(ll_head);
    while( count < num_of_nodes_to_remove) {
        if(list_get_elem_at(ll_head, ll_head -> length) != list_remove_from_back(ll_head)) {
            return false;
        }
        count ++;
        list_print(ll_head);
        continue;
    }
    return true;
   }
   printf("The list is empty");
   return false;
}

/**
 * * Test if the node at the given index is removed
 * Returns true if removed correctly at the given index
 * @param ll_head: pointer to the first node(head) of the list
*/
bool test_list_remove_at_index(list_t *ll_head) {
    int count = 0;
    int max = ll_head->length;
    int min = 1;
    if (ll_head->length > 0) {
        int num_of_nodes_to_remove =  (rand() % (max - min + 1)) + min; // generate a random number between min and max to remove
        printf("Here are the amount of nodes to remove from the list: %d\n", num_of_nodes_to_remove);
        while (count < num_of_nodes_to_remove) {
            //int max = ll_head->length; //dynamically gets the length of the linked list
            int randomNum = (rand() % (max - min + 1)) + min; //gets a random number to serve as index within given linked listd
            list_print(ll_head);
            printf("A value is being removed at this index: %d\n", randomNum);
            if (list_get_elem_at(ll_head, randomNum) != list_remove_at_index(ll_head, randomNum)) {
                return false;
            }
            count++;
            continue;
        }
        list_print(ll_head);
        return true;
    }
    printf("The list is empty\n");
    return false;
}


/**
 * * Test if the value is in the linked list
 * Returns true if the value is in the linked list
 * @param ll_head: pointer to the first node(head) of the list
 * @param value_array: array of values to be added to the linked list
*/
bool test_list_is_in(list_t *ll_head, int *value_array, int array_size) {
   int i;
   for(i = 0; i < array_size; i++) {
       printf("Value to check if in list: %d\n", value_array[i]);
       if (list_is_in(ll_head, value_array[i]) == false) {
           printf("Value: %d not found\n", value_array[i]);
           list_print(ll_head);
           return false;
       }
       printf("Found value\n");
   }
    return true;
}


/**
 * * Test if the index returns given value
 * @brief Function to test the list_get_elem_at function
 * @param[in] ll_head: pointer to the first node(head) of the list
*/
bool test_list_get_elem_at(list_t *ll_head) {
   int i;
   int max = ll_head->length;
   int min = 1;
   if (max == 0){
    printf("List is empty. Could not get element from an empty list...returning false\n");
    return false; //Technically the function works, since there is nothing to return due to empty list
   } 
   else {
    for (i = 0; i < 3; i++) {
        int randomNum = (rand() % (max - min + 1)) + min; // gets a random number to serve as index
        printf("Here is a random index: %d\n", randomNum);// prints the random index
        if (list_is_in(ll_head, list_get_elem_at(ll_head, randomNum)) != true) {
        return false;
        }
    }
    return true;
   }
}