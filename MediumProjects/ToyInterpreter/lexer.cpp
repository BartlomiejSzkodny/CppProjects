#include <iostream>
#include <fstream>  // For file operations
#include <string>   // For std::string
#include <vector>  // For std::vector
#include "token.h"
#include "structures.cpp" // Include the structures header file
#include <iomanip> // Include for std::setw

int printLineBuffer(const std::vector<Line>& lineBuffer) {
    for (const auto& line : lineBuffer) {
        std::cout << line.lineNumber << ": " << line.lineContent << "\n"; // Print the line number and content
    }
    return 0;
}
int printTokenBuffer(const std::vector<Token>& tokenBuffer) {
    

    std::cout << std::left << std::setw(40) << "Symbol" 
              << std::setw(20) << "Type" 
              << std::setw(10) << "Line" 
              << "Column\n"; // Print header
    std::cout << "-------------------------------------------------------------------------------------\n";
    for (auto token : tokenBuffer) {
        std::cout << std::left << std::setw(40) << token.symbol 
                  << std::setw(20) << token.tokenTypeToString() 
                  << std::setw(10) << token.lineNumber 
                  << token.columnNumber << "\n"; // Print each token in columns
    }
    return 0;
}
int lexer(const char* filename) {
    // Open the file in read mode
    std::vector<Line> lineBuffer; // Vector to store lines
    int lineNumber = 1;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for reading.\n";
        return 1;
    }
    while(true) {
        
        std::string line;
        if (!std::getline(file, line)) {
            break; // End of file reached
        }
        if (line.empty()) {
            continue; // Skip empty lines
        }else if (line[0] == '#') {
            lineNumber++; // Increment the line number for comment lines
            continue; // Skip comment lines
        }else {
            lineBuffer.push_back({lineNumber, line}); // Store the line in the vector
            lineNumber++; // Increment the line number
        }

        // Process the line (for example, print it)
    }
    printLineBuffer(lineBuffer); // Print the line buffer
    std::vector<Token> tokenBuffer; // Vector to store tokens
    for (auto& line : lineBuffer) {
        for(int i = 0; i < line.lineContent.length(); i++) {
            Token token;
            token.lineNumber = line.lineNumber; // Set the line number for the token
            token.columnNumber = i; // Set the column number for the token
            if (line.lineContent[i] == ' ') {
                continue; // Skip spaces
            } else if (line.lineContent[i] == ';') {
                token.type = tokenType::Semicolon; // Set the token type to Semicolon
                token.symbol = ";"; // Set the symbol for the token
            } else if (isdigit(line.lineContent[i])) {
                while (i < line.lineContent.length() && isdigit(line.lineContent[i])) {
                    token.symbol += line.lineContent[i]; // Append digits to the symbol
                    i++; // Move to the next character
                }
                token.type = tokenType::Number; // Set the token type to Number
                i--; // Step back one position to reprocess the current character if it's not part of the number

            } else if (line.lineContent[i] == '+') {
                token.type = tokenType::Plus; // Set the token type to Plus
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            } else if (line.lineContent[i] == '-') {
                token.type = tokenType::Minus; // Set the token type to Minus
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            } else if (line.lineContent[i] == '*') {
                token.type = tokenType::Multiply; // Set the token type to Multiply
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            } else if (line.lineContent[i] == '/') {
                token.type = tokenType::Divide; // Set the token type to Divide
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            } else if (line.lineContent[i] == '(') {
                token.type = tokenType::RoundBracketOpen; // Set the token type to ParenthesisOpen
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            } else if (line.lineContent[i] == ')') {
                token.type = tokenType::RoundBracketClose; // Set the token type to ParenthesisClose
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            } else if (line.lineContent[i] == '=') {
                token.type = tokenType::Assign; // Set the token type to Equal
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            } else if (line.lineContent[i] == '%') {
                token.type = tokenType::Modulus; // Set the token type to Modulus
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            }  else if (line.lineContent[i] == '"') {
                token.type = tokenType::String; // Set the token type to String
                i++; // Move past the opening quote
                while (i < line.lineContent.length() && line.lineContent[i] != '"') {
                    token.symbol += line.lineContent[i++]; // Append characters to the symbol until closing quote
                }
                if (i < line.lineContent.length()) {
                    i++; // Move past the closing quote
                }
            } else if (line.lineContent[i] == '\'') {
                token.type = tokenType::Char; // Set the token type to Char
                i++; // Move past the opening quote
                while (i < line.lineContent.length() && line.lineContent[i] != '\'') {
                    token.symbol += line.lineContent[i++]; // Append characters to the symbol until closing quote
                }
                if (i < line.lineContent.length()) {
                    i++; // Move past the closing quote
                }
            } else if (line.lineContent[i] == '#') {
                token.type = tokenType::Comment; // Set the token type to Comment
                token.symbol = line.lineContent.substr(i); // Set the symbol to the rest of the line
                break; // Stop processing the line after the comment
            }else if (line.lineContent[i]=='<') {
                token.type = tokenType::LessThan; // Set the token type to LessThan
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            }else if (line.lineContent[i]=='>') {
                token.type = tokenType::GreaterThan; // Set the token type to GreaterThan
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            }else if (line.lineContent[i]=='!' && line.lineContent[i+1]=='=') {
                token.type = tokenType::NotEqual; // Set the token type to NotEqual
                token.symbol = line.lineContent[i]; // Set the symbol for the token
                i++; // Move past the '='
            }else if (line.lineContent[i]=='<' && line.lineContent[i+1]=='=') {
                token.type = tokenType::LessThanOrEqual; // Set the token type to LessThanOrEqual
                token.symbol = line.lineContent[i]; // Set the symbol for the token
                i++; // Move past the '='
            }else if (line.lineContent[i]=='>' && line.lineContent[i+1]=='=') {
                token.type = tokenType::GreaterThanOrEqual; // Set the token type to GreaterThanOrEqual
                token.symbol = line.lineContent[i]; // Set the symbol for the token
                i++; // Move past the '='
            }else if (line.lineContent[i]=='&' && line.lineContent[i+1]=='&') {
                token.type = tokenType::AND; // Set the token type to Boolean
                token.symbol = line.lineContent[i]; // Set the symbol for the token
                i++; // Move past the '&'
            }else if (line.lineContent[i]=='|' && line.lineContent[i+1]=='|') {
                token.type = tokenType::OR; // Set the token type to Boolean
                token.symbol = line.lineContent[i]; // Set the symbol for the token
                i++; // Move past the '|'
            }else if (line.lineContent[i]=='=' && line.lineContent[i+1]=='=') {
                token.type = tokenType::Equal; // Set the token type to Equal
                token.symbol = line.lineContent[i]; // Set the symbol for the token
                i++; // Move past the '='
            }else if (line.lineContent[i]=='{') {
                token.type = tokenType::CurlyBracketOpen; // Set the token type to CurlyBracketOpen
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            }
            else if (line.lineContent[i]=='}') {
                token.type = tokenType::CurlyBracketClose; // Set the token type to CurlyBracketClose
                token.symbol = line.lineContent[i]; // Set the symbol for the token
            }

                
            
            
            else if (isalpha(line.lineContent[i])) {
                token.symbol = line.lineContent[i]; // Set the symbol for the token
                while (i + 1 < line.lineContent.length() && isalnum(line.lineContent[i + 1])) {
                    token.symbol += line.lineContent[++i]; // Append the next character to the symbol
                }
                if(token.symbol == "if") {
                    token.type = tokenType::If; // Set the token type to If
                } else if (token.symbol == "else") {
                    token.type = tokenType::Else; // Set the token type to Else
                } else if (token.symbol == "while") {
                    token.type = tokenType::While; // Set the token type to While
                } else if (token.symbol == "for") {
                    token.type = tokenType::For; // Set the token type to For
                } else if (token.symbol == "true" || token.symbol == "false") {
                    token.type = tokenType::Boolean; // Set the token type to Boolean
                } else if (token.symbol == "var") {
                    token.type = tokenType::VariableId; // Set the token type to Variable
                } else if (token.symbol == "print") {
                    token.type = tokenType::Print; // Set the token type to Print
                }
                else {
                    token.type = tokenType::Variable; // Set the token type to Variable
                }
            }
            tokenBuffer.push_back(token); // Add the token to the buffer
        }
          
        
    }
    printTokenBuffer(tokenBuffer); // Print the token buffer

    file.close(); 
    return 0;


}


