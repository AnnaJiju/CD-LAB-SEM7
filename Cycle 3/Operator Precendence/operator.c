#include <stdio.h>
#include <string.h>

int main() {
    char stack[20], input[20];
    int top = -1, i = 0;

    // Correct Operator precedence table
    //          i    +    * $
    char prec[4][4] = {
        /* i */ {'R', '>', '>', '>'}, // R = Reject (i followed by i is invalid)
        /* + */ {'<', '>', '<', '>'},
        /* * */ {'<', '>', '>', '>'},
        /* $ */ {'<', '<', '<', 'A'}  // A = Accept
    };
    // < : Shift
    // > : Reduce
    
    char sym[] = {'i', '+', '*', '$'};

    printf("Enter expression (use i for operand, end with $): ");
    scanf("%s", input);

    // Initialize stack with $
    stack[++top] = '$';

    printf("\nSTACK\t\tINPUT\t\tACTION\n");

    while (1) {
        // Print current stack and input
        for (int j = 0; j <= top; j++)
            printf("%c", stack[j]);
        printf("\t\t%s\t\t", &input[i]);

        int row = -1, col = -1;

        // Find the corresponding column (from input)
        for (int k = 0; k < 4; k++) {
            if (input[i] == sym[k]) col = k;
        }

        // --- FIXED: Find row (from stack's top-most terminal) ---
        // This skips over 'E's to find the last operator or 'i'
        int top_terminal_pos = top;
        while (stack[top_terminal_pos] == 'E') {
            top_terminal_pos--;
        }
        for (int k = 0; k < 4; k++) {
            if (stack[top_terminal_pos] == sym[k]) row = k;
        }

        // Invalid symbol case
        if (row == -1 || col == -1) {
            printf("Reject (Invalid Symbol)\n");
            break;
        }

        char action = prec[row][col];

        // Perform actions based on precedence
        if (action == '<') {
            // SHIFT
            stack[++top] = input[i++];
            printf("Shift\n");
        } 
        else if (action == '>') {
            // --- FIXED: REDUCE ---
            // Now correctly finds the handle to reduce
            if (stack[top] == 'i') {
                stack[top] = 'E'; // Reduce i -> E
                printf("Reduce i -> E\n");
            } 
            // Check for E+E or E*E
            else if (stack[top] == 'E' && 
                     (stack[top - 1] == '+' || stack[top - 1] == '*') && 
                     stack[top - 2] == 'E') 
            {
                char op = stack[top - 1]; // Get the operator
                top -= 2; // Pop 'E' and 'operator'
                // stack[top-2] (which is 'E') becomes the new stack[top]
                printf("Reduce E%cE -> E\n", op);
            } 
            else {
                // If we get > but don't have a valid handle, reject
                printf("Reject (Invalid Handle)\n");
                break;
            }
        } 
        else if (action == 'A') {
            // --- FIXED: ACCEPT ---
            printf("Accept\n");
            break;
        } 
        else { // 'R' or any other invalid state
            // REJECT
            printf("Reject (Invalid Precedence)\n");
            break;
        }
    }

    return 0;
}
