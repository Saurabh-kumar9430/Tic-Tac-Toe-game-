#include <iostream>
using namespace std;

int main() {
    char op;
    double num1, num2, result;

    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    cout << "Enter operator (+, -, *, /): ";
    cin >> op;

    switch(op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0)
                result = num1 / num2;
            else {
                cout << "Error! Division by zero.";
                return 1; // Exit the program with error code
            }
            break;
        default:
            cout << "Invalid operator!";
            return 1; // Exit the program with error code
    }

    cout << "Result: " << result;

    return 0;
}
