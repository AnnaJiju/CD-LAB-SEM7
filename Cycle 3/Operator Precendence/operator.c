#include <stdio.h>
#include <string.h>

int main() {
    char stack[20], input[20];
    int top = -1, i = 0;

    // Operator precedence table
    //       i    +    *    $
    char prec[5][5] = {
        {'>', '<', '<', '>'}, // i
        {'>', '>', '<', '>'}, // +
        {'>', '>', '>', '>'}, // *
        {'<', '<', '<', 'A'}  // $
    };

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

        // Find the corresponding row and column in the precedence table
        for (int k = 0; k < 4; k++) {
            if (stack[top] == sym[k]) row = k;
            if (input[i] == sym[k]) col = k;
        }

        // Invalid symbol case
        if (row == -1 || col == -1) {
            printf("Reject\n");
            break;
        }

        char action = prec[row][col];

        // Accept condition
        if (stack[top] == '$' && input[i] == '$') {
            printf("Accept\n");
            break;
        }

        // Perform actions based on precedence
        if (action == '<' || action == '=') {
            // SHIFT
            stack[++top] = input[i++];
            printf("Shift\n");
        }
        else if (action == '>') {
            // REDUCE
            if (stack[top] == 'i' || stack[top] == 'E') {
                stack[top] = 'E';
                printf("Reduce\n");
            } else {
                top--;
                printf("Reduce\n");
            }
        }
        else {
            // REJECT (invalid relation)
            printf("Reject\n");
            break;
        }
    }

    return 0;
}
