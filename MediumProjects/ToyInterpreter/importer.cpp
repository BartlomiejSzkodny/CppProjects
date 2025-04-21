#include <iostream>
#include <fstream>  // For file operations
#include <string>   // For std::string
#include <vector>  // For std::vector
#include "structures.cpp"

int printLineBuffer(const std::vector<Line>& lineBuffer) {
    for (const auto& line : lineBuffer) {
        std::cout << line.lineNumber << ": " << line.lineContent << "\n"; // Print the line number and content
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
            continue; // Skip comment lines
        }else {
            lineBuffer.push_back({lineNumber, line}); // Store the line in the vector
            lineNumber++; // Increment the line number
        }

        // Process the line (for example, print it)
    }
    printLineBuffer(lineBuffer); // Print the line buffer

    file.close(); 
    return 0;


}


