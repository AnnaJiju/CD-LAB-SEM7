#include <stdio.h>
#include <ctype.h>

char expr[100];
int idx = 0;  // current position in expression

int E(); // Expression
int T(); // Term
int F(); // Factor

// Expression: E -> T { + T | - T }
int E() {
    int result = T();
    while (expr[idx] == '+' || expr[idx] == '-') {
        char op = expr[idx];
        idx++;
        int val = T();
        if (op == '+') {
            result = result + val;
        } else if (op == '-') {
            result = result - val;
        }
    }
    return result;
}

// Term: T -> F { * F | / F }
int T() {
    int result = F();
    while (expr[idx] == '*' || expr[idx] == '/') {
        char op = expr[idx];
        idx++;
        int val = F();
        if (op == '*') {
            result = result * val;
        } else if (op == '/') {
            result = result / val;
        }
    }
    return result;
}

// Factor: F -> (E) | multi-digit number
int F() {
    int result = 0;
    if (expr[idx] == '(') {
        idx++;           // skip '('
        result = E();    // evaluate inner expression
        if (expr[idx] == ')') {
            idx++;       // skip ')'
        }
    } 
    else if (isdigit(expr[idx])) {
        result = 0;
        while (isdigit(expr[idx])) {   // read all digits of a multi-digit number
            result = result * 10 + (expr[idx] - '0');
            idx++;
        }
    }
    return result;
}

int main() {
    printf("Enter expression (no spaces): ");
    scanf("%s", expr);

    int result = E();       // start evaluating
    printf("Result: %d\n", result);

    return 0;
}
