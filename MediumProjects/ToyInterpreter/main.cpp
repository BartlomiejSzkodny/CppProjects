//https://toylang.com/getting_started/quick-start-guide/#/getting_started/
#include "lexer.h"
#include "parser.h"
#include "token.h"

int main(int argc, char const *argv[])
{
    //use the filename from the command line arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    const char* filename = argv[1];
    std::vector<Token> tokenBuffer; // Vector to store tokens
    // Call the lexer function with the filename
    int result = lexer(filename,tokenBuffer);
    if (result != 0) {
        std::cerr << "Lexer failed with error code: " << result << "\n";
        return result;
    }
    Parser parser; // Create a Parser object
    parser.parse(tokenBuffer); // Call the parse function with the token buffer

    return 0;
}
