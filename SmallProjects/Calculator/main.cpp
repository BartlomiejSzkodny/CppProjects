#include <iostream>

int main()
{
    double num1, num2;
    char op;

    std::cout << "Enter first number: ";
    std::cin >> num1;

    std::cout << "Enter operator (+, -, *, /, %): ";
    std::cin >> op;

    std::cout << "Enter second number: ";
    std::cin >> num2;

    switch (op)
    {
        case '+':
            std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
            break;
        case '-':
            std::cout << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
            break;
        case '*':
            std::cout << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
            break;
        case '/':
            if (num2 != 0)
                std::cout << num1 << " / " << num2 << " = " << num1 / num2 << std::endl;
            else
                std::cout << "Error: Division by zero" << std::endl;
            break;
        case '%':
            if (num2 != 0)
                std::cout << num1 << " % " << num2 << " = " << static_cast<int>(num1) % static_cast<int>(num2) << std::endl;
            else
                std::cout << "Error: Division by zero" << std::endl;
            break;
        default:
            std::cout << "Error: Invalid operator" << std::endl;
            break;
    }
}