#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "token.h"

class Parser {
public:
    std::vector<Token> tokens;
private:
    int checkSyntaxErrors() {
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i].type == tokenType::Unknown) {
                std::cerr << "Syntax error at line " << tokens[i].lineNumber << ", column " << tokens[i].columnNumber << ": Unknown token '" << tokens[i].symbol << "'." << std::endl;
                return -1;
            }
            else if (tokens[i].type == tokenType::Semicolon && i > 0 && tokens[i - 1].type == tokenType::Semicolon) {
                std::cerr << "Syntax error at line " << tokens[i].lineNumber << ", column " << tokens[i].columnNumber << ": Consecutive semicolons." << std::endl;
                return -1;
            }
            else if (!(tokens[i].type == tokenType::VariableId && i > 0 && tokens[i +1].type == tokenType::Variable)) {
                std::cerr << "Syntax error at line " << tokens[i].lineNumber << ", column " << tokens[i].columnNumber << ": Variable ID without assignment." << std::endl;
                return -1;
            }
            else if (tokens[i].type == tokenType::Assign && (i == 0 || tokens[i - 1].type != tokenType::Variable)) {
                std::cerr << "Syntax error at line " << tokens[i].lineNumber << ", column " << tokens[i].columnNumber << ": Assignment without variable." << std::endl;
                return -1;
            }
            else if (tokens[i].type == tokenType::Print && ( tokens[i +1].type != tokenType::String || tokens[i +1].type != tokenType::Variable)) {
                std::cerr << "Syntax error at line " << tokens[i].lineNumber << ", column " << tokens[i].columnNumber << ": Print statement without semicolon." << std::endl;
                return -1;
            } else if (tokens[i].type == tokenType::RoundBracketClose && ( tokens[i +1].type != tokenType::CurlyBracketOpen)) {
                std::cerr << "Syntax error at line " << tokens[i].lineNumber << ", column " << tokens[i].columnNumber << ": Curly bracket without if statement." << std::endl;
                return -1;
            } else if (tokens[i].type == tokenType::Number && (i==0 || tokens[i -1].type == tokenType::Assign || tokens[i -1].type == tokenType::Print )) {
                std::cerr << "Syntax error at line " << tokens[i].lineNumber << ", column " << tokens[i].columnNumber << ": Number without semicolon." << std::endl;
                return -1;
            } 
        }
        
    }
};

#endif // PARSER_H