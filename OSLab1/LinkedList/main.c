#include "list.h"
#include "test_list.c"

typedef struct {
    int* pArray;
    int size;
} ArrayInfo;

//Helper function to create my arrays for the linked list values!!
ArrayInfo create_array() {
    ArrayInfo array;
    int max_size = 10;
    int min_size = 1;
    int i;
    array.size = (rand() % (max_size - min_size + 1)) + min_size; // gets a random number to serve as size
    array.pArray = (int*)malloc(sizeof(int) * array.size); // Allocate memory

    if (array.pArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Fill the array with random integer
    for (i = 0; i < array.size; i++) {
        array.pArray[i] = rand() % 100; // Generate random integers between 0 and 99
    }

    return array;
}

int main() {
    //Create a linked list
    int x;
    srand(time(NULL));
    printf("Write your Tests for your linked list implementation\n");
    list_t *linked_list = list_alloc();
    ArrayInfo value_array1 = create_array();
    ArrayInfo value_array2 = create_array();

    //Test list_add_to_front
    printf("Testing list_add_to_front...\n");
    if (test_list_add_to_front(linked_list, value_array1.pArray, value_array1.size)) {
        printf("ADD TO FRONT FUNCTION: PASSED !!\n\n");
    }
    else {
        printf("ADD TO FRONT FUNCTION: FAILED...GO FIX IT!!\n\n");
    }

    //Test list_add_to_back
    printf("Testing list_add_to_back...\n");
    if (test_list_add_to_back(linked_list, value_array2.pArray, value_array2.size)) {
        printf("ADD TO BACK FUNCTION: PASSED !!\n\n");
    }
    else {
        printf("ADD TO BACK FUNCTION: FAILED...GO FIX IT!!\n\n");
    }

    //Test list_add_at_index
    printf("Testing list_add_at_index...\n");
    if (test_list_add_at_index(linked_list, value_array1.pArray, value_array1.size)) {
        printf("ADD AT INDEX FUNCTION: PASSED !!\n\n");
    }
    else {
        printf("ADD AT INDEX FUNCTION: FAILED...GO FIX IT!!\n\n");
    }


    // //! TEST CASE IS CAUSING SEGMENTATION FAULT
    //Test list_is_in function after adding
    printf("Testing list_is_in...\n");
    if (test_list_is_in(linked_list, value_array1.pArray, value_array1.size)) {
        printf("IS IN FUNCTION: PASSED!!\n\n");
    }
    else {
        printf("IS IN FUNCTION: FAILED...GO FIX IT!!\n\n");
    }

    //Test list_remove_from_front
    printf("Testing list_remove_from_front...\n");
    if (test_list_remove_from_front(linked_list)) {
        printf("REMOVE FROM FRONT FUNCTION: PASSED!!\n\n");
    }
    else {
        printf("DID NOT REMOVE VALUE FROM INDEX: LIST IS EMPTY or FAILED\n\n");
    }

    //Test list_remove_from_back
    printf("Testing list_remove_from_back...\n");
    if(test_list_remove_from_back(linked_list)) {
        printf("REMOVE FROM BACK FUNCTION: PASSED!!\n\n");
    }
    else{
        printf("DID NOT REMOVE VALUE FROM INDEX: LIST IS EMPTY or FAILED\n\n");
    }

    //Test list_is_in after removing from back
    printf("Testing list_is_in...\n");
    if (test_list_is_in(linked_list, value_array1.pArray, value_array1.size)) {
        printf("IS IN FUNCTION: PASSED!! All values were found in the linked\n\n");
    }
    else {
        printf("That value was not found in this linked list. So it returned false for not being in the linked list\n\n");
    }

    //Tets list_remove_at_index
    printf("Testing list_remove_at_index...\n");
    if(test_list_remove_at_index(linked_list)) {
        printf("LIST_REMOVE_AT_INDEX: PASSED!!\n\n");
    } 
    else {
        printf("DID NOT REMOVE VALUE FROM INDEX: LIST IS EMPTY or FAILED\n\n");
    }
    
    //Test list_get_element_at_index
    if (test_list_get_elem_at(linked_list)){
        printf("GET ELEM AT: TEST PASSED!!\n\n");
    } else {
        printf("GET ELEM AT: TEST FAILED...Uh Oh\n\n");
    }


    //freeing up memory from the linked list and arrays
    list_free(linked_list);
    // free(linked_list);
    free(value_array1.pArray);
    free(value_array2.pArray);

}