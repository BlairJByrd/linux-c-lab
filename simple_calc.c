#include <stdio.h>
#include <stdlib.h>

// Function prototypes
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main(int argc, char *argv[]) {

    // Check if the number of arguments is correct
    if (argc != 4) {
        printf("Usage: ./simple_calc <number1> <operator> <number2>\n");
        return 1;
    }

    // Parse command-line arguments into numbers and operator
    double num1 = atof(argv[1]);
    char op = argv[2][0];
    double num2 = atof(argv[3]);

    double result;

    // Use a switch-case to perform the appropriate calculation
    switch (op) {
        case '+':
            result = add(num1, num2);
            break;
        case '-':
            result = subtract(num1, num2);
            break;
        case '*':
            result = multiply(num1, num2);
            break;
        case '/':
            // Handle invalid operators and division by zero
            if (num2 == 0) {
                printf("Error: Division by zero is not allowed.\n");
                return 1;
            }
            result = divide(num1, num2);
            break;
        default:
            printf("Error: Unsupported operator '%c'. Use +, -, *, or /.\n", op);
            return 1;
    }

    // Print the result
    printf("Result: %.2f\n", result);

    return 0;
}

// Function definitions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}
