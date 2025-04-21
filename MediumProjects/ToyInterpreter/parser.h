#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "token.h"

class Parser {
public:
int parse(const std::vector<Token>& tokens, int& index) {
     // Implement the parsing logic here
     // For demonstration, we'll just print the tokens
     while (index < tokens.size()) {
        if (tokens[index].type == tokenType::CurlyBracketClose) {
            return 0; // Skip semicolon
        }
        // Parsing assignment statements
        else if (tokens[index].type == tokenType::Assign) {
            parseAssignment(tokens, index);
        }
        // Parsing print statements
        else if (tokens[index].type == tokenType::Print) {
            parsePrint(tokens, index);
        }
        // Parsing comparison statements
        else if (tokens[index].type == tokenType::Comparison) {
            parseComparison(tokens, index);
        }
        // Parsing if statements
        else if (tokens[index].type == tokenType::If) {
            parseIf(tokens, index);
        }
        // Parsing else statements
        else if (tokens[index].type == tokenType::Else) {
            parseElse(tokens, index);
        }
        // Increment index to avoid infinite loops

        else {
            ++index;
        }
    }
    return 0; // Return 0 on success

}
int parseAssignment(const std::vector<Token>& tokens, int& index) {
    if (tokens[index].type == tokenType::Assign) {
        if (tokens[index+1].type==tokenType::Value && tokens[index+2].type==tokenType::Semicolon && tokens[index-1].type==tokenType::Variable) {
            std::cout << "Assignment: " << tokens[index-1].symbol << " = " << tokens[index+1].symbol << std::endl;
            index += 2; // Skip the value and the semicolon
        } else {
            std::cerr << "Error: Invalid assignment at line " << tokens[index].lineNumber << ", column " << tokens[index].columnNumber << std::endl;

        }

    }
    // Implement the parsing logic for assignment statements here
    return 0; // Return 0 on success
};
int parsePrint(const std::vector<Token>& tokens, int& index) {
    if (tokens[index].type == tokenType::Print) {
        if (tokens[index+1].type==tokenType::Value || tokens[index+1].type==tokenType::Variable) {
            std::cout << "Print: " << tokens[index+1].symbol << std::endl;
            index++;
        } else {
            std::cerr << "Error: Invalid print statement at line " << tokens[index].lineNumber << ", column " << tokens[index].columnNumber << std::endl;
        }
    }
    return 0; // Return 0 on success
};

int parseComparison(const std::vector<Token>& tokens, int& index) {
    if (tokens[index].type == tokenType::Comparison) {
        if ((tokens[index-1].type == tokenType::Value || tokens[index-1].type == tokenType::Variable) &&
            (tokens[index+1].type == tokenType::Value || tokens[index+1].type == tokenType::Variable)) {
            std::cout << "Comparison: " 
                      << tokens[index-1].symbol << " " 
                      << tokens[index].symbol << " " 
                      << tokens[index+1].symbol << std::endl;
            index += 1; // move past comparison operator
        } else {
            std::cerr << "Error: Invalid comparison at line " 
                      << tokens[index].lineNumber << ", column " 
                      << tokens[index].columnNumber << std::endl;
        }
    }
    return 0;
}


int parseIf(const std::vector<Token>& tokens, int& index) {
    if (tokens[index+1].type == tokenType::RoundBracketOpen) {
        std::cout << "If statement: " << tokens[index].symbol << std::endl;
        index += 2; // Skip 'if' and '('
        
        while (index < tokens.size()) {
            if (tokens[index].type == tokenType::RoundBracketClose) {
                std::cout << "End of if condition" << std::endl;
                index++; // Move past ')'
                break;
            }
            if (tokens[index].type == tokenType::Comparison) {
                parseComparison(tokens, index);
            }
            index++;
        }
        
        if (index < tokens.size() && tokens[index].type == tokenType::CurlyBracketOpen) {
            std::cout << "If block starts" << std::endl;
            index++; // Move past '{'

            while (index < tokens.size()) {
                if (tokens[index].type == tokenType::CurlyBracketClose) {
                    break;
                }
                parse(tokens, index); // Parse anything inside the block
            }
            if (index < tokens.size() && tokens[index].type == tokenType::CurlyBracketClose) {
                std::cout << "End of if block" << std::endl;
                index++; // Move past '}'
            } else {
                std::cerr << "Error: Missing closing curly bracket in if block" << std::endl;
            }
        } else {
            std::cerr << "Error: Missing '{' after if condition" << std::endl;
        }
    } else {
        std::cerr << "Error: Invalid if statement at line " 
                  << tokens[index].lineNumber << ", column " 
                  << tokens[index].columnNumber << std::endl;
    }
    return 0;
}

int parseElse(const std::vector<Token>& tokens, int& index) {
    if (tokens[index].type == tokenType::Else) {
        std::cout << "Else statement: " << tokens[index].symbol << std::endl;
        index++; // Move past 'else'

        if (tokens[index].type == tokenType::CurlyBracketOpen) {
            std::cout << "Else block starts" << std::endl;
            index++; // Move past '{'

            while (index < tokens.size()) {
                if (tokens[index].type == tokenType::CurlyBracketClose) {
                    break;
                }
                parse(tokens, index); // Parse anything inside the block
            }
            if (index < tokens.size() && tokens[index].type == tokenType::CurlyBracketClose) {
                std::cout << "End of else block" << std::endl;
                index++; // Move past '}'
            } else {
                std::cerr << "Error: Missing closing curly bracket in else block" << std::endl;
            }
        } else {
            std::cerr << "Error: Missing '{' after else" << std::endl;
        }
    } else {
        std::cerr << "Error: Invalid else statement at line "
                  << tokens[index].lineNumber << ", column "
                  << tokens[index].columnNumber << std::endl;
    }
    return 0;
}



};

#endif // PARSER_H