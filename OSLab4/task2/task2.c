#include <stdio.h>
#include <stdlib.h>

/* Function declarations */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

int main(void) {
    int a = 6;  // Example operand 'a'
    int b = 3;  // Example operand 'b'
    char operation;

    /* Array of function pointers */
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};

    /* Prompt user for operation */
    printf("Operand ‘a’ : %d | Operand ‘b’ : %d\n", a, b);
    printf("Specify the operation to perform (0: add | 1: subtract | 2: Multiply | 3: divide | 4: exit): ");
    scanf(" %c", &operation);

    /* Convert char to int and subtract '0' to get the actual numeral value */
    int opIndex = operation - '0';

    /* Validate input and perform operation */
    if (opIndex >= 0 && opIndex <= 3) {
        int result = operations[opIndex](a, b);
        printf("Result: %d\n", result);
    } else if (opIndex == 4) {
        printf("Exiting program.\n");
    } else {
        printf("Invalid operation.\n");
    }

    return 0;
}

/* Define your functions here */
int add(int a, int b) { 
    printf("Adding 'a' and 'b'\n"); 
    return a + b; 
}

int subtract(int a, int b) { 
    printf("Subtracting 'b' from 'a'\n"); 
    return a - b; 
}

int multiply(int a, int b) { 
    printf("Multiplying 'a' and 'b'\n"); 
    return a * b; 
}

int divide(int a, int b) { 
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    printf("Dividing 'a' by 'b'\n"); 
    return a / b; 
}
