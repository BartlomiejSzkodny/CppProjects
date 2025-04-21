#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "token.h"

class Parser {
public:
int parse(const std::vector<Token>& tokens) {
    // Implement parsing logic here
    // This is a placeholder implementation
    for(int i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type == tokenType::Variable){
            if (tokens[i + 1].type == tokenType::Assign) {
                std::cout << "Assignment operator found\n"; // Print the assignment operator found
            } else if (tokens[i + 1].type == tokenType::Semicolon) {
                std::cout << "Initialization found\n"; // Print the semicolon found
            }
        } else if (tokens[i].type == tokenType::Print) {
            if (tokens[i + 1].type == tokenType::String) {
                std::cout << "Print string found\n"; // Print the print statement found
            } else if (tokens[i + 1].type == tokenType::Variable) {
                std::cout << "Print variable found\n"; // Print the print variable found
            } else if (tokens[i + 1].type == tokenType::Semicolon) {
                std::cout << "Print statement without argument found\n"; // Print the print statement without argument found
            }
                
        } else if (tokens[i].type == tokenType::If) {
            if (tokens[i + 1].type == tokenType::RoundBracketOpen) {
                std::cout << "If condition found\n"; // Print the if statement found
                int j = i + 2; // Start looking for the condition after the opening bracket
                while (tokens[j].type != tokenType::RoundBracketClose && j < tokens.size()) {
                    ++j; // Skip to the closing bracket
                }
                std::cout << "If condition ends at index: " << j << "\n"; // Print the index of the closing bracket
                if (tokens[j + 1].type == tokenType::CurlyBracketOpen) {
                    std::cout << "If block found\n"; // Print the if block found
                    int k = j + 2; // Start looking for the closing bracket after the opening bracket
                    while (tokens[k].type != tokenType::CurlyBracketClose && k < tokens.size()) {
                        ++k; // Skip to the closing bracket
                    }
                    std::cout << "If block ends at index: " << k << "\n"; // Print the index of the closing bracket
                } else {
                    std::cout << "If statement without block found\n"; // Print the if statement without block found
                }
                
            } else {
                std::cout << "If statement without condition found\n"; // Print the if statement without condition found
            }
        } else if (tokens[i].type == tokenType::Else) {
            if (tokens[i + 1].type == tokenType::If) {
                std::cout << "Else if statement found\n"; // Print the else if statement found
            } else if (tokens[i + 1].type == tokenType::CurlyBracketOpen) {
                std::cout << "Else block found\n"; // Print the else block found
                int j = i + 2; // Start looking for the closing bracket after the opening bracket
                while (tokens[j].type != tokenType::CurlyBracketClose && j < tokens.size()) {
                    ++j; // Skip to the closing bracket
                }
                std::cout << "Else block ends at index: " << j << "\n"; // Print the index of the closing bracket
            } else {
                std::cout << "Else statement found\n"; // Print the else statement found
                int k = i + 1; // Start looking for the closing bracket after the else statement
                while (tokens[i].type != tokenType::CurlyBracketClose && k < tokens.size()) {
                    ++k; // Skip to the closing bracket
                }
            }
        } else if (tokens[i].type == tokenType::While) {
            std::cout << "While statement found\n"; // Print the while statement found
            if (tokens[i + 1].type == tokenType::RoundBracketOpen) {
                std::cout << "While condition found\n"; // Print the while condition found
                int j = i + 2; // Start looking for the condition after the opening bracket
                while (tokens[j].type != tokenType::RoundBracketClose && j < tokens.size()) {
                    ++j; // Skip to the closing bracket
                }
                std::cout << "While condition ends at index: " << j << "\n"; // Print the index of the closing bracket
                if (tokens[j + 1].type == tokenType::CurlyBracketOpen) {
                    std::cout << "While block found\n"; // Print the while block found
                    int k = j + 2; // Start looking for the closing bracket after the opening bracket
                    while (tokens[k].type != tokenType::CurlyBracketClose && k < tokens.size()) {
                        ++k; // Skip to the closing bracket
                    }
                    std::cout << "While block ends at index: " << k << "\n"; // Print the index of the closing bracket
                } else {
                    std::cout << "While statement without block found\n"; // Print the while statement without block found
                }
            } else {
                std::cout << "While statement without condition found\n"; // Print the while statement without condition found
            }
        } else if (tokens[i].type == tokenType::For) {
            std::cout << "For statement found\n"; // Print the for statement found
        } else if (tokens[i].type == tokenType::Semicolon) {
            std::cout << "Semicolon found\n"; // Print the semicolon found
        }
    }
    return 0; // Return 0 on success
}
};

#endif // PARSER_H